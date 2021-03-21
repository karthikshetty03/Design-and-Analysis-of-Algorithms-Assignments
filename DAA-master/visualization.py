import matplotlib.pyplot as plt

my_file = open("my_file2.txt", "r")
content = my_file.read()
plt.title(content)


my_file = open("my_file1.txt", "r")
content = my_file.read()
content_rect = content.split("\n")
del(content_rect[len(content_rect)-1])
print(content_rect)

i = 0
while i < len(content_rect)-1:
  x1, y1 = content_rect[i].split(" ")
  x2, y2 = content_rect[i+1].split(" ")
  x1 = int(x1)
  x2 = int(x2)
  y1 = int(y1)
  y2 = int(y2)
  plt.plot([x1, x2], [y1, y1], "#FF69B4")
  plt.plot([x1, x2], [y2, y2], "#FF69B4")
  plt.plot([x1, x1], [y1, y2], "#FF69B4")
  plt.plot([x2, x2], [y1, y2], "#FF69B4")
  i+=2


my_file = open("my_file.txt", "r")
content = my_file.read()
content_list = content.split("\n")
del(content_list[len(content_list)-1])
print(content_list)

#contour plots
i=0
while i < len(content_list)-1:
  x1, y1 = content_list[i].split(" ")
  x2, y2 = content_list[i+1].split(" ")
  x1 = int(x1)
  x2 = int(x2)
  y1 = int(y1)
  y2 = int(y2)
  print(x1, y1)
  print(x2, y2)
  plt.plot([x1, x2], [y1, y2], "g")
  print()
  i+=2

plt.ylabel('some numbers')
plt.show()
