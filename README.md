# Skinner

This branch uses the bone as a the middle of the joint, as opposed to acting as the pivot point.

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
./A6 [NUM BONES] [NUM VERTICES WIDE] [NUM VERTICES LONG] [RECT WIDTH] [RECT LENGTH] [DEFORM FACTOR]
`

This input will change as the inputs are changed, and as the project is developed into a unique project.

Additional controls:
* To scale, hold cntrl + mouse 1 + move mouse
* To translate, hold shift + mouse 1 + move mouse
* To rotate, hold mouse 1 + move mouse
* Press 'w' to toggle wireframe (disabled by default)
* Press 'b' to toggle bones (disabled by default)
* Press 'c' to toggle culling (enabled by default)

Notes on inputs:
* All numeric values must be natural number (not including 0)