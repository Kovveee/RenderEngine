#include <RenderEngine.h>

class Sandbox : public RenderEngine::Application {
public:
	Sandbox() {

	}
	~Sandbox() {

	}
};

int main() {
	Sandbox* sandbox = new Sandbox();
	sandbox->Run();
	delete sandbox;
	return 0;
}