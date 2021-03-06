#pragma once

#include "engine/graphics/interface/shader.h"
#include "engine/graphics/interface/instance.h"



namespace oe::graphics {

	class DefaultShader {
	private:
		const Instance* m_instance;
	
	public:
		Shader *shader; // inheritance not possible

	public:
		DefaultShader(const Instance* instance);
		~DefaultShader();

		inline void bind() { shader->bind(); }
		inline void unbind() { shader->unbind(); }

		inline void modelMatrix(glm::mat4 matrix) const {
			shader->setUniformMat4("ml_matrix", matrix);
		}
		
		inline void viewMatrix(glm::mat4 matrix) const {
			shader->setUniformMat4("vw_matrix", matrix);
		}
		
		inline void projectionMatrix(glm::mat4 matrix) const {
			shader->setUniformMat4("pr_matrix", matrix);
		}
		
		inline void useTexture(bool use_tex) const {
			shader->setUniform1i("usetex", use_tex ? 1 : 0);
		}

	};
}