#include "OpenGL/OpenGLtexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Frisk {

	OpenGLtexture::OpenGLtexture() {

	}

	OpenGLtexture::OpenGLtexture(const std::filesystem::path& a_TexturePath) : m_TexturePath(a_TexturePath) {
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		STRING path_string = a_TexturePath.string();
		unsigned char* data = stbi_load(path_string.c_str(), &width, &height, &nrChannels, 0);

		m_Width = width;
		m_Height = height;

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			Log::Error("Failed to load texture.\n\n");
		}
		stbi_image_free(data);
	}

	OpenGLtexture::~OpenGLtexture() {
		glDeleteTextures(1, &m_TextureID);
	}

	void OpenGLtexture::Bind() const {
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void OpenGLtexture::Unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}