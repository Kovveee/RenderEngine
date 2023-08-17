#include <RenderEngine.h>

class Sandbox : public RenderEngine::Application {
public:
	Sandbox() {
		
	}
	~Sandbox() {

	}
};


RenderEngine::Application* RenderEngine::CreateApplication()
{
	return new Sandbox();
}
