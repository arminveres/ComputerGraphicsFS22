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

		bool createVertexArray(GLuint posAttribLoc, GLuint colAttribLoc, GLuint normAttribLoc);

        virtual void draw() const;

		std::vector<glm::vec3> & getPositions();
		std::vector<glm::vec3> & getNormals();
		std::vector<glm::uvec3> & getFaces();
		std::vector<glm::vec3> & getFaceNormals();

		glm::mat4 getModelMatrix() const;

        /* TODO: update the following functions
         * in the cpp file for translation,
         * scaling and rotations
         */
        void setPosition(glm::vec3);
        void setRotation(float _angle, glm::vec3 _rot);
        void setScaling(glm::vec3 _scale);
		void calculateModelMatrix();

	protected:
        virtual void initIndexBuffer();

        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> colors;
		std::vector<glm::vec3> normals;
		std::vector<glm::uvec3> faces;
		std::vector<glm::vec3> faceNormals;

        /* TODO: use other matrices matrices if necessary
         */
        glm::mat4 rotationMatrix;
        glm::mat4 translationMatrix;
        glm::mat4 scalingMatrix;
        glm::mat4 modelMatrix = glm::mat4(1);	// Identity matrix
        // TODO End

		GLuint vaoID = 0;
		GLuint posBufferID = 0;
		GLuint colorBufferID = 0;
		GLuint normalBufferID = 0;
		GLuint indexBufferID = 0;
	};
}

#endif //  SHAPE_H

