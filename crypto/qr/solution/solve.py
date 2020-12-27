from z3 import Solver, Int, Or, sat
import ast

matrix2 = ast.literal_eval(open("output.txt").read().strip())
solver = Solver()

matrix = [[ Int("{}_{}".format(x, y)) for x in range(len(matrix2) + 1)] for y in range(len(matrix2) + 1)]

for y in range(len(matrix)):
  for x in range(len(matrix)):
    solver.add(Or(matrix[y][x] == 0, matrix[y][x] == 1))

for y in range(len(matrix2)):
  for x in range(len(matrix2)):
    solver.add( matrix2[y][x] == (matrix[y][x] + matrix[y+1][x] + matrix[y][x+1] + matrix[y+1][x+1]) % 4)

r = solver.check()
if r != sat:
  print(r)
  quit()

m = solver.model()

output = ""
for y in range(len(matrix)):
  for x in range(len(matrix)):
    if m[matrix[y][x]].as_long():
      output += '\033[0;37;47m  '
    else:
      output += '\033[0;37;40m  '
  output += '\033[0m\n'

print(output)


