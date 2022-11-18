import os
import numpy as np
from PIL import Image

# img = Image.open('sprites.png')
# ima = np.asarray(img)
# f = open('teste.ppm', 'r')
# pixels = f.readlines()
# pixels = np.zeros((96, 32, 3), dtype=np.uint8)
# image = Image.fromarray(pixels)

# image.save('iamge.'+'png');

# f = open('teste.ppm', 'w')
# for i in range(0, len(ima)):
# 	for j in range(0, len(ima[i])):
# 		for pixel in ima[i][j]:
# 					# print(pixel)
# 					f.write(str(pixel)+',\n')


file = str(input("Type the file name: "))
# file = 'All_Textures.ppm'
filename, ext = os.path.splitext(file)
f = open(file)
lines = f.readlines()

# # Delete first 4 lines
# for i in range(0, 4):
# 	lines.pop(0);

# Write to file
f = open(file, 'w')
f.write("int "+filename+"[] = {\n")

for i in range(0, len(lines)):
	line = lines[i].replace('\n', '')

	# Reach final -> close array
	if(i == len(lines)-1):
		f.write(line+'\n'+'};')
		break
	f.write(line+',\n')

