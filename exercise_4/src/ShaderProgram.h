#ifndef _SHADERPROGRAM_H
#define _SHADERPROGRAM_H

#include "GLIncludes.h"
#include <string>

namespace cgCourse
{
	class ShaderProgram
	{
	public:
		ShaderProgram(std::string _name);

        void deleteShaderProgramFromGPU();
        void bind() const;
        void unbind() const;

        // Get uniform locations, e.g. for our mvp matrix
        // This can be done on the fly however, usually
        // the location is stored while shader compilation
        // to avoid the name lookup.
        GLuint getUniformLocation(const std::string & _uniformName);

	private:
		bool loadAndCompileShaderToGPU(GLuint _program, const std::string & _source);
		bool checkLinkStatusOfProgram(GLuint _program);
        std::string loadFile(const std::string & filename) const;

		GLuint program = 0;
	};
}

#endif
