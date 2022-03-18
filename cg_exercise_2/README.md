# OpenGL - Exercise 2

## Subject / goals

Understand how 3D objects are defined and how you create them.


## Tasks:
Generate a mesh with the shape describing a cuboid bent along a specific function (see 'Additional Information' below).

<!-- In this exercise, you have to generate a mesh with the shape of a torus. Specifically, you need to write the code to compute all the vertices and faces of the mesh. Each vertex requires a 3D position value, a 3D normal vector and a RGB color value. Each face (or triangle) requires a triplet with the indices of its vertices and a 3D normal vector. -->
<!---->
<!-- The source code of this project is the viewer from the first exercises extended with some functions to help you visualize the objects. An incomplete Torus class has been created already. Specifically you need to complete code pieces in the following classes: -->
<!---->
<!-- - GLExample.cpp -->
<!-- - Torus.cpp -->
<!---->
<!---->
<!-- Example screenshots of the result can be seen in the doc folder. You are free to color you torus however you want. -->

## How to submit:

<!-- Once your code compiles and works, create a .zip file with the source code (please include only the source files, not the build folder) and upload it to OLAT together with a screenshot of the rendering window working in your computer. -->
<!---->
<!-- Important: Similar to the first exercise this project includes a CMake config file to generate the building scripts for different build systems. You do this the same way as for exercise 1, so it should be straightforward (now) to build the project using CMake.  -->

Once your code compiles and works, create a .zip file with the source code (please include only the source files, the src/ folder) and upload it to OLAT together with a screenshot of the rendering window working on your computer.

## Learning targets:

- You are able to procedurally generate a simple object with triangles

- You know how to enable/disable face culling in OpenGL

- You know how to change the clockwise and counterclockwise ordering of triangle geometry in OpenGL

- You know how to change the culling mode (frontface vs. backface culling in OpenGL)

- You know how to render a model in wireframe mode

- You know the difference between vertex shader fragment shader

## Additional Information

The cudoid lies on the XY-plane. The functions describing the cuboid are the following: [ y = x^2 + x, y = x^3 - 1, y = x^3 + 0.5*x ]. Pick the one at the index which equals "last two digits of your legi-number % 3". The cuboid should describe the function on a finite interval (you can define one yourself or just pick [-2,2]). Introduce a variable to steer the number of vertices/faces of the object.

You need to write the code to compute all the vertices and faces of the mesh. Each vertex requires a 3D position value and a RGB color value. Each face (or triangle) requires a triplet with the indices of its vertices. To do this, write your code in the Cuboid class.

In addition, the GLExample class defines the camera matrix. It is positioned in a way such that all the functions are completely visible in the interval [-2,2]. You can try to play with the position to get a different/better image of your object.

To get familiar with face culling, vertex/index ordering, wireframe mode etc. go to GLExample::render().

Example screenshots of the result can be seen in the doc folder. You are free to color your object however you want.
