import hashlib

key = "12131411"
hashed_key = hashlib.sha256(key.encode()).hexdigest()
print("Generated hash:", hashed_key)
