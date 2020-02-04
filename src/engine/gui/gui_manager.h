#pragma once

#include "widgets/widget.h"
#include "widgets/form.h"
#include "widgets/text_panel.h"
#include "widgets/text_input.h"
#include "widgets/button.h"
#include "widgets/button_decorated.h"
#include "widgets/slider.h"
#include "widgets/sprite_panel.h"



namespace oe::gui {

	class GUI {
	public:
		GUI();
		~GUI();
		
		// needs to be after every window resize
		void resize(const glm::vec2& window_size);

		// calls resize(window width, window height)
		void resize();

		void cursor(int button, int action, const glm::vec2& cursor_window);
		void text(unsigned int character, int mods);
		void key(int key, int action, int mods);
		
		// assigns std::unique_ptr for this pointer
		// do forget pointer to this widget
		void addSubWidget(Widget* widget);
		
		// bind SpritePacker that you used to create Font and all Sprites for StaticTextureViews
		void render();
		
	};

}