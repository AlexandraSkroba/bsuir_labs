from des import encrypt, decrypt
from helpers import get_timestamp, get_random_key, print_line
from tgs import TGS


class AS:
    def __init__(self):
        self.period = 60  # 1 minute
        self.tgs_id = None
        self.tgs_key = None  # K(AS_TGS)
        self.client_keys = {}

    def authenticate_client(self, cid, tgs):
        print_line()
        print("2. AS -> C: { {TGT}K(AS_TGS), K(C_TGS) }K(C) ")
        # генерация тикета TGT и ключа K(C_TGS)
        tgs_ticket, k_c_tgs = self.generate_tgs_ticket(cid, tgs)
        try:
            key_c = self.client_keys[cid]
        except KeyError:
            print("Unknown client!")
            return
        message = tgs_ticket + [k_c_tgs]
        print("\nNon-encrypted message: ", message, '\n')
        message = encrypt(message, key_c)
        return message

    def generate_tgs_ticket(self, cid, tgs):
        client_id = cid
        tgs_id = tgs.tgs
        t1 = get_timestamp()
        p1 = self.period
        key_c_tgs = get_random_key()
        tgs.add_client(cid, key_c_tgs)
        tgs_ticket = [client_id, tgs_id, t1, p1, key_c_tgs]
        print("\nNon-ecrypted {TGT}: ", tgs_ticket, '\n')
        tgs_ticket = encrypt(tgs_ticket, self.tgs_key)
        return tgs_ticket, key_c_tgs

    def add_tgs(self, tgs: TGS):
        self.tgs_id = tgs.tgs
        self.tgs_key = get_random_key()
        tgs.as_key = self.tgs_key

    def add_client(self, cid, k_c):
        self.client_keys[cid] = k_c
