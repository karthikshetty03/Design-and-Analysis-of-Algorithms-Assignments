import matplotlib.pyplot as plt

file = open("points.txt", "r")
points = file.read()
file1 = open("segments.txt", "r")
fin = file1.read()
lines = fin.split("\n")
a = points.split("\n")

i = 0
while i < len(a) - 1:
    x, y = a[i].split(" ")
    x = float(x)
    y = float(y)
    plt.scatter(x, y, color="b")
    i += 1

i = 0
del lines[len(lines) - 1]

while i < len(lines):
    x1, y1, x2, y2 = lines[i].split(" ")
    x1 = float(x1)
    y1 = float(y1)
    x2 = float(x2)
    y2 = float(y2)
    plt.plot([x1, x2], [y1, y2], "g")
    i += 1

plt.show()
