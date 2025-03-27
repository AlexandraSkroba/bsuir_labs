import unittest
from tkinter import Tk
from main import DataBase, Application, RoleWindow

class TestApplication(unittest.TestCase):
    def setUp(self):
        self.db = DataBase()
        self.app = Application(self.db)
        self.root = Tk()

    def tearDown(self):
        self.root.destroy()

    # def test_buffer_overflow(self):
    #     # Проверяем ограничение на ввод более 10 символов
    #     username_entry = self.app.username_entry
    #     username_entry.delete(0, 'end')
    #     username_entry.insert(0, '12345678901')
    #     self.app.login()
    #     error_message = self.app.tk.children['!messagebox'].children['messagebox']
    #     self.assertTrue(error_message, "Ожидалось сообщение об ошибке из-за переполнения буфера")

    # def test_xss_attack(self):
    #     # Проверяем экранирование HTML-кода
    #     message_entry = RoleWindow(self.root, 'user', self.db, 'user1').data_entry
    #     message_entry.delete(0, 'end')
    #     message_entry.insert(0, "<script>")
    #     message = message_entry.get()
    #     self.assertNotIn("<script>", message, "HTML-тег <script> не должен быть в сообщении")

    def test_privileges(self):
        # Проверяем доступ к административным функциям от имени пользователя
        self.db.add_user('test_admin', 'password', 'admin')
        self.db.add_user('test_user', 'password', 'user')
        self.app.username_entry.insert(0, 'user1')
        self.app.password_entry.insert(0, '1234')
        self.app.login()
        role_window = RoleWindow(self.root, 'user', self.db, 'user1')
        role_window.manage_users()
        error_message = self.app.tk.children['!messagebox'].children['messagebox']
        self.assertTrue(error_message, "Ожидалось сообщение об ошибке из-за недостаточных привилегий")

    def test_dos_attack(self):
        role_window = RoleWindow(self.root, 'user', self.db, 'user1')
        message_entry = role_window.data_entry
        message_entry.delete(0, 'end')
        message_entry.insert(0, "Test")
        role_window.submit_data()
        for _ in range(5):
            role_window.submit_data()
            self.root.after(500)
        error_message = self.app.tk.children['!messagebox'].children['messagebox']
        self.assertTrue(error_message, "Ожидалось сообщение об ошибке из-за частых запросов")

if __name__ == '__main__':
    unittest.main()
