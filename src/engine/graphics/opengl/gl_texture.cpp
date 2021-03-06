#include "gl_texture.h"

#include <glad/glad.h>

#include <assert.h>
#include <spdlog/spdlog.h>

#include "engine/engine.h"
#include "engine/internal_libs.h"



namespace oe::graphics {

	GLTexture::GLTexture(const Instance* instance, const TextureInfo& texture_info)
		: Texture(instance, texture_info)
	{
		// generate texture
		m_target = 0;
		glGenTextures(1, &m_id);

		// load texture
		switch (m_texture_info.dimensions)
		{
		case 1:
			if (m_texture_info.empty)
				empty1D(m_texture_info.width);
			else
				load1D(m_texture_info.data, m_texture_info.width);
			break;
		case 2:
			if (m_texture_info.empty)
				empty2D(m_texture_info.width, m_texture_info.height);
			else
				load2D(m_texture_info.data, m_texture_info.width, m_texture_info.height);
			break;
		case 3:
			if (m_texture_info.empty)
				empty3D(m_texture_info.width, m_texture_info.height, m_texture_info.depth);
			else
				load3D(m_texture_info.data, m_texture_info.width, m_texture_info.height, m_texture_info.depth);
			break;
		default:
			oe_error_terminate("Unsupported texture dimension ({})", m_texture_info.dimensions);
			break;
		}

		// mipmaps
		if (m_texture_info.generate_mipmaps) {
			glGenerateMipmap(m_target);
		}
	}

	GLTexture::~GLTexture() {
		glDeleteTextures(1, &m_id);
	}

	void GLTexture::bind() {
		glBindTexture(m_target, m_id);
	}

	void GLTexture::unbind() {
		glBindTexture(m_target, 0);
	}

	void GLTexture::setData(const TextureInfo& texture_info) {
		// load texture
		switch (m_texture_info.dimensions)
		{
		case 1:
			data1D(m_texture_info.data, m_texture_info.width, m_texture_info.x_offset);
			break;
		case 2:
			data2D(m_texture_info.data, m_texture_info.width, m_texture_info.x_offset, m_texture_info.height, m_texture_info.y_offset);
			break;
		case 3:
			data3D(m_texture_info.data, m_texture_info.width, m_texture_info.x_offset, m_texture_info.height, m_texture_info.y_offset, m_texture_info.depth, m_texture_info.z_offset);
			break;
		default:
			oe_error_terminate("Unsupported texture dimension ({})", m_texture_info.dimensions);
			break;
		}

		// mipmaps
		if (m_texture_info.generate_mipmaps) {
			glGenerateMipmap(m_target);
		}
	}

	void GLTexture::empty1D(size_t width) {
		m_target = GL_TEXTURE_1D;
		bind();

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexStorage1D(m_target, 1, GL_RGBA8, width);
	}

	void GLTexture::empty2D(size_t width, size_t height) {
		m_target = GL_TEXTURE_2D;
		bind();

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexStorage2D(m_target, 1, GL_RGBA8, width, height);
	}

	void GLTexture::empty3D(size_t width, size_t height, size_t depth) {
		m_target = GL_TEXTURE_3D;
		bind();

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexStorage3D(m_target, 1, GL_RGBA8, width, height, depth);
	}

	void GLTexture::load1D(const uint8_t* data, size_t width) {
		m_target = GL_TEXTURE_1D;
		bind();

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage1D(m_target, 0, GL_RGBA8, width, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	void GLTexture::load2D(const uint8_t* data, size_t width, size_t height) {
		m_target = GL_TEXTURE_2D;
		bind();

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTexImage2D(m_target, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	void GLTexture::load3D(const uint8_t* data, size_t width, size_t height, size_t depth) {
		m_target = GL_TEXTURE_3D;
		bind();

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage3D(m_target, 0, GL_RGBA8, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	void GLTexture::data1D(const uint8_t* data, size_t width, size_t x_offset) {
		bind();
		if (x_offset + width > m_texture_info.width) 
			oe_error_terminate("Sub texture bigger than initial texture");
		glTextureSubImage1D(m_id, 0, x_offset, width, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	
	void GLTexture::data2D(const uint8_t* data, size_t width, size_t x_offset, size_t height, size_t y_offset) {
		bind();
		if (x_offset + width > m_texture_info.width || y_offset + height > m_texture_info.height) 
			oe_error_terminate("Sub texture bigger than initial texture");
		glTextureSubImage2D(m_id, 0, x_offset, y_offset, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	
	void GLTexture::data3D(const uint8_t* data, size_t width, size_t x_offset, size_t height, size_t y_offset, size_t depth, size_t z_offset) {
		bind();
		if (x_offset + width > m_texture_info.width || y_offset + height > m_texture_info.height || z_offset + depth > m_texture_info.depth) 
			oe_error_terminate("Sub texture bigger than initial texture");
		glTextureSubImage3D(m_id, 0, x_offset, y_offset, z_offset, width, height, depth, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

}
