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

/*
layout(std140) uniform materialBlock {
  float ambient;
  float diffuse;
  float specular;
  float shininess;
} material;

layout(std140) uniform lightBlock {
  vec3 position;
  vec3 color;
} light;
*/

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

  /**
   * TODO: add there code for gourand shading
   */
  /*

  // didn't work out as in the slides ...

  // model-view camera transformation
  vec4 v_position = mvpMatrix * vec4(vPosition, 1.f);

  // normal transform in camera coordinates
  mat3 normMatrix = mat3(transpose(inverse(mvpMatrix)));
  vec3 n = normMatrix * normalize(vNormal);

  // set base color
  // vec4 color = vec4(vColor, 1.f);
  vec3 color = vColor;

  // light and eye vectors, in camera coordinates
  vec3 l = normalize(light.position.xyz - vec3(v_position));
  vec3 e = normalize(-vec3(v_position));

  // set ambient light contribution
  objectColor = material.ambient * light.color * color;

  // add diffuse contribution
  float diff = max(dot(n, vec3(1.f)), 0.f);
  if (diff > 0.f) {
    objectColor += material.diffuse * diff * light.color * color;

    // reflection vector
    vec3 r = normalize(reflect(vec3(-1.f), n));

    // add specular contribution
    float spec = max(dot(r, e), 0.f);
    if (spec > 0.f) {
      objectColor += material.specular * pow(spec, material.shininess) * light.color * color;
    }
  }

  // apply model-view-projection transform
  gl_Position = mvpMatrix * vec4(vPosition, 1);
  */

  fragPos = vec3(modelMatrix * vec4(vPosition, 1.f));
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
  // End TODO

}
