import qrcode

with open("flag", "r") as f:
  flag = f.read().strip()

qr = qrcode.QRCode(border=0)
qr.add_data(flag)
qr.make(fit=True)

matrix = qr.get_matrix()
matrix2 = [ [0 for _ in range(len(matrix) - 1) ] for _ in range(len(matrix) - 1)]

for y in range(len(matrix)-1):
  for x in range(len(matrix)-1):
    matrix2[y][x] = (matrix[y][x] + matrix[y+1][x] + matrix[y][x+1] + matrix[y+1][x+1]) % 4

print(matrix2)
