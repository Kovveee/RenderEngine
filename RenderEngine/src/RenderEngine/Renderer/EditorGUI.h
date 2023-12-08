#pragma once

//imGUI
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//C++
#include <vector>

//RenderEngine
#include "Model.h"
#include "LightSource.h"
#include "DirectionalLight.h"


class EditorGUI
{
public:
	EditorGUI(GLFWwindow* window);
	void enableGui();
	void destroyGui();
	void drawGui();
	void MainWindow(std::vector<Model*>& models, std::vector<DirectionalLight*>& lightSources);
	void TestDepthMap(float& near_plane, float& far_plane, float& size, bool& isNormal);
private:
	void PropertyWindow(Model* model);

};

