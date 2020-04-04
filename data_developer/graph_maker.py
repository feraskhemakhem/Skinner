import numpy
import matplotlib.pyplot as plt
import sys

angles = []
areas = []

min_angle = 361
max_angle = -1
min_area = 100000
max_area = -1
w0 = ""
w1 = ""
line_label = ""

lines = []

for i in range (0, 2):
	filename = "../data/temp_" + str(i) + ".txt"
	with open(filename, "r") as temp_file:
		angles = []
		areas = []
		w0, w1 = temp_file.readline().split(" ")
		line_label = w0 + str(", ") + w1
		for line in temp_file:
			angle_s, area_s = line.split(" ")
			angle = float(angle_s)
			area = float(area_s.strip())
			if angle < min_angle:
				min_angle = angle
			if angle > max_angle:
				max_angle = angle
			if area < min_area:
				min_area = area
			if area > max_area:
				max_area = area
			angles.append(angle) # read angle
			areas.append(area) # read area

		# plotting the points  
		c = numpy.random.rand(3,)
		plt.plot(angles, areas, color=c, linestyle='solid', linewidth = 3, marker='o', markerfacecolor=c, markersize=6, label = line_label)


# plot reference line
x = numpy.linspace(min_angle ,max_angle,2)
y = [19.9957, 19.9957]
plt.plot(x, y, color='black', linestyle='dashed', linewidth = 3, marker='o', markerfacecolor='black', markersize=6, label = 'control') 
  
# setting x and y axis range 
plt.xlim(min_angle - 0.5, max_angle + 0.5) # angles
plt.ylim(min_area - 0.1, max_area + 0.1) # area

# naming the x axis 
plt.xlabel('Angle (degrees)') 
# naming the y axis 
plt.ylabel('Area') 
  
# giving a title to my graph 
# plt.title('Combinations of v0 and v1 and Their Resulting Areas Across Different Angles') 
plt.title('Changes in Area of Mesh with Varying Values of w0 and w1 Across Different Angles') 

# provide key
plt.legend(loc="upper left")
  
# functions to save and show the plot 
savefile = '../data/' + str(sys.argv[1])
plt.savefig(savefile)
plt.show() 