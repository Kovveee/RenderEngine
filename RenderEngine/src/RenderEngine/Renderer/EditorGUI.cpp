#include "EditorGUI.h"

EditorGUI::EditorGUI(GLFWwindow* window)
{
	// Init imGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
}
void EditorGUI::enableGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
void EditorGUI::destroyGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
void EditorGUI::drawGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void EditorGUI::MainWindow(std::vector<Model*>& models, std::vector<DirectionalLight*>& lightSources) 
{
		ImGui::Begin("Main window");
		static int item_current_idx = 0;
		if (ImGui::BeginListBox("Objects"))
		{
			for (int n = 0; n < models.size(); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(models[n]->GetName().c_str(), is_selected))
					item_current_idx = n;

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
					PropertyWindow(models[n]);
				}

			}
			ImGui::EndListBox();
		}
		if (ImGui::BeginListBox("Lights"))
		{
			for (int n = 0; n < lightSources.size(); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable("n", is_selected))
					item_current_idx = n;

				if (is_selected)
				{
					DirectionalLightData* data = (DirectionalLightData*)lightSources[n]->GetData();
					glm::vec3 direction = glm::vec3(data->direction.x, data->direction.y, data->direction.z);
					ImGui::SetItemDefaultFocus();
					ImGui::Begin(n + " properties");
					ImGui::DragFloat3("Position", (float*)&direction, 0.001f, -1000.f, 1000.f);
					ImGui::End();
					data->direction = glm::vec4(direction.x,direction.y,direction.z,1.0f);
				}

			}
			ImGui::EndListBox();
		}
		ImGui::End();
}
void EditorGUI::PropertyWindow(Model* model)
{
	ImGui::Begin((model->GetName() + " properties").c_str());
	ImGui::DragFloat3("Position", (float*)model->GetTranslation(), 1.f, -1000.f, 1000.f);
	ImGui::DragFloat3("Rotation", (float*)model->GetRotation(), 1.f, -360.f, 360.f);
	ImGui::DragFloat3("Scale", (float*)model->GetScale(), 0.001f, 0.001f, 1000.f);
	ImGui::End();
}

void EditorGUI::TestDepthMap(float& near_plane, float& far_plane, float& size, bool& isNormal) {
	ImGui::Begin("Test depth map");
	ImGui::DragFloat("Near plane", &near_plane, 10.f, -1000.f, 1000.f);
	ImGui::DragFloat("Far plane", &far_plane, 10.f, -1000, 1000.f);
	ImGui::DragFloat("Size", &size, 10.f, 0.f, 100.f);
	if (ImGui::Button("Normal")) {
		if (isNormal)
			isNormal = false;
		else
			isNormal = true;
	}
	ImGui::End();
}