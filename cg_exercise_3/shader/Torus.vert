#version 410 core

// TODO: update this shader so that
//       - normals are shown as colors
//       - a normal matrix is declared and is applied so that..
//       - ...normals are given to the fragment shader


layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

out vec3 fragColor;
/* out vec3 normal; */

// matrices that stay constant for the whole mesh.
uniform mat4 mvpMatrix;
uniform mat4 normMatrix;

void main()
{
  gl_Position =  mvpMatrix * vec4(vPosition, 1.f);
  // normal color
  /* fragColor = vColor; */

  // normal colors
  fragColor = vNormal;

  // normal matrix applied
  fragColor = (mat3(normMatrix) * vNormal);
}
