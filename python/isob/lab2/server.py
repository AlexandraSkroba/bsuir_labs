from des import decrypt, encrypt
from helpers import hex2decimal, print_line
import random


class Server:
    def __init__(self):
        self.id = random.randint(0, 255)
        self.tgs_id = None
        self.tgs_key = None  # K(TGS_SS)
        self.client_keys = {}

    def process_request(self, message, aut2):
        # расшифровка тикета от TGS
        print("\nEncrypted message: ", message, '\n')
        tgs = decrypt(message[:-2], self.tgs_key)
        tgs = self.parse_ticket(tgs)
        aut2 = [hex2decimal(x) for x in decrypt(message[-2:], tgs['k_c_ss'])]
        self.add_client(tgs['c'], tgs['k_c_ss'])
        print("AFTER SS DECRYPTED THE MESSAGE:")
        print("{TGS} = ", tgs)
        print("{Aut2} = ", aut2)
        if not self.check_validity(tgs, aut2):
            return None
        print_line()
        print("6. SS -> C: {t4+1}K(C_SS)")
        response = aut2[1] + 1
        print("\nNon-encrypted message: ", response, '\n')
        response = encrypt(response, tgs['k_c_ss'])
        return response

    def parse_ticket(self, tgs):
        ticket = {'c': hex2decimal(tgs[0]),
                  'ss': hex2decimal(tgs[1]),
                  't3': hex2decimal(tgs[2]),
                  'p2': hex2decimal(tgs[3]),
                  'k_c_ss': tgs[4]}
        return ticket

    def check_validity(self, ticket, aut):
        # проверка срока тикета TGS
        print("\nПРОВЕРКА ВАЛИДНОСТИ ТИКЕТА\n")
        current_time = aut[1]
        ticket_timestamp = ticket['t3']
        ticket_lifetime = ticket['p2']
        if current_time - ticket_timestamp > ticket_lifetime:
            print(f"1. t4 - t3 = {current_time - ticket_timestamp} > {ticket_lifetime} = p2")
            print("Expired ticket")
            return False
        else:
            print(f"1. t4 - t3 = {current_time - ticket_timestamp} < {ticket_lifetime} = p2")
            print("OK")

            if aut[0] != ticket['c']:
                print(f"2. c из tgs {ticket['cid']} != c из aut1 {aut[0]}")
                print("Client ids don't match!")
                return False
            else:
                print(f"2. c из tgs {ticket['c']} == c из aut1 {aut[0]}")
                print("OK")
            if self.id != ticket['ss']:
                print(f"3. ss из tgs {ticket['ss']} != id сервера {self.id}")
                print("Wrong server id!")
                return False
            else:
                print(f"3. ss из tgt {ticket['ss']} == id сервера {self.id}")
                print("OK")
            return True

    def add_tgs(self, tgs_id, key):
        self.tgs_id = tgs_id
        self.tgs_key = key

    def add_client(self, cid, key):
        self.client_keys[cid] = key

    def delete_client(self, cid):
        del self.client_keys[cid]