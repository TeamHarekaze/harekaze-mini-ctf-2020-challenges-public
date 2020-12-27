def recover_p(points):
    xs = []
    for i in range(len(points)):
        xs.append(points[i][0])

    xy = []
    for i in range(len(points)):
        xy.append(points[i][0]**3  - points[i][1]**2 )


    diffs = []
    for i in range(len(xy)-1):
        diffs.append(xy[i] - xy[i+1])

    pk = []
    for i in range(len(diffs)-1):
        pk.append(diffs[i] * (xs[i+1] - xs[i+2]) - diffs[i+1] * (xs[i] - xs[i+1]))

    return gcd(pk) # p or p * small

def pohlig_hellman(P, Q, order, limit=10**10):
    factors = [f[0]**f[1] for f in order.factor(limit=limit) if f[0] <= limit]
    bs = []
    mods = []
    M = 1
    for f in factors:
        k = order//f
        Pi = k * P
        Qi = k * Q
        b = discrete_log(Qi, Pi, operation="+")
        bs.append(b)
        mods.append(f)
        M *= f

    return CRT(bs, mods), M

points = []
with open("output.txt") as f:
    for line in f.readlines():
        points.append(eval(line.strip()))

p = recover_p(points)
a = (points[0][1] ** 2 - points[1][1] ** 2 - points[0][0] ** 3 + points[1][0] ** 3) * inverse_mod(points[0][0] - points[1][0], p) % p
b = (points[0][1] ** 2 - points[0][0] ** 3 - points[0][0] * a) % p

EC = EllipticCurve(GF(p), [a, b])
order = EC.order()

P = EC(points[0])
Q = EC(points[1])

x, _ = pohlig_hellman(P, Q, order=order)
print(bytes.fromhex(hex(x)[2:]))
