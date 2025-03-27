class TCP:
    def __init__(self, source_port, destination_port, ip):
        # Связанный IP-пакет, содержащий информацию о источнике и назначении
        self.ip = ip
        # Порт источника, с которого исходит сегмент
        self.source_port = source_port
        # Порт назначения, к которому сегмент направлен
        self.destination_port = destination_port
        # Порядковый номер сегмента (используется для упорядочивания сегментов)
        self.sequence = 0
        # Номер подтверждения (используется для подтверждения приема сегментов)
        self.acknowledgment = 0
        # Смещение данных (размер заголовка TCP в 32-битных словах)
        self.offset = 20

        # Nonce Sum: используется для защиты от некоторых видов атак
        self.ns = None

        # Reserved
        # Congestion Window Reduced: уменьшение окна перегрузки
        self.cwr = None
        # ENC-Echo: используется для указания, что в сети наблюдается перегрузка
        self.ece = None

        # Flags
        # Urgent Pointer: если True, указывает, что передаются срочные данные
        self.urg = None
        # Acknowledgment: если True, пакет содержит номер подтверждения
        self.ack = False
        # Push Function: призывает приложение получателя как можно скорее обработать данные
        self.psh = None
        # Reset: сброс соединения
        self.rst = False
        # Synchronize: используется для установления соединения
        self.syn = False
        # Finish: используется для завершения соединения
        self.fin = False
        # Размер окна: указывает количество данных, которое отправитель готов принять
        self.window_size = None
        # Контрольная сумма, используемая для проверки целостности данных TCP-сегмента
        self.checksum = 0
        # Указатель на срочные данные
        self.urgent = None

    def __str__(self):
        return f"Source {self.ip.source_ip}:{self.source_port}, " \
               f"Destination {self.ip.destination_ip}:{self.destination_port}, " \
               f"Sequence: {self.sequence}, " \
               f"Ack: {self.acknowledgment}, " \
               f"Payload: '{self.ip.payload}'"

    def __repr__(self):
        return "\n".join(
            [
                f"IP: {self.ip}",
                f"Source_port: {self.source_port}",
                f"Destination: {self.destination_port}",
                f"Sequence: {self.sequence}",
                f"Acknowledgment: {self.acknowledgment}",
                f"Offset: {self.offset}",
                f"NS: {self.ns}",
                f"CWR: {self.cwr}",
                f"URG: {self.urg}",
                f"ACK: {self.ack}",
                f"PSH: {self.psh}",
                f"RST: {self.rst}",
                f"SYN: {self.syn}",
                f"FIN: {self.fin}",
                f"Window size: {self.window_size}",
                f"Checksum: {self.checksum}",
                f"Urgent: {self.urgent}",
            ]
        )
