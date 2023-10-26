#include "stdpch.h"

#include "Texture.h"
#include <GL\glew.h>

#include "stb_image\stb_image.h"


Texture::Texture(const std::string& path)
	:m_Renderer_ID(0), m_FilePath(path), m_LocalBufer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBufer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_Renderer_ID);
	glBindTexture(GL_TEXTURE_2D, m_Renderer_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBufer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBufer)
		stbi_image_free(m_LocalBufer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Renderer_ID);
}

void Texture::Bind(uint32_t slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_Renderer_ID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}