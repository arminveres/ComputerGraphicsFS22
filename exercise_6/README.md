Tasks:
In this exercise we will take a closer look at normal mapping. The tasks are:

- Apply normal mapping to our demo objects.
- Combine the normal mapping with the previously implemented blinn-phong illumination model.

The example viewer is based on the result of exercise 5. To implement normal mapping you have to update the following files:

GLExample
Cube & Torus classes
Cube & Torus Shaders
Texture & Multiline (eventually for debugging)

Normal mapping is another really nice light effect which enhances the surface roughness. In face it is a trick, because we use a texture with normal information to update the shading of an object without really changing the geometry. So the basic idea is that you load an additional texture with normal information, make this texture accessible in the fragment shader and use this normal information instead of the usual vertex normals. The major problem is to think about what happens to your normals which are stored in the texture when mapping them on the object. Of cource these normals have to change because the texture is defined in a 2D Space and when these normals are mapped on the object they have to point in other 3D directions (even if it is the same normal used from the texture).

This problem leads to the generation of a TBN matrix (tagent, bitangent, normal). The learnopengl.com Chapter 35 (Normal Mapping) has a nice introduction to this topic. The implementation of the example is really similar but you can not just copy over the source. Generating the tangents for the torus is tricky and might require you to use the MultiLine class for debugging (you can add lines for the tangents for example). Try to first introduce Normal Mapping for the cube and then for the torus.
 
The final results for the tasks are shown in den doc folder. Compare your results with the files in the _doc_ folder to see if your result is correct. Make screenshots of all your results during the normal mapping process and upload them to OLAT.

How to submit:
Once your code compiles and works, take screenshots showing the above mentioned things and submit the .zip file with your source code (do not include the _build_ folder) to OLAT before the deadline.

Important: this project also includes a CMake config file similar to the projects before. It should be straightforward to build the project in most of the systems using CMake. Read the assignment 1 and/or 5 file for instructions in case something is unclear.

Learning targets:
- You know how to load do normal mapping with OpenGL
- You know how to generate a tangents, bitangents and the TBN matrix
- You know how to apply normal mapping to your blinn-phong model