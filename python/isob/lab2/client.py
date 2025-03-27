from des import encrypt, decrypt
from helpers import get_timestamp, get_random_key, hex2decimal, print_line
from server import Server
from as_server import AS
from tgs import TGS
import random


class Client:
    def __init__(self, as_: AS, tgs_: TGS):
        self.tgt = None
        self.k_c_tgs = None
        self.c = random.randint(0, 255)
        self.key = get_random_key()
        self.as_ = as_
        self.tgs_ = tgs_
        self.server_keys = {}
        self.as_.add_client(self.c, self.key)

    def connect(self, server: Server):
        print(f"Клиент ({self.c}) пытается подключиться к серверу ({server.id})")
        try:
            k_c_ss = server.client_keys[self.c]
            print("Клиент уже подключен к данному серверу! K(C_SS) = ", k_c_ss, '\n\n\n\n')
            return
        except KeyError:
            pass

        if self.tgt and self.k_c_tgs:
            # скип 1, 2 шага если тикет уже есть
            print("У клиента уже есть {TGT} тикет, переходим к шагу 3")
            tgt = self.tgt
        else:
            # шаг 1
            print_line()
            print("1. C -> AS: {c} = ", self.c)
            response = self.request_authentication(self.as_, self.tgs_)

            # шаг 2
            tgt, k_c_tgs = self.receive_ticket_from_as(response, self.key)
            self.k_c_tgs = k_c_tgs
            print("AFTER C DECRYPTED THE MESSAGE:")
            print("{TGT}K(AS_TGS) = ", tgt, "\nK(C_TGS) = ", k_c_tgs)

        # шаг 3
        response = self.request_service_ticket(self.tgs_, tgt, self.k_c_tgs, server.id)
        if type(response) is str:
            print(response)
            print("An error occurred! Try again")
            if response == "Expired ticket":
                print("Пытаемся получить новый тикет...")
                self.clear_ticket()
                self.connect(server)
            return

        # шаг 4
        tgs, k_c_ss = self.receive_service_ticket(response, self.k_c_tgs)
        self.add_server(server.id, k_c_ss)

        # шаг 5
        response, t4 = self.request_service_access(server, tgs)
        if not response:
            print("An error occurred! Try again")
            del self.server_keys[server.id]
            return

        # шаг 6
        result = self.receive_service_response(response, k_c_ss, t4)
        if not result:
            print("Server is not valid!")
            del self.server_keys[server.id]
            server.delete_client(self.c)
        else:
            print(f"SUCCESS! Клиент ({self.c}) подключился к серверу ({server.id})!!!!\n\n\n\n")

    def request_authentication(self, auth_server: AS, tgs: TGS):
        # шаг 1: C -> AS: {c}
        return auth_server.authenticate_client(self.c, tgs)

    def receive_ticket_from_as(self, ticket_from_as, client_key):
        # шаг 2: AS -> C: { {TGT}K(AS_TGS), K(C_TGS) }K(C)
        # {TGT} = {c, tgs, t1, p1, K(C_TGS)}
        print("\nEncrypted messsage: ", ticket_from_as, '\n')
        decrypted_ticket = decrypt(ticket_from_as, client_key)
        decrypted_ticket = (decrypted_ticket[:-1], decrypted_ticket[-1])
        self.tgt = decrypted_ticket[0]
        return decrypted_ticket

    def request_service_ticket(self, tgs_server, tgt, k_c_tgs, server_id):
        # шаг 3: C -> TGS: {TGT}K(AS_TGS), {Aut1}K(C_TGS), {ID}
        # {Aut1} = {c, t2}
        print_line()
        print("3. C -> TGS: {TGT}K(AS_TGS), {Aut1}K(C_TGS), {ID}")
        aut1 = [self.c, get_timestamp()]
        aut1_encrypted = encrypt(aut1, k_c_tgs)
        message = tgt + aut1_encrypted + [server_id]
        print("\nNon-encrypted message: \n{TGT}K(AS_TGS): ", tgt, ", \n{Aut1}: ", aut1, ", \n{ID}: ", server_id, '\n')
        print("\nEncrypted message: \n{TGT}K(AS_TGS): ", tgt, ", \n{Aut1}K(C_TGS): ", aut1_encrypted,
              ", \n{ID}: ", server_id, '\n')
        return tgs_server.grant_ticket(message)

    def receive_service_ticket(self, tgs_response, k_c_tgs):
        # шаг 4: TGS -> C: { {TGS}K(TGS_SS), K(C_SS) }K(C_TGS)
        # {TGS} = {c, ss, t3, p2, K(C_SS)}
        print("\nEncrypted message: ", tgs_response, '\n')
        response = decrypt(tgs_response, k_c_tgs)
        tgs = response[:-1]
        k_c_ss = response[-1]
        print("AFTER C DECRYPTED THE MESSAGE:")
        print("{TGS}K(TGS_SS): ", tgs, "\nK(C_SS): ", k_c_ss)
        return tgs, k_c_ss

    def request_service_access(self, server, tgs_ticket):
        # шаг 5: C -> SS: {TGS}K(TGS_SS), {Aut2}K(C_SS)
        # {Aut2} = {c, t4}
        print_line()
        print("5. C -> SS: {TGS}K(TGS_SS), {Aut2}K(C_SS)")
        aut2 = [self.c, get_timestamp()]
        print("\nNon-encrypted message: \n{TGS}K(TGS_SS): ", tgs_ticket, ", \n{Aut2}: ", aut2, '\n')
        aut2_encrypted = encrypt(aut2, self.server_keys[server.id])
        message = tgs_ticket + aut2_encrypted
        return server.process_request(message, aut2_encrypted), aut2[1]

    def receive_service_response(self, server_response, k_c_ss, time):
        # шаг 6: SS -> C: {t4+1}K(C_SS)
        print("\nEncrypted message: ", server_response, '\n')
        response = hex2decimal(decrypt(server_response, k_c_ss))
        print("AFTER C DECRYPTED THE MESSAGE:")
        print("{t4+1} = ", response)
        print("\nПРОВЕРКА ВАЛИДНОСТИ ОТВЕТА:")
        print("По версии клиента {t4+1} =", time + 1)
        print("По версии сервера {t4+1} =", response)
        if not response - 1 == time:
            print(f"{time + 1} != {response}")
            return False
        else:
            print(f"{time + 1} == {response}")
        return True

    def add_server(self, sid, key):
        self.server_keys[sid] = key

    def clear_ticket(self):
        self.tgt = None
