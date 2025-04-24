#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<cmath>

#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
#include<ft2build.h>
#include FT_FREETYPE_H
// TODO:   
// (Deltatime adden)
// freetype
// (mehr gui stuff)
// save state
// outline wie Polygon mode
// Collision *_*

#include"mesh.h"
#include"gui.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

float FOV = 90.0f;

int FramesPerSecond = 20;

float rotation = 0.0f;

float CamX = 0.0f;
float CamY = 1.0f;
float CamZ = 2.0f;

float XPos = 0.0f;
float YPos = 0.0f;
float ZPos = 0.0f;

float CubeXPos = 0.0f;
float CubeYPos = 1.0f;
float CubeZPos = 0.0f;

float CubeScaleX = 1.0f;
float CubeScaleY = 0.5f;
float CubeScaleZ = 1.0f;

float LightXPos = 1.5f;
float LightYPos = 1.5f;
float LightZPos = 1.5f;

float scaleX = 1.0f;
float scaleY = 1.0f;
float scaleZ = 1.0f;

float lightRed = 1.0f;
float lightGreen = 1.0f;
float lightBlue = 1.0f;

bool PolygonOn = false;

bool point = true;
bool direct = false;
bool spot = false;

bool drawObject = false;

bool rgb = true;

double DeltaTime();
void Model(Shader& shader, glm::mat4 model, Camera cam, Mesh mesh);
//void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

std::string Title = "If I loose it all, slip and fall";

Vertex vertices[] =
{
//                     x      y      z                  Normals                   R     G      B               TexCoord   
    Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

GLuint indices[] =
{
	0, 1 ,2,
	0, 2, 3
};

Vertex CubeVertices[] =
{
	//                     x      y      z                  Normals                   R     G      B               TexCoord   
		Vertex{glm::vec3(-0.25f, 0.0f,  0.25), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.25f, 0.0f, -0.25), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3( 0.25,  0.0f, -0.25), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3( 0.25,  0.0f,  0.25), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

GLuint CubeIndices[] =
{
	0, 1 ,2,
	0, 2, 3
};


Vertex lightVertices[] =
{ 
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3( 0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int main()
{
	//deltatime
	DeltaTime();

	// Intizailisierung von GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window Creation
	GLFWwindow* window = glfwCreateWindow(width, height, "Peekaboo", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "FAILED TO CREATE WINODW" << '\n';
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	
	glViewport(0, 0, width, height);

	//glfwSetKeyCallback(window, keyCallback);

	

	Texture textures[]
	{
		Texture("Assets/Textures/planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("Assets/Textures/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	Texture white[]
	{
		Texture("Assets/Textures/release.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("Assets/Textures/release.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	// lesen der shader dateien
	Shader shaderProgram("default.vert", "default.frag");
	
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh obj(verts, inds, tex);

	std::vector <Vertex> Cubeverts(CubeVertices, CubeVertices + sizeof(CubeVertices) / sizeof(Vertex));
	std::vector <GLuint> Cubeinds(CubeIndices, CubeIndices + sizeof(CubeIndices) / sizeof(GLuint));
	std::vector <Texture> Cubetex(white, white + sizeof(white) / sizeof(Texture));
	Mesh Cube(Cubeverts, Cubeinds, Cubetex);

	
	Shader lightShader("light.vert", "light.frag");

	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInds(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	std::vector <Texture> lightTex(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh lightObj(lightVerts, lightInds, lightTex);

	

	GLboolean uniPoint = glGetUniformLocation(shaderProgram.ID, "point");
	GLboolean uniDirect = glGetUniformLocation(shaderProgram.ID, "direct");
	GLboolean uniSpot = glGetUniformLocation(shaderProgram.ID, "spot");
	

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);

	Camera camera(width, height, glm::vec3(CamX, CamY, CamZ));

	GUI GUI1(window);

	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	glfwSwapInterval(1); //Vsync
		
	while (!glfwWindowShouldClose(window))
	{
		float dt = (float)DeltaTime();
		
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 30.0)
		{
			std::string FPS = std::to_string((int)(1.0 / timeDiff) * counter);
			std::string ms = std::to_string((timeDiff / counter) * 1000);
			std::string newTitle = Title + " - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(window, newTitle.c_str());
			prevTime = crntTime;
			counter = 0;
		}


		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//light
		glm::vec4 lightColor = glm::vec4(lightRed, lightGreen, lightBlue, 1.0f);
		glm::vec3 lightPos = glm::vec3(LightXPos, LightYPos, LightZPos);
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);

		

		//cube
		glm::mat4 CubeModel = glm::mat4(1.0f);
		glm::vec3 CubeScale = glm::vec3(CubeScaleX, CubeScaleY, CubeScaleZ);
		glm::vec3 CubePos = glm::vec3(CubeXPos, CubeYPos, CubeZPos);
		CubeModel = glm::translate(CubeModel, CubePos);
		CubeModel = glm::scale(CubeModel, CubeScale);
		CubeModel = glm::rotate(CubeModel, glm::radians(0.0f),glm::vec3(0.0f, 1.0f, 0.0f));
		

		//model
		glm::vec3 pyramidPos = glm::vec3(XPos, YPos, ZPos);
		glm::vec3 pyramidScale = glm::vec3(scaleX, scaleY, scaleZ);
		glm::mat4 pyramidModel = glm::mat4(1.0f);
		pyramidModel = glm::translate(pyramidModel, pyramidPos);
		pyramidModel = glm::scale(pyramidModel, pyramidScale);
		pyramidModel = glm::rotate(pyramidModel, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));



		lightShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		lightObj.Draw(lightShader, camera);

		shaderProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
		obj.Draw(shaderProgram, camera);


		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(CubeModel));
		Cube.Draw(shaderProgram, camera);
		

		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		
		

		camera.Inputs(window, dt);
		camera.updateMatrix(FOV, 0.1f, 100.0f, dt);

		
		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");


		

		//Switch zwischen Polygon mode 
		if (PolygonOn == true)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (PolygonOn == false)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glUniform1i(uniPoint, point);
		glUniform1i(uniDirect,direct);
		glUniform1i(uniSpot, spot);

		GUI1.guiNewFrame();
		GUI1.Theme1();
		GUI1.Begin("Menu");


		

		if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
		{

			
			

			if (ImGui::BeginTabItem("Camera"))
			{
				ImGui::SetWindowSize(ImVec2(400.0f, 150.0f));
				//ImGui::Text("X: %f", CamX);
				GUI1.Slider(      "FOV",   &FOV,          45.0f, 120.0f, NULL);
				ImGui::InputFloat("Speed", &camera.speed, 0.1f, 2.0f);
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Light"))
			{
				ImGui::SetWindowSize(ImVec2(400.0f, 325.0f));
				GUI1.Slider(  "X-Position",           &LightXPos, -10.0f, 10.0f, NULL);
				GUI1.Slider(  "Y-Position",           &LightYPos, -10.0f, 10.0f, NULL);
				GUI1.Slider(  "Z-Position",           &LightZPos, -10.0f, 10.0f, NULL);
				GUI1.Checkbox("Point Lighting",       &point);
				GUI1.Checkbox("Directional Lighting", &direct);
				GUI1.Checkbox("Spot Lighting",        &spot);
				GUI1.Slider(  "Red",                  &lightRed,    0.0f,  1.0f, NULL);
				GUI1.Slider(  "Green",                &lightGreen,  0.0f,  1.0f, NULL);
				GUI1.Slider(  "Blue",                 &lightBlue,   0.0f,  1.0f, NULL);
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Model"))
			{
				//           Name          referenze    min      max
				ImGui::SetWindowSize(ImVec2(400.0f, 600.0f));
				ImGui::Text("Model 1");
				ImGui::Separator();
				GUI1.Slider("X-Position",  &XPos,     -10.0f,   10.0f,   NULL);
				GUI1.Slider("Y-Position",  &YPos,     -10.0f,   10.0f,   NULL);
				GUI1.Slider("Z-Position",  &ZPos,     -10.0f,   10.0f,   NULL);
				GUI1.Slider("X-Size",      &scaleX,     0.1f,    2.0f,   NULL);
				GUI1.Slider("Y-Size",      &scaleY,     0.1f,    2.0f,   NULL);
				GUI1.Slider("Z-Size",      &scaleZ,     0.1f,    2.0f,   NULL);
				GUI1.Slider("Rotation",    &rotation,   0.0f,  360.0f,   NULL);
				ImGui::Text("Model 2");
				ImGui::Separator();
				GUI1.Slider("X-Position", &CubeXPos,  -10.0f, 10.0f,    NULL);
				GUI1.Slider("Y-Position", &CubeYPos,  -10.0f, 10.0f,    NULL);
				GUI1.Slider("Z-Position", &CubeZPos,  -10.0f, 10.0f,    NULL);
				GUI1.Slider("X-Size ",     &CubeScaleX,  0.1f,  2.0f,    NULL);
				GUI1.Slider("Y-Size ",     &CubeScaleY,  0.1f,  2.0f,    NULL);
				GUI1.Slider("Z-Size ",     &CubeScaleZ,  0.1f,  2.0f,    NULL);

				GUI1.Checkbox("Polygon Mode", &PolygonOn);
				ImGui::EndTabItem();
			}


			if (ImGui::BeginTabItem("Settings"))
			{
				//           Name          referenze    min      max

				ImGui::EndTabItem();
			}

		}
		
		//ImGui::ShowStyleEditor();
		ImGui::EndTabBar();
		GUI1.End();

		GUI1.renderGUI();

		glfwSwapBuffers(window);

		glfwPollEvents();

	}

	GUI1.Delete();

	
	shaderProgram.Delete();
	lightShader.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}

double DeltaTime()
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
		
	double Delta = currentTime - lastTime;
	lastTime = currentTime;
	return Delta;
}

void Model(Shader& shader, glm::mat4 model, Camera cam, Mesh mesh)
{
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	mesh.Draw(shader, cam);
}

/*
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// On key press 
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		drawObject = true;
	}
}*/


