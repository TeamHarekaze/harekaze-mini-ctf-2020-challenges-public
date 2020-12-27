from math import gcd

exec(open("output.txt").read())

p = gcd(c2 + c3, n)
q = n // p
d = pow(65537, -1, (p-1)*(q-1))
flag = pow(c1, d, n)

print(bytes.fromhex(hex(flag)[2:]))
