#pragma once

#ifdef RE_PLATFORM_WINDOWS
	#ifdef RE_BUILD_DLL
		#define RENDERENGINE_API __declspec(dllexport)
	#else
		#define RENDERENGINE_API __declspec(dllimport)
	#endif
#else
	#error RenderEngine only support windows!
#endif