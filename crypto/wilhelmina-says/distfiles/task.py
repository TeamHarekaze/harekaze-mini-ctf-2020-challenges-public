from Crypto.Util.number import getStrongPrime
import random

p = getStrongPrime(512)

with open("flag", "rb") as f:
  flag = int.from_bytes(f.read().strip(), "big")
  assert flag < p

t = flag.bit_length()
n = 5
k = 350

xs = [random.randint(2, p-1) for _ in range(n)]
ys = [x * flag % p for x in xs]
zs = [(y >> k) << k for y in ys]

print(f"{t=}")
print(f"{p=}")
print(f"{xs=}")
print(f"{zs=}")
