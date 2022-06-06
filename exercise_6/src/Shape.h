#ifndef SHAPE_H
#define SHAPE_H

#include "GLIncludes.h"
#include <vector>
#include <glm/mat4x4.hpp>

namespace cgCourse
{
	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape();

		bool createVertexArray( GLuint posAttribLoc,
								GLuint colAttribLoc,
								GLuint normAttribLoc,
								GLuint texAttribLoc,
								GLuint tangentsAttribLoc
								);

		virtual void draw() const;

		std::vector<glm::vec3> & getPositions();
		std::vector<glm::vec3> & getNormals();
		std::vector<glm::uvec3> & getFaces();
		std::vector<glm::vec3> & getFaceNormals();
		std::vector<glm::vec3> & getTangents();

		const glm::mat4 & getModelMatrix() const;
		const glm::vec3 & getPosition() const;

		void setPosition(glm::vec3);
		void setRotation(float _angle, glm::vec3 _rot);
		void setScaling(glm::vec3 _scale);
		void calculateModelMatrix();

	protected:
		virtual void initIndexBuffer();

		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> tangents;
		glm::vec3 objectPosition;

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> colors;
		std::vector<glm::vec3> normals;
		std::vector<glm::uvec3> faces;
		std::vector<glm::vec3> faceNormals;

		glm::mat4 rotationMatrix = glm::mat4(1);
		glm::mat4 translationMatrix = glm::mat4(1);
		glm::mat4 scalingMatrix = glm::mat4(1);
		glm::mat4 modelMatrix = glm::mat4(1);	// Identity matrix

		GLuint vaoID = 0;
		GLuint posBufferID = 0;
		GLuint colorBufferID = 0;
		GLuint normalBufferID = 0;
		GLuint texCoordsBufferID = 0;
		GLuint tangentBufferID = 0;
		GLuint indexBufferID = 0;
	};
}

#endif // SHAPE_H

