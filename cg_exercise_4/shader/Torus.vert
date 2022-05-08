#version 410 core

/* TODO: update your vertex shader so that...
 *      ...it emits all necessary information to the fragment shader for phong illumination
 *      ...it emits the color in case you do gourand shading
 */

// Input vertex data
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

// Output data will be interpolated for each fragment.
// Tip: Try to use the flat modifier to make color associations of a fragment visible for debugging. 
out vec3 objectColor;
out vec3 normal;
out vec3 fragPos;

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

/* TODO: additional variables
 *
 */
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 ambientTerm;
uniform vec3 diffuseTerm;
uniform vec3 specularTerm;

void main()
{
  normal = mat3(transpose(inverse(modelMatrix))) * vNormal;
  // Output position of the vertex, in clip space : MVP * vPosition
  gl_Position = mvpMatrix * vec4(vPosition, 1);
  // The color of each vertex will be interpolated
  // to produce the color of each fragment
  // ... uncomment this for color
  objectColor = vColor;
  // ... uncomment this for color according to normals
  //objectColor = vNormal;

  /* TODO: add there code for gourand shading
  *
  */

  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(lightPos - fragPos);
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  vec3 ambient = ambientTerm * objectColor;
  vec3 diffuse = diffuseTerm * max(dot(norm, lightDir), 0.0) * objectColor;

  int shininess = 5;
  float spec = pow(max(dot(viewDir, reflectDir), 0.f), shininess);
  vec3 specular = specularTerm * spec * objectColor;

  objectColor = (ambient + diffuse + specular) * objectColor;
  fragPos = vec3(modelMatrix * vec4(vPosition, 1.f));

  // End TODO:
}
