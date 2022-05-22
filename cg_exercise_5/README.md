Tasks:
In this exercise we will take a closer look at mapping. The tasks are:

- Apply texture mapping to our cube and torus objects.
- Apply a light map to the cube and the torus object.
- Combine the texture mapping with the previously implemented blinn-phong illumination model.
- (optional) apply gamma correction in the fragment shaders to enhance your results (learnopengl Chapter 33 "Gamma Correction").

The example viewer is based on the result of exercise 4 but has only one cube in the background and the torus in the front. To implement texture mapping and your light maps you have to update the following files:

GLExample
Cube & Torus classes
Cube & Torus Shaders
Texture

What to do first. For me personally it is always easiest to start from a "working state" to the next "working state" of your application. In this case the best way to start is to set the texture coordinates for the cube (fill up the texCoords array) and try to output them as color output in the cube shader. If you see the color output then try to load a texture. For this you have to fill in the rest of the code in the texture class. This can be tricky and you might have to figure out what kind of texture format and data type you are using. The image data is loaded from the files with the freeimage library. You don't need to change this code part, but you might have to set debug points to check how your incoming data looks like (32 bits p pixels etc.). After you create a texture handle, set opengl texture parameteres and loaded the image data to opengl you have to update the rendering code for the cube on the CPU side (binding textures, setting uniforms) and in the shaders (declaring sampler, apply texture function and apply the color to the object). When you color texture works, try the same thing to apply a light map texture. You should be able to just load a second texture and update the rendering code for this.

After you have done this for the cube, try to make the same for the torus as well. For the result image I used texture coordinates from 0.0 to 4.0 for the torus object and used the GL_MIRROR parameter for the texture but you can achieve the same results also with other coordinates/parameter combinations.

Texturing is happening in the fragment shader but it will take some time to understand how the loading of a texture work so be prepared to check the opengl specification for the commands your are using. Also, if you haven't done so already I would advice you to read and follow the learnopengl.com Chapter 6 (Textures) and Chapter 14 (Light maps). The implementation of the example is similar but of course has to be adapted to your needs.

The final results for the tasks are shown in den doc folder. Compare your results with the files in the _doc_ folder to see if your result is correct. Make screenshots of all your results during the texturing process (texture coordinates, texture only, texture and light map applied) and upload them to OLAT.

How to submit:
Once your code compiles and works, take screenshots showing the above mentioned things and submit the .zip file with your source code (do not include the _build_ folder) to OLAT before the deadline.

How to get it running:

This example has an additional libary named freeimage. Under OSX you can install this library with homebrew:

brew install freeimage

Under windows you should be able to use it out of the box because it is provided with the project. In case you have problems with this please don't hesitate to write me immediately.

Important: this project also includes a CMake config file similar to the projects before. besides the freeimage library it should be straightforward to build the project in most of the systems using CMake. Read the assignment 1 file for instructions in case something is unclear.

Learning targets:

- You know how to load a texture with OpenGL
- You know how to apply texture mapping in a shader program
- You know how to apply a light map to your blinn-phong model
- You know the difference between GL_NEAREST and GL_LINEAR when applied to texture parameters
- You know the difference between GL_CLAMP_TO_EDGE, GL_REPEAT, GL_MIRROR_REPEAT
- You know how to set uniforms for samplers in GLSL shaders
