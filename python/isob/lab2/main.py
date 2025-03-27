from client import Client
from as_server import AS
from tgs import TGS
from server import Server
import time

if __name__ == "__main__":
    as_server = AS()
    tgs = TGS()
    as_server.add_tgs(tgs)
    client = Client(as_server, tgs)
    client1 = Client(as_server, tgs)
    server = Server()
    tgs.add_server(server)
    server1 = Server()
    tgs.add_server(server1)

    client.connect(server)
    client.connect(server)

    # time.sleep(61)
    client.connect(server1)

    client1.connect(server)
    client1.connect(server1)

    print('AS clients: ', as_server.client_keys)
    print('TGS clients: ', tgs.client_keys)
    print('TGS servers: ', tgs.server_keys)
    print('Client\'s servers: ', client.server_keys)
    print('Server clients: ', server.client_keys)
    print('Server1 clients: ', server1.client_keys)
