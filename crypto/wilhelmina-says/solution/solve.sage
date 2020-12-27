import ast

with open("output.txt") as f:
  t = ast.literal_eval(f.readline().strip().split("=")[1])
  p = ast.literal_eval(f.readline().strip().split("=")[1])
  xs = ast.literal_eval(f.readline().strip().split("=")[1])
  zs = ast.literal_eval(f.readline().strip().split("=")[1])

n = len(xs)
k = 350

M = matrix(ZZ, n+2, n+2)
M.set_block(0, 0, p * matrix.identity(n))
M.set_block(n, 0, matrix(ZZ, 1, n, xs))
M.set_block(n+1, 0, matrix(ZZ, 1, n, zs))
M[n,n] = 1
M[n+1,n+1] = 2^k

B = M.LLL()
flag = abs(B[0][n])

print(bytes.fromhex(hex(flag)[2:]))
