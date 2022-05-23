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
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 ambientTerm;
uniform vec3 diffuseTerm;
uniform vec3 specularTerm;

void main()
{
  // Output color = color specified in the vertex shader,
  // interpolated between all 3 surrounding vertices
  color = objectColor;
  //color = normal;

  /**
   *TODO: add there code for phong lighting
   */
  /*
  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  vec3 ambient = ambientTerm * objectColor;
  vec3 diffuse = diffuseTerm * max(dot(norm, lightDir), 0.0) * objectColor;

  int shininess = 32;
  float spec = pow(max(dot(viewDir, reflectDir), 0.f), shininess);
  vec3 specular = specularTerm * spec * objectColor;

  color = (ambient + diffuse + specular) * objectColor;
  // End TODO
  */
}
