Tasks:

In this exercise, you have to generate a mesh with the shape of a torus. Specifically, you need to write the code to compute all the vertices and faces of the mesh. Each vertex requires a 3D position value, a 3D normal vector and a RGB color value. Each face (or triangle) requires a triplet with the indices of its vertices and a 3D normal vector.

The source code of this project is the viewer from the first exercises extended with some functions to help you visualize the objects. An incomplete Torus class has been created already. Specifically you need to complete code pieces in the following classes:

- GLExample.cpp
- Torus.cpp


Example screenshots of the result can be seen in the doc folder. You are free to color you torus however you want.

How to submit:

Once your code compiles and works, create a .zip file with the source code (please include only the source files, not the build folder) and upload it to OLAT together with a screenshot of the rendering window working in your computer.

Important: Similar to the first exercise this project includes a CMake config file to generate the building scripts for different build systems. You do this the same way as for exercise 1, so it should be straightforward (now) to build the project using CMake. 

Learning targets:

- You are able to procedurally generate a simple object with triangles

- You know how to enable/disable face culling in OpenGL 

- You know how to change the clockwise and counterclockwise ordering of triangle geometry in OpenGL 

- You know how to change the culling mode (frontface vs. backface culling in OpenGL)

- You know how to render a model in wireframe mode

- You know the difference between vertex shader fragment shader
