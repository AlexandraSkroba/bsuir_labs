class IP:
    def __init__(self, source_ip, destination_ip, payload):
        # Версия IP-протокола, 4 для IPv4
        self.version = 4

        # Internet Header Length: длина заголовка в 32-битных словах, минимум 5 (20 байт)
        self.ihl = 5

        # Differentiated Services Code Point: указывает на класс обслуживания
        self.dscp = None

        # Explicit Congestion Notification: уведомление о перегрузке
        self.ecn = None

        # Общая длина IP-пакета, включая заголовок и данные
        self.total_length = 576

        # Уникальный идентификатор пакета для корректной сборки фрагментов
        self.id = None

        # Флаги для управления и состояния фрагментации пакета
        self.flags = None

        # Смещение фрагмента в рамках исходного пакета
        self.fragment_offset = None

        # Time To Live: ограничение времени жизни пакета, для предотвращения зацикливания
        self.ttl = 15

        # Идентификатор протокола верхнего уровня (6 - TCP)
        self.protocol = 6

        # Контрольная сумма для проверки целостности заголовка
        self.checksum = None

        # IP-адрес отправителя пакета
        self.source_ip = source_ip

        # IP-адрес получателя пакета
        self.destination_ip = destination_ip

        # Полезная нагрузка пакета
        self.payload = payload

    def __str__(self):
        return f"IPv{self.version}"

    def __repr__(self):
        return "\n".join(
            [
                f"Version: {self.version}",
                f"IHL: {self.ihl}",
                f"DSCP: {self.dscp}",
                f"ECN: {self.ecn}",
                f"Total length: {self.total_length}",
                f"ID: {self.id}",
                f"Flags: {self.flags}",
                f"Fragment offset: {self.fragment_offset}",
                f"TTL: {self.ttl}",
                f"Protocol: {self.protocol}",
                f"Checksum: {self.checksum}",
                f"Source IP: {self.source_ip}",
                f"Destination IP: {self.destination_ip}",
                f"Parameters: {self.payload}",
            ]
        )
