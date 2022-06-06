#include "MultiLine.h"

#include <iostream>
#include <cmath>

namespace cgCourse
{
	MultiLine::MultiLine(const std::vector<glm::vec3> & _vertices,
						 const std::vector<glm::vec3> & _normals) : Shape()
	{
		positions.resize(_vertices.size() * 2);
		colors.resize(_vertices.size() * 2);

		for(int i = 0; i < _vertices.size(); ++i)
		{
			int a = i << 1;	// 2 * i;
			int b = a + 1;	// 2 * i + 1;

			positions[a] = _vertices[i];
			positions[b] = _vertices[i] + 0.25f * _normals[i];

			colors[a] = colors[b] = glm::vec3(1, 1, 0);
		}
	}

	void MultiLine::draw() const
	{
		glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, posBufferID);
		glDrawArrays(GL_LINES, 0, positions.size());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

