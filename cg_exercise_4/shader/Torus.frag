#version 410 core

/* TODO: update your vertex shader so that...
 *      ...it emits the color for phong illumination
 *      ...it emits the color from the vertex shader in case you do gourand shading there
 */

in vec3 objectColor;
in vec3 normal;
in vec3 fragPos;

// Ouput data
out vec3 color;

/* TODO: fill these structs with values from outside the shader similar
 *      to your matric variables
 */
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 ambientTerm;
uniform vec3 diffuseTerm;

void main()
{
  // Output color = color specified in the vertex shader,
  // interpolated between all 3 surrounding vertices
  color = objectColor;
  //color = normal;

  /* TODO: add there code for phong lighting
  *
  */
  vec3 lightDir = normalize(lightPos - fragPos);
  vec3 norm = normalize(normal);

  vec3 ambient = ambientTerm * objectColor;
  vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;
  color = (ambient + diffuse) * objectColor;
  // End TODO
}
