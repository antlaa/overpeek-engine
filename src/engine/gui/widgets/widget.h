#pragma once

#include <vector>
#include <engine/graphics/renderer.h>



namespace oe::gui {

	class Widget {
	private:
		Widget* m_parent;
		std::vector<Widget*> m_nodes;
		
	protected:
		oe::graphics::alignment m_align_parent;
		oe::graphics::alignment m_align_render;
		glm::vec2 m_offset_position;
		glm::vec2 m_topleft_position;
		glm::vec2 m_render_position;
		glm::vec2 m_size;

	public:
		// called from manager || __renderNodes
		void __render(oe::graphics::Renderer& renderer);
		void __resize();
		void __cursor(int button, int action, const glm::vec2& cursor_window);
		void __text(unsigned int character, int mods);
		void __key(int key, int action, int mods);

		void __setParent(Widget* parent);

	public:
		Widget(glm::ivec2 size);
		~Widget();

		virtual void addSubWidget(Widget* widget);
		virtual void render(oe::graphics::Renderer& renderer) {}
		virtual void resize() {}
		virtual void cursor(int button, int action, const glm::vec2& cursor_window) {}
		virtual void text(unsigned int character, int mods) {}
		virtual void key(int key, int action, int mods) {}

	public:
		oe::graphics::alignment& align_parent() { return m_align_parent; }
		oe::graphics::alignment& align_render() { return m_align_render; }
		glm::vec2& offset_position() { return m_offset_position; }
		glm::vec2& render_position() { return m_render_position; }
		glm::vec2& size() { return m_size; }
	};

}