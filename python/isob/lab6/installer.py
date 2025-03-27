from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding
import tkinter as tk
from tkinter import messagebox, scrolledtext
import subprocess
import hashlib
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization

private_key = rsa.generate_private_key(
    public_exponent=65537,
    key_size=2048,
)

public_key = private_key.public_key()

public_pem = public_key.public_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PublicFormat.SubjectPublicKeyInfo
)

with open('/python/isob/lab4_5/key.txt', 'wb') as f:
    f.write(public_pem)

def sign_data(data):
    signature = private_key.sign(
        data.encode(),
        padding.PSS(
            mgf=padding.MGF1(hashes.SHA256()),
            salt_length=padding.PSS.MAX_LENGTH
        ),
        hashes.SHA256()
    )
    return signature


def verify_signature(data, signature):
    try:
        public_key.verify(
            signature,
            data.encode(),
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            hashes.SHA256()
        )
        return True
    except:
        return False


def compile_project():
    try:
        subprocess.run(["pyinstaller", "--onefile", "--windowed", "main.py"], check=True)
        messagebox.showinfo("Success", "Project compiled successfully.")
        window.quit()
    except subprocess.CalledProcessError:
        messagebox.showerror("Error", "Failed to compile the project.")


def check_license():
    license_key = license_entry.get("1.0", "end").strip()
    hashed_key = hashlib.sha256(license_key.encode()).hexdigest()
    correct_hash = "68166df26b13863846886fe64a4ed69ffcc1b3e4da4ff1f694de24aaad63f64f"

    if hashed_key == correct_hash:
        signature = sign_data(license_key)
        if verify_signature(license_key, signature):
            compile_project()
        else:
            messagebox.showerror("Error", "Signature verification failed.")
    else:
        messagebox.showerror("Error", "Invalid license key.")


window = tk.Tk()
window.title("License Key Input")
window.geometry("400x200")

label_license = tk.Label(window, text="Enter your license key:")
label_license.pack()

license_entry = scrolledtext.ScrolledText(window, height=5, width=40)
license_entry.pack()

check_button = tk.Button(window, text="Check License", command=check_license)
check_button.pack()

window.mainloop()
