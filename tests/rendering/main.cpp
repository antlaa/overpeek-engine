#include <engine/engine.h>

#include <string>

#include "texture.png.h"



const oe::graphics::Sprite* sprite;
const oe::graphics::Sprite* sprite_white;
oe::graphics::Instance* instance;
oe::graphics::Window* window;
oe::graphics::SpritePack* pack;
oe::graphics::DefaultShader* shader;
oe::graphics::Renderer* renderer;

float t = 0;
void render(float update_fraction) {
	t += oe::utils::GameLoop::getFrameUpdateScale();

	// clear framebuffer
	window->clear();

	// begin submitting
	renderer->begin();
	renderer->clear();
	
	// submitting
	renderer->submit(glm::vec2(-0.5f, 0.5f), glm::vec2(0.4f), sprite_white, oe::colors::blue, oe::alignments::center_center, std::sin(t));
	renderer->submit(glm::vec2(-0.5f,-0.5f), glm::vec2(0.4f), sprite_white, oe::colors::red,   oe::alignments::center_center, std::tan(t));
	renderer->submit(glm::vec2( 0.5f,-0.5f), glm::vec2(0.4f), sprite_white, oe::colors::green, oe::alignments::center_center, t * 100.0f);
	renderer->submit(glm::vec2( 0.5f, 0.5f), glm::vec2(0.4f), sprite,       oe::colors::white, oe::alignments::center_center, std::pow(std::sin(t * 5.0f), 11.0f));

	// stop submitting and render
	pack->bind();
	renderer->end();
	renderer->render();
	
	// swap buffers and poll events
	window->update();

	// check if needs to close
	if (window->shouldClose()) oe::utils::GameLoop::stop();
}

void update() {
	spdlog::info("FPS: " + std::to_string(oe::utils::GameLoop::getFPS()));
}

void resize(const glm::vec2& window_size) {
	float aspect = window->aspect();
	glm::mat4 pr = glm::ortho(-aspect, aspect, 1.0f, -1.0f);
	spdlog::info(aspect);
	shader->projectionMatrix(pr);
	shader->useTexture(true);
}

void keyboard(oe::keys key, oe::actions action, oe::modifiers mods) {
	if (action == oe::actions::press) {
		if (key == oe::keys::key_escape) {
			oe::utils::GameLoop::stop();
		}
		else if (key == oe::keys::key_enter) {
			window->setFullscreen(!window->getFullscreen());
		}
	}
}

int main(int argc, char** argv) {
	// engine
	oe::EngineInfo engine_info = {};
	engine_info.api = oe::graphics_api::OpenGL;
	oe::Engine::init(engine_info);

	// instance
	oe::InstanceInfo instance_info = {};
	instance_info.debug_messages = true;
	// instance_info.favored_gpu_vulkan = oe::gpu::dedicated;
	instance = oe::Engine::createInstance(instance_info);

	// window
	oe::WindowInfo window_info;
	window_info.title = "Test 1 - Renderer";
	window_info.multisamples = 4;
	window = instance->createWindow(window_info);
	window->setResizeCallback(resize);
	window->setKeyboardCallback(keyboard);
	
	// instance settings
	instance->culling(oe::culling_modes::back);
	instance->swapInterval(1);
	instance->blending();

	// renderer
	oe::RendererInfo renderer_info = {};
	renderer_info.arrayRenderType = oe::types::dynamicrender;
	renderer_info.indexRenderType = oe::types::staticrender;
	renderer_info.max_quad_count = 6;
	renderer_info.staticVBOBuffer_data = nullptr;
	renderer = instance->createRenderer(renderer_info);

	// shader
	shader = new oe::graphics::DefaultShader(instance);
	
	// sprites
	auto img = oe::utils::loadImageCopy(texture_png, 5, 5);
	pack = new oe::graphics::SpritePack(instance);
	sprite = pack->addSprite(img);
	sprite_white = pack->empty_sprite();
	pack->construct();
	
	// start
	resize(window->getSize());
	oe::utils::GameLoop::init(render, update, 1);

	// closing
	delete pack;
	delete shader;
	instance->destroyRenderer(renderer);
	instance->destroyWindow(window);

	return 0;
}
