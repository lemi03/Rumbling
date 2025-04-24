#include"gui.h"



GUI::GUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImFont* font = io.Fonts->AddFontFromFileTTF("C:/Users/atayo/OneDrive/Desktop/OpenGLOL/Assets/Fonts/Open_Sans/static/OpenSans-Medium.ttf", 18.0f);
	ImFont* font1 = io.Fonts->AddFontFromFileTTF("C:/Users/atayo/OneDrive/Desktop/OpenGLOL/Assets/Fonts/ComicGeek/comicgeek.ttf", 18.0f);
}

void GUI::Theme1()
{
	
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 0.75f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.01f, 0.01f, 0.01f, 0.45f);
	//Frame
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.095f, 0.095f, 0.095f, 0.90f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.12f, 0.12f, 0.85f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.5f, 0.17f, 0.17f, 0.85f);
	//SliderGrab
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	//Ckeckmark
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.5f, 0.17f, 0.17f, 1.0f);
	//tab
	style.Colors[ImGuiCol_Tab] = ImVec4(0.5f, 0.17f, 0.17f, 0.85f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.5f, 0.17f, 0.17f, 0.95f);
	style.Colors[ImGuiCol_TabSelected] = ImVec4(0.55f, 0.18f, 0.18f, 1.0f);
	//Button
	style.Colors[ImGuiCol_Button] = ImVec4(0.17f, 0.17f, 0.17f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.5f, 0.17f, 0.17f, 0.85f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.5f, 0.18f, 0.18f, 1.0f);
	//Resizegrip 
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.55f, 0.17f, 0.17f, 0.33f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.55f, 0.18f, 0.18f, 0.5f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.55f, 0.18f, 0.18f, 0.95f);
	//Header
	style.Colors[ImGuiCol_Header] = ImVec4(0.55f, 0.17f, 0.17f, 0.75f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.55f, 0.18f, 0.18f, 0.85f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.55f, 0.18f, 0.18f, 1.0f);
	//Seperator
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.55f, 0.17f, 0.17f, 0.5f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.55f, 0.18f, 0.18f, 0.95f);

	style.WindowRounding = 5.0f;
	style.FrameRounding = 5.0f;
	style.PopupRounding = 3.0f;
	style.GrabRounding = 4.0f;
	style.WindowBorderSize = 0.0f;
}


void GUI::guiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUI::renderGUI()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Delete()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUI::Begin(const char *name)
{
	ImGui::Begin(name);
}

void GUI::Checkbox(const char* name, bool* tf)
{
	ImGui::Checkbox(name, tf);
}

void GUI::Slider(const char* label, float* v, float v_min, float v_max, const char* format)
{
	ImGui::SliderFloat(label, v, v_min, v_max, format);
}

void GUI::End()
{
	ImGui::End();
}