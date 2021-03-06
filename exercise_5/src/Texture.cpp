#include "Texture.h"
#include <FreeImage.h>
#include <iostream>
#include <cstring>
#ifdef __APPLE__
#include <FreeImagePlus.h>
#endif

namespace cgCourse
{
	Texture::Texture(): texhandle(0)
	{
		bitsPerPixel = 0;
	}

	void Texture::loadFromFile(const std::string& _filename)
    {
		// .tif images have to be loaded with freeimage
		FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType(_filename.c_str(), 0);
		FIBITMAP* rawimage = FreeImage_Load(imageFormat, _filename.c_str());
		size = glm::vec2(FreeImage_GetWidth(rawimage),
							   FreeImage_GetHeight(rawimage));
		bitsPerPixel = FreeImage_GetBPP(rawimage);
		FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(rawimage);

		unsigned char* data = nullptr;

		switch (bitsPerPixel) {

		case 24: {
			FIBITMAP* image = FreeImage_ConvertTo32Bits(rawimage);
			if (!image) {
				std::cout << "Freeimage loading: go mad here" << std::endl;
			}
			FREE_IMAGE_COLOR_TYPE newcolorType = FreeImage_GetColorType(rawimage);
			data = new unsigned char[(int)(size.x * size.y * 4)];
			BYTE* rawArray = FreeImage_GetBits(image);
			memcpy(data, (BYTE*)FreeImage_GetBits(image), size.x * size.y * 4);
			break;
		}
		case 32: {
			data = new unsigned char[(int)(size.x * size.y * 4)];
			memcpy(data, (BYTE*)FreeImage_GetBits(rawimage), size.x * size.y * 4);
			break;
		}
		default: {
			std::cout << "Image could not be loaded." << std::endl;
			break;
		}
		}

		/*
		 *  TODO: generate the textures here:
		 *        - generate the texture handle and set the variable texhandle
		 *        - bind the texture handle
		 *        - set the min/mag filter parameter and if it works test if you
		 *          see a difference between GL_LINEAR, MIPMAP_LINEAR, NEAREST etc..
		 *        - set the texture wrap parameters
		 *        - set the texture data with glTexImage2D
		 *        - generate mipmaps
		 *        - unbind the texture handle (we do this to have a clean state when the
		 *          function is ending and no textures are bound after this call.)
		 *   For the moment we can assume that the textures have also 4 byte per pixel
		 *   so that we have RGBA textures. Some operating system might use BGRA as
		 *   pixel formats.
		 */

		// bind();
		glGenTextures(1, &texhandle);
		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		unbind();


		// End TODO

		// this function releases the memory previously occupied by freeimage for
		// image loading
		FreeImage_Unload(rawimage);
		// after copying the data to the GPU we can also delete data again.
		delete[] data;
    }

	GLuint Texture::getTexHandle() const
	{
		return texhandle;
	}

	void Texture::bind() const {
		if(texhandle != 0) {
			glBindTexture(GL_TEXTURE_2D, texhandle);
		}
    }

    void Texture::unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
    }
}

