import hashlib
import time
import tkinter as tk
from tkinter import messagebox, simpledialog
import html
from functools import wraps

class PrivilegesProtection:
    @staticmethod
    def require_admin(func):
        @wraps(func)
        def wrapper(self, *args, **kwargs):
            if self.role == "admin":
                return func(self, *args, **kwargs)
            else:
                messagebox.showerror("Error", "Access denied. Administrator role required.")
            return None
        return wrapper



def sanitize(input_string):
    return html.escape(input_string)


class DataBase:
    def __init__(self):
        self.users = {}
        self.messages = []
        self.last_action_time = {}

    def add_user(self, username, password, role):
        hash_password = hashlib.sha256(password.encode()).hexdigest()
        self.users[username] = (hash_password, role)
        self.last_action_time[username] = 0

    def add_message(self, username, message):
        sanitized_message = sanitize(message)
        current_time = time.time()
        if current_time - self.last_action_time.get(username, 0) < 10:
            messagebox.showerror("Error", "You are doing that too often. Please wait.")
            return False
        self.messages.append((username, sanitized_message))
        self.last_action_time[username] = current_time
        return True

    def authenticate(self, username, password):
        if username in self.users:
            stored_password, role = self.users[username]
            if hashlib.sha256(password.encode()).hexdigest() == stored_password:
                return role
        return None

    def get_users(self):
        return [(user, role) for user, (password, role) in self.users.items()]

    def get_user_messages(self, username):
        return [(user, msg) for user, msg in self.messages if user == username]

    def get_all_messages(self):
        return self.messages

    def remove_user(self, username):
        if username in self.users:
            del self.users[username]
            return True
        return False

class RoleWindow(tk.Toplevel):
    def __init__(self, master, role, db, username):
        super().__init__(master)
        self.role = role
        self.db = db
        self.username = username
        self.title(f"{role.capitalize()} Panel")
        self.geometry("400x400")
        if role == 'admin':
            self.setup_admin_interface()
        else:
            self.setup_user_interface()

    def setup_admin_interface(self):
        tk.Label(self, text="Admin Panel").pack(pady=10)
        tk.Button(self, text="Manage Users", command=self.manage_users).pack(pady=10)
        tk.Button(self, text="View All Messages", command=self.view_all_messages).pack(pady=10)
        tk.Button(self, text="View Users", command=self.view_users).pack(pady=10)

    def setup_user_interface(self):
        tk.Label(self, text="User Panel").pack(pady=10)
        self.data_entry = tk.Entry(self, validate="key", validatecommand=(self.register(self.validate_input), '%P'), width=20)
        self.data_entry.pack(pady=10)
        tk.Button(self, text="Submit Data", command=self.submit_data).pack(pady=10)
        tk.Button(self, text="View My Messages", command=self.view_my_messages).pack(pady=10)
        tk.Button(self, text="View Users", command=self.view_users).pack(pady=10)

    def validate_input(self, new_value):
        if len(new_value) > 10:
            return False
        return True

    @PrivilegesProtection.require_admin
    def manage_users(self):
        def on_submit():
            username = entry.get()
            if self.db.remove_user(username):
                messagebox.showinfo("Success", f"User {username} removed successfully.")
                top.destroy()
            else:
                messagebox.showerror("Error", "User not found or input is too long.")

        top = tk.Toplevel(self)
        top.title("Remove User")
        tk.Label(top, text="Enter username to remove:").pack(padx=10, pady=10)
        entry = tk.Entry(top, validate="key", validatecommand=(top.register(self.validate_input), '%P'))
        entry.pack(padx=10, pady=10)
        submit_button = tk.Button(top, text="Submit", command=on_submit)
        submit_button.pack(pady=10)

    @PrivilegesProtection.require_admin
    def view_all_messages(self):
        messages = self.db.get_all_messages()
        self.show_messages(messages)

    def view_my_messages(self):
        messages = self.db.get_user_messages(self.username)
        self.show_messages(messages)

    def show_messages(self, messages):
        sanitized_messages = [(user, sanitize(msg)) for user, msg in messages]
        messages_text = '\n'.join([f"{user}: {msg}" for user, msg in sanitized_messages])
        messagebox.showinfo("Messages", messages_text)

    @PrivilegesProtection.require_admin
    def view_users(self):
        users = self.db.get_users()
        sanitized_users_info = [(sanitize(user), role) for user, role in users]
        users_info = '\n'.join([f"{user}: {role}" for user, role in sanitized_users_info])
        messagebox.showinfo("Users List", users_info)

    def submit_data(self):
        data = self.data_entry.get()
        if not data:
            messagebox.showerror("Error", "No data entered.")
            return
        if self.db.add_message(self.username, data):
            messagebox.showinfo("Success", "Your message has been saved.")
        else:
            messagebox.showerror("Error", "You are doing that too often. Please wait.")


class Application(tk.Tk):
    def __init__(self, db):
        super().__init__()
        self.db = db
        self.title("User Authentication")
        self.geometry("300x150")
        tk.Label(self, text="Username:").pack()
        self.username_entry = tk.Entry(self, validate="key", validatecommand=(self.register(self.validate_input), '%P'))
        self.username_entry.pack()
        tk.Label(self, text="Password:").pack()
        self.password_entry = tk.Entry(self, show="*", validate="key", validatecommand=(self.register(self.validate_input), '%P'))
        self.password_entry.pack()
        tk.Button(self, text="Login", command=self.login).pack(pady=20)

    def validate_input(self, new_value):
        # Ограничение максимальной длины ввода до 10 символов
        if len(new_value) > 10:
            return False
        return True

    def login(self):
        username = self.username_entry.get()
        password = self.password_entry.get()
        role = self.db.authenticate(username, password)
        if role:
            role_window = RoleWindow(self, role, self.db, username)
            role_window.grab_set()
        else:
            messagebox.showerror("Login failed", "Invalid username or password")


def setup():
    db = DataBase()
    db.add_user('admin', 'adminpass', 'admin')
    db.add_user('user1', '1234', 'user')
    db.add_user('user2', '1234', 'user')
    db.add_user('user3', '1234', 'user')
    app = Application(db)
    app.mainloop()


if __name__ == '__main__':
    setup()
