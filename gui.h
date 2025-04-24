#ifndef IMGUI_CLASS_H
#define IMGUI_CLASS_H

#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
#include"imgui/imgui_internal.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>

class GUI
{
	public:

		GUI(GLFWwindow* window);

		void Theme1();

		void guiNewFrame();

		void renderGUI();

		void Delete();

		void Begin(const char *name);

		void Checkbox(const char* name, bool* tf);

		void Slider(const char* label, float* v, float v_min, float v_max, const char* format);

		void End();
};

#endif
