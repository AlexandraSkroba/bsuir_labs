from des import encrypt, decrypt
from helpers import get_timestamp, get_random_key, hex2decimal, print_line
from server import Server
import random


class TGS:
    def __init__(self):
        self.period = 60  # 1 minute
        self.tgs = random.randint(0, 255)
        self.as_key = None
        self.client_keys = {}
        self.server_keys = {}

    def grant_ticket(self, message):
        tgt = self.parse_ticket(decrypt(message[:5], self.as_key))
        print("AFTER TGS DECRYPTED THE MESSAGE:")
        print("{TGT} = ", tgt)
        aut = [hex2decimal(x) for x in decrypt(message[5:-1], tgt['k_c_tgs'])]
        print("{Aut1} = ", aut)
        server_id = message[-1]
        print("{ID} = ", server_id)
        validity = self.is_ticket_valid(tgt, aut)
        if type(validity) is str:
            return validity
        # шаг 4: TGS -> C: { {TGS}K(TGS_SS), K(C_SS) }K(C_TGS)
        print_line()
        print("4. TGS -> C: { {TGS}K(TGS_SS), K(C_SS) }K(C_TGS)")
        message = self.generate_ss_ticket(tgt, server_id)
        return message

    def is_ticket_valid(self, ticket, aut):
        # проверка срока годности тикета TGT
        print("\nПРОВЕРКА ВАЛИДНОСТИ ТИКЕТА\n")
        current_time = aut[1]
        ticket_timestamp = ticket['t1']
        ticket_lifetime = ticket['p1']

        if current_time - ticket_timestamp > ticket_lifetime:
            print(f"1. t2 - t1 = {current_time - ticket_timestamp} > {ticket_lifetime} = p1")
            return "Expired ticket"
        else:
            print(f"1. t2 - t1 = {current_time - ticket_timestamp} < {ticket_lifetime} = p1")
            print("OK")
            if aut[0] != ticket['cid']:
                print(f"2. c из tgt {ticket['cid']} != c из aut1 {aut[0]}")
                return "Client ids don't match!"
            else:
                print(f"2. c из tgt {ticket['cid']} == c из aut1 {aut[0]}")
                print("OK")
            if ticket['tgs'] != self.tgs:
                print(f"3. tgs из tgt {ticket['tgs']} != tgs сервера {self.tgs}")
                return "Wrong TGS server id!"
            else:
                print(f"3. tgs из tgt {ticket['tgs']} == tgs сервера {self.tgs}")
                print("OK")
            return True

    def parse_ticket(self, ticket_enc):
        ticket = {'cid': hex2decimal(ticket_enc[0]),
                  'tgs': hex2decimal(ticket_enc[1]),
                  't1': hex2decimal(ticket_enc[2]),
                  'p1': hex2decimal(ticket_enc[3]),
                  'k_c_tgs': ticket_enc[4]}
        return ticket

    def generate_ss_ticket(self, ticket, sid):
        # генерация тикета для SS
        k_c_ss = get_random_key()
        tgs = [ticket['cid'], sid, get_timestamp(), self.period, k_c_ss]
        print("\nNon-encrypted TGS: ", tgs, '\n')
        tgs = encrypt(tgs, self.server_keys[sid])
        message = tgs + [k_c_ss]
        print("\nNon-encrypted message: ", message, '\n')
        message = encrypt(message, ticket['k_c_tgs'])
        return message

    def add_client(self, cid, key):
        self.client_keys[cid] = key

    def add_server(self, server: Server):
        self.server_keys[server.id] = get_random_key()
        server.add_tgs(self.tgs, self.server_keys[server.id])
