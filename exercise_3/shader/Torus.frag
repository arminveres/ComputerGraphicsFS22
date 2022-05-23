#version 410 core


// TODO: update this shader so that
//       - draw incoming normals from the vertex shader


in vec3 fragColor;
/* in vec3 normal; */
out vec3 out_color;
/* out vec3 out_normal; */


void main()
{
  // ... uncomment this for color
  out_color = fragColor;
  // ... uncomment this for color according to normals
  /* out_normal = in_normal; */
}
