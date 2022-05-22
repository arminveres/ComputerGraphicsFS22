#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "GLIncludes.h"
#include <string>
#include <glm/vec2.hpp>

namespace cgCourse
{
	class Texture
	{
	public:
		Texture();

        void bind() const;
        void unbind() const;

		void loadFromFile(const std::string & filename);
		GLuint getTexHandle() const;

	private:
		GLuint texhandle;

		// Texture info
		glm::vec2 size;
		uint8_t bitsPerPixel;

	};
}

#endif
