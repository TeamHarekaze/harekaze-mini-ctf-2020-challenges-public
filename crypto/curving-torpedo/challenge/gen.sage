factor_lower = 2
factor_upper = 10**10
prime_lower = 2**360
prime_upper = 2**512

cnt = 0
while True:
    p = 1
    factors = []
    while p < prime_upper:
        factor = randint(factor_lower, factor_upper)
        factors.append(factor)
        p = p*factor

        if prime_lower < p < prime_upper and p % 3 == 2 and is_prime(p-1):
            p = p-1
            a = randint(2, p-1)
            b = 0
            EC = EllipticCurve(GF(p), [a, b])
            g = EC.random_point().xy()

            print("p={}".format(p))
            print("a={}".format(a))
            print("b={}".format(b))
            print("q={}".format(EC.order()))
            print("gx={}".format(g[0]))
            print("gy={}".format(g[1]))

            quit()
