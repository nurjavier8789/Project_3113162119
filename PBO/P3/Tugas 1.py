class GameObject:
    def __init__(self, symbol, x, y):
        self.symbol = symbol
        self.x = x
        self.y = y

    def print_object(self):
        print(self.symbol, self.x, self.y)

class Grid:
    def __init__(self, xs, ys):
      self.xs = xs
      self.ys = ys
      self.board = []

      for i in range(xs):
          row = []
          for j in range(ys):
              row.append("-")
          self.board.append(row)

    def check_bounds(self, x, col):
      if x < 0 or x >= self.xs:
        return False
      elif col < 0 or col >= self.ys:
        return False
      else:
        return True

    def display(self):
      for x in self.board:
          print(" ".join(x))

    def place_object(self, object):
      if not self.check_bounds(object.x, object.y):
        print("Out of bounds!")
        return
      self.board[object.y][object.x]=object.symbol

    def move_object(self, oldObject, newX, newY):
      if not self.check_bounds(oldObject.x, oldObject.y):
        print("Out of bounds!")
        return
      if not self.check_bounds(newX, newY):
        print("Out of bounds!")
        return
      self.board[oldObject.y][oldObject.x] = "-"

      self.board[newY][newX]=oldObject.symbol

# Here!

grid = Grid(10,10)
print("Current grid size: " + str(grid.xs) + "x" + str(grid.ys) + "\nWith the anchor on top-left\n")

Liz = GameObject("L", 1, 4)
print("Initial Liz position: " + str(Liz.x + 1) + ", " + str(Liz.y + 1))
grid.place_object(Liz)
grid.display()
print("======================")

print("Changing position into: " + str(4 + 1) + ", " + str(5 + 1))

print("======================")
grid.move_object(Liz, Liz.x, Liz.y)
Liz.x = 4
Liz.y = 5
print("Current Liz position: " + str(Liz.x + 1) + ", " + str(Liz.y + 1))
grid.display()
# print("======================")

# print("Changing position into: " + str(10 + 1) + ", " + str(5 + 1))

# print("======================")
# grid.move_object(Liz, GameObject(Liz.symbol, 10, 5))
# print("Current Liz position: " + str(Liz.x + 1) + ", " + str(Liz.y + 1))
# grid.display()