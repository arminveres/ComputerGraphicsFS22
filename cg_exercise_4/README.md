Tasks:
In this exercise we will take a closer look at lighting. The tasks are:

- [ ] Apply the **Phong** lighting model with ambient, diffuse and specular term to
      the cube objects and the torus. Use for this the **Phong Shading** model.
- [ ] If you are done with phong illumination try to render your objects with
      Gourand Shading.
- [ ] (optional) Apply Blinn-Phong Illumination to your scene and make a screenshot
      in comparison to phong illuminations.

The example viewer is the similar to the one in exercise 3 but with 4 scaled cubes
in the background and the torus in the front.

To implement Phong lighting you have to update the following files:

GLExample
Cube & Torus Shaders

Try to first implement the different terms of the light (ambient, diffuse and specular)
and then combined. Remember, that in the shader it is hard to debug because you
can't set breakpoints. This means that usually you have to use the color output
of the fragment shader for debugging purposes (e.g. outputting the normals as colors).
In general you should be able to follow the learnopengl.com Chapters "Basic Lighting"
and "Advanced Lighting" (for the optional task).

The biggest part of this exercise will happen in the shader, so be prepared to write shader code and make sure that you have read the learnopengl.com Chapter 5 (Shaders) in case you haven't done this already. On the application side (GLExample) the main focus lies on how to set up the light information and fill the uniform structures for the shader.

To prove that you understood the code you will to provide the screenshots above with an ambient and diffuse light color according to the first 6 digits of your legi number (e.g. 11-789-5XX). You can use pairs of two digits to express one color channel but be aware that you might have to rescale the values.

The final results for the tasks are shown in den doc folder (Light values are here white, all 1.0). Compare your results with the files in the _doc_ folder to see if your result is correct. Make screenshots of all your results during the phong lighting process (ambient only, diffuse & ambient illumination, specular and phong lighting) and upload them to OLAT. For the gourand shading it is only required to upload a screenshot showing the difference between gourand shading and phong shading (see lecture slides for the difference between phong lighting and phong shading vs. gourand shading).

How to submit:
Once your code compiles and works, take screenshots showing the above mentioned things and submit the .zip file with your source code (do not include the _build_ folder) to OLAT before the deadline.

Important: this project also includes a CMake config file similar to the projects before. It should be straightforward to build the project in most of the systems using CMake. Read the assignment 1 file for instructions in case something is unclear.

Learning targets:

- You know how to apply basic phong lighting to a scene in the shader
- You know the difference between gourand shading and phong shading
- You know how to set uniforms to a shader
