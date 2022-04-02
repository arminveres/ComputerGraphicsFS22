## Tasks:
In this exercise there are several small tasks for you:

- ~~Apply rotation, translation and scalings for a **shape** object~~
- ~~Let the **torus** and **cube** spin around one or multiple axis of your choice~~
- ~~Show the normals for the **torus** as a MultiLine Object~~
- ~~Show the **torus** with colors according to normals~~
- Calculate the normal matrix, apply it to the normals of the **torus** and compare the color output
- _(optional) apply the normal matrix of the torus also to manipulate the line object_

The example viewer is basically the same from exercise 2. However, due to some refactoring the source is easier to understand but it did not work out very well and somehow the object are now messed up. The first task for you is now to fix the scene by implementing the transformations for translation, rotation and scaling so that the objects are again in the right place. For this you have to change the Shape class to manipulate the modelmatrix of a certain shape and the GLExample class to apply the transformations:


GLExample
Shape

The final results for the tasks are shown in den doc folder. After you fixed my mess you should focus on implementing the normals both, as lines with GL_LINES and as colors of the torus. For this you can change the following files:

Multiline
Torus shaders (.vert & .frag)

The main goal is that you are able to show the difference between normals with or without an applied normalmatrix. Of course, you will need to implement a scaling transformation first to the torus, otherwise you will not see the difference. You should also make screenshots of your working transformations e.g. rotations, translations and scaling of the torus and/or the cube. It is also possible to apply transformations as animations in the GLExample::update() function for every time the update function is called.  Compare your results with the files in the _doc_ folder to see if your result is ok.

It is a good idea to read the learnopengl.com tutorials number 7 (Transformations) &  12 (Basic Lighting) to get familiar with the problem of transformations and the normal matrix.

## How to submit:
Once your code compiles and works, take screenshots showing the above mentioned things and submit the .zip file with your source code (do not include the _build_ folder) to OLAT before the deadline.

Important: this project also includes a CMake config file similar to the projects before. It should be straightforward to build the project in most of the systems using CMake. Read the assignment 1 file for instructions in case something is unclear.

## Learning targets:
- You know how to apply a transformation to a model matrix
- You now how to draw lines based objects
- You know how to apply a normal matrix to normals and you see the difference between right and wrong normals in your program
