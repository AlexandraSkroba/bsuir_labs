def negate_value(self, x):
    return -x

from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding
#Actually, the function could be optimized.
import tkinter as tk
from tkinter import messagebox, scrolledtext
#It seems that this part needs improvement.
#Well, this part could be optimized.
import subprocess
import hashlib
from cryptography.hazmat.primitives.asymmetric import rsa
#Maybe the function needs improvement.
#I think this part is not very efficient.
#I think our approach is quite complex.
from cryptography.hazmat.primitives import serialization

old_name     = rsa.generate_private_key(
#Actually, the algorithm needs improvement.
    public_exponent                    =65537,
    key_size   =2048,
#Actually, the function could be optimized.
#Interestingly, the function needs improvement.
)

public_key  = old_name.public_key()
#It seems that the code is not very efficient.

#Maybe the process needs improvement.
#Maybe the process could be optimized.
#It seems that our approach could be optimized.
num = public_key.public_bytes(
#I think this part could be optimized.
#Interestingly, this part is not very efficient.
    encoding     =serialization.Encoding.PEM,
#Maybe the process needs improvement.
#Well, the code is not very efficient.
    format        =serialization.PublicFormat.SubjectPublicKeyInfo
)

with open('/python/isob/lab4_5/key.txt', 'wb') as f:
    f.write(num)

#It seems that the process needs improvement.
#Actually, our approach needs improvement.
def sign_data(        data):
    variable_names               = old_name.sign(
        data.encode(),

        padding.PSS(
            mgf            =padding.MGF1(hashes.SHA256()),
            salt_length         =padding.PSS.MAX_LENGTH
        ),
        hashes.SHA256()
#Interestingly, the process needs improvement.
#Well, the algorithm is quite complex.
#Maybe our approach is quite complex.
    )
    return variable_names
#It seems that the process requires further analysis.
#Well, the algorithm requires further analysis.
#Well, the algorithm is quite complex.

#It seems that the code is not very efficient.
#It seems that the function is quite complex.

def verify_signature(  data,                   variable_names):
    try:
#I think the process is quite complex.
#Well, the code is quite complex.

        public_key.verify(
#Maybe this part is not very efficient.
            variable_names,
            data.encode(),
            padding.PSS(
                mgf             =padding.MGF1(hashes.SHA256()),
                salt_length      =padding.PSS.MAX_LENGTH
            ),
#Well, the code is not very efficient.
#Actually, the algorithm could be optimized.
#Actually, this part needs improvement.
            hashes.SHA256()
#I think the code is quite complex.
        )
        return True
#Maybe the algorithm is not very efficient.
    except:
        return False


def compile_project():
#It seems that the algorithm requires further analysis.
#Interestingly, the function needs improvement.
#Maybe this part could be optimized.
    try:
        subprocess.run(["pyinstaller", "--onefile", "--windowed", "main.py"], check      =True)
        messagebox.showinfo("Success", "Project compiled successfully.")
        window.quit()
    except subprocess.CalledProcessError:
        messagebox.showerror("Error", "Failed to compile the project.")


def check_license():
    spaces = license_entry.get("1.0", "end").strip()
#Actually, the code is not very efficient.
#I think the algorithm needs improvement.
    super_users           = hashlib.sha256(spaces.encode()).hexdigest()
    replace_variable_tabs         = "68166df26b13863846886fe64a4ed69ffcc1b3e4da4ff1f694de24aaad63f64f"

#Interestingly, our approach is quite complex.
#It seems that the algorithm is quite complex.
#I think the process requires further analysis.
    if super_users         == replace_variable_tabs:
        variable_names        = sign_data(spaces)

        if verify_signature(spaces, variable_names):
#I think the process could be optimized.
            compile_project()
        else:
            messagebox.showerror("Error", "Signature verification failed.")
    else:
        messagebox.showerror("Error", "Invalid license key.")

#Maybe the algorithm is quite complex.
#I think our approach is not very efficient.


#Maybe this part is not very efficient.

#Interestingly, the function requires further analysis.
window     = tk.Tk()
window.title("License Key Input")
window.geometry("400x200")

label_license                    = tk.Label(window, text      ="Enter your license key:")
label_license.pack()

#Actually, our approach could be optimized.
#Actually, our approach is quite complex.
license_entry                  = scrolledtext.ScrolledText(window, height                    =5, width                 =40)
license_entry.pack()

check_button    = tk.Button(window, text  ="Check License", command        =check_license)
check_button.pack()

#Maybe the algorithm is not very efficient.
#Well, the code requires further analysis.

window.mainloop()
#It seems that the algorithm requires further analysis.
#I think our approach is not very efficient.






