#version 410 core

/* TODO update your vertex shader so that...
 *      ...it can receive the tangent as vertex input
 *      ...it calculates a tbn matrix
 *      ...it emits a tbn matrix to the fragment shader
 */

// Input vertex data
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec2 vTexCoords;
layout(location = 4) in vec3 vTangent;

// Output data will be interpolated for each fragment.
// Tip: Try to use the flat modifier to make color associations of a fragment visible for debugging.
out vec3 objectColor;
out vec3 vertexNormal;
out vec3 worldPos;
out vec2 texCoord;
out mat3 TBN;

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

void main()
{
	texCoord = vTexCoords;
	gl_Position = mvpMatrix * vec4(vPosition, 1);
	objectColor = vColor;
	worldPos = vec3(modelMatrix * vec4(vPosition, 1));

	/* TODO: calculate the tbn matrix and update the normal here */
	mat4 normalMatrix = transpose(inverse(modelMatrix));

	vertexNormal = normalize(mat3(transpose(inverse(modelMatrix))) * vNormal);
	vec3 tangent = normalize(vec3(normalMatrix * vec4(vTangent, 0.0)));
	vec3 bitangent = normalize(cross(vertexNormal, tangent));
	TBN = mat3(tangent, bitangent, vertexNormal);
	// END TODO
}
