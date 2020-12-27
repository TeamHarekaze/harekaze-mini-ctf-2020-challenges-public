from Crypto.Util.number import getStrongPrime, getRandomRange

with open("flag", "rb") as f:
  flag = int.from_bytes(f.read(), "big")

p = getStrongPrime(512)
q = getStrongPrime(512)
n = p * q
phi = (p-1)*(q-1)
e = 65537
c1 = pow(flag, e, n)
c2 = pow(p + q, e, n)
c3 = pow(p - q, e, n)

print(f"{n=}")
print(f"{e=}")
print(f"{c1=}")
print(f"{c2=}")
print(f"{c3=}")

