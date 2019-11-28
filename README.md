# Skinner

This project is based on Assignment 6 of Dr. Shinjiro Sueda's (@sueda) CSCE 441 Computer Graphics class at Texas A&M University. It builds
off the concept of Linear Blend Skinnning (LBS) and will allow for Dual Quaternion Skinning (DQS) rendering in 2D. The goal of this project
is to familiarize with the differences in LBS and DQS in 2D and their differences in computational cost and output.

To compile the project:

 ```
 cd build
 make -j4
```

The project currenntly takes the following input to run:

`
./A6 [NUM BONES] [NUM VERTICES WIDE] [NUM VERTICES LONG] [RECT WIDTH] [RECT LENGTH] [ANIMATED? (T or F)]
`

These inputs respond to the folder where the shaders exist, the object being skinned, attachment file, and skeleton file. This input will
change as the inputs are changed, and as the project is developed into a unique project.

Notes on inputs:
* NUM BONES must be greater than 1
* For odd values of NUM VERTICES, it will be replaced with the next largest even value
* RECT WIDTH and RECT LENGTH must be positive

In addition, to control the camera, use the following actions:

* To scale, hold cntrl + move mouse
* To translate, hold shift + move mouse
* To rotate, just move mouse