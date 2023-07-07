#pragma once

#ifdef RE_PLATFORM_WINDOWS

extern RenderEngine::Application* RenderEngine::CreateApplication();


int main(int argc, char** argv) 
{
	auto app = RenderEngine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif