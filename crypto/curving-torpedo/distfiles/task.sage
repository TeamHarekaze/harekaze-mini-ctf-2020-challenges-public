from params import p, a, b

EC = EllipticCurve(GF(p), [a, b])
order = EC.order()

with open("flag", "rb") as f:
    flag = int.from_bytes(f.read().strip(), "big")
    assert flag < order

G = EC.random_point()

print(G.xy())
print((flag * G).xy())

for i in range(10):
    x = randint(2, order-1)
    print((x * G).xy())


