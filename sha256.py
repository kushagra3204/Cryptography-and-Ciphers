import hashlib

def mod_exp(x, n, m):
    res = 1
    while n:
        if n & 1:
            res = (res * x) % m
        n //= 2
        x = (x * x) % m
    return res

def extended_euclid_solve(a, b, r, t1, t2):
    q = a // b
    r = a % b
    if r == 0:
        return t2
    t = t1 - (t2 * q)
    return extended_euclid_solve(b, r, a % b, t2, t)

def extended_euclid(b, n):
    ans = extended_euclid_solve(n, b, 0, 0, 1)
    if ans < 0:
        ans += n
    return ans

def generator(p):
    arr = [False] * p
    i = 2
    while True:
        for j in range(1, p):
            g = mod_exp(i, j, p)
            if arr[g]:
                break
            else:
                arr[g] = True
                if j == p - 1:
                    return i
        i += 1
        arr = [False] * p

def sha256_hash(message):
    return int(hashlib.sha256(message.encode()).hexdigest(), 16)

def main():
    p, m, x, r = 43, 14, 7, 26
    g = generator(p)
    y = mod_exp(g, x, p)  # y = (g^x)mod(p)
    c1 = mod_exp(g, r, p)  # c1 = (g^r)mod(p)
    h = sha256_hash("Hello, World!")  # Example message
    c2 = (mod_exp(y, r, p) * h) % p  # c2 = ((y^r)*hash(message))mod(p)
    print("Encryption:")
    print("c = (", c1, ",", c2, ")")
    plain_text = (c2 * extended_euclid(mod_exp(c1, x, p), p)) % p  # m = (c2/(c1^x))mod(p)
    print("Decryption:")
    print("Message Hash (SHA-256):", h)
    print("Decrypted hash (Plain text):", plain_text)

if __name__ == "__main__":
    main()
