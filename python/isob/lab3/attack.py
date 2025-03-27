import time

from connection import Connection, print_package
from client import Client
from hacker import Hacker


# Устанавливает флаг RST в пакете при каждом пятом вызове
class RSTMiddleware:
    def __init__(self):
        self.call_number = 0

    def change(self, package):
        self.call_number += 1
        if self.call_number == 5:
            package.rst = True
        return package

# Изменяет содержимое пакета и выводит информацию о флагах, начиная с 5-го пакета.
class PassiveScan:
    def __init__(self):
        self.call_number = 0

    def change(self, package):
        self.call_number += 1
        if self.call_number >= 5 and self.call_number % 5 == 0:
            package.ip.payload = "Passive scan"
            print("Information: ", "syn:", package.syn, "ack:", package.ack, "rst:", package.rst)
        return package

# Изменяет содержимое пакета на 'Sniffing' и выводит его детальное представление начиная с 5-го вызова.
class Sniffing:
    def __init__(self):
        self.call_number = 0

    def change(self, package):
        self.call_number += 1
        if self.call_number >= 5:
            package.ip.payload = "Sniffing"
            print("Information: ", repr(package))
        return package

# Похищает соединение, изменяя пакеты для перенаправления ответов обратно к источнику
class ConnectionHijack:
    def __init__(self):
        self.call_number = 0

    def change(self, package):
        self.call_number += 1
        if self.call_number >= 5:
            package.ip.payload = "Connection hijacked"
            t = package.sequence
            package.sequence = package.acknowledgment
            package.acknowledgment = t + len(package.ip.payload)
            package.ip.destination_ip = package.ip.source_ip
            package.destination_port = package.source_port
            print_package(package)
        return package


def run_attacks():
    client = Client(123, 1)
    server1 = Client(221, 3)
    server2 = Hacker(331, 2)

    # Изменяет содержимое пакета на 'Sniffing' и выводит его детальное представление начиная с 5-го вызова.
    sniffing = Sniffing()

    # Изменяет содержимое пакета и выводит информацию о флагах, начиная с 5-го пакета.
    passive_scan = PassiveScan()

    # Устанавливает флаг RST в пакете при каждом пятом вызове
    rst_middleware = RSTMiddleware()

    # Похищает соединение, изменяя пакеты для перенаправления ответов обратно к источнику
    connection_hijack = ConnectionHijack()
    connection = Connection([client, server1, server2], [rst_middleware])

    client.call_any_other(connection)


run_attacks()