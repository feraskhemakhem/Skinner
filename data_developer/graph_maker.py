import numpy
import matplotlib.pyplot as plt
import sys

angles = []
areas = []

min_angle = 361
max_angle = -1
min_area = 100000
max_area = -1

with open("../data/temp.txt", "r") as temp_file:
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
plt.plot(angles, areas, color='green', linestyle='solid', linewidth = 3, marker='o', markerfacecolor='blue', markersize=6) 
  
# setting x and y axis range 
plt.xlim(min_angle - 1, max_angle + 1) # angles
plt.ylim(min_area - 1, max_area + 1) # area

# naming the x axis 
plt.xlabel('Angle (degrees)') 
# naming the y axis 
plt.ylabel('Area') 
  
# giving a title to my graph 
plt.title('Linear Interpolation') 
  
# functions to save and show the plot 
savefile = '../data/' + str(sys.argv[1])
plt.savefig(savefile)
plt.show() 