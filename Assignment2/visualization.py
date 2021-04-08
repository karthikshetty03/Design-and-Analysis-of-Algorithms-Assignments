import matplotlib.pyplot as plt
import numpy as np

# my_file = open("title.txt", "r")
# content = my_file.read()
# plt.title(content)

my_file = open("segments.txt", "r")
content = my_file.read()
content_rect = content.split("\n")

i = 0
while i < len(content_rect) - 1:
    x1, y1, x2, y2 = content_rect[i].split(" ")
    x1 = float(x1)
    x2 = float(x2)
    y1 = float(y1)
    y2 = float(y2)
    x_values = [x1, x2]
    y_values = [y1, y2]
    plt.plot(x_values, y_values)
    i += 1

my_file = open("points.txt", "r")
content = my_file.read()
content_rect = content.split("\n")

i = 0
del lines[len(lines) - 1]

while i < len(content_rect) - 1:
    x1, y1 = content_rect[i].split(" ")
    x1 = float(x1)
    y1 = float(y1)
    a.append([x1, y1])
    i += 1

plt.plot(*zip(*a), marker="o", color="b", ls="")
plt.show()
