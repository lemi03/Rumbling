#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane, float deltatime)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	FOVdeg = FOV;

	view = glm::lookAt(Position, Position + Orientation, Up);
	
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	cameraMatrix = projection * view * deltatime;

}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}


void Camera::Inputs(GLFWwindow* window , float deltatime)
{
	glm::vec3 Direction = glm::normalize(glm::vec3(Orientation.x, 0.0f, Orientation.z));
	glm::vec3 SpectateDirection = glm::normalize(Orientation);
	//vorwärts
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS and !spectator)
	{
		Position += Direction * speed * deltatime; 
	}
	//vorwärts spectator
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS and spectator)
	{
		Position += SpectateDirection * speed * deltatime;
	}
	//links
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up)) * deltatime;
	}
	//hinten
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS and !spectator)
	{
		Position -= Direction * speed * deltatime;
	}
	//hinten spectator
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS and spectator)
	{
		Position -= SpectateDirection * speed * deltatime;
	}
	//rechts
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up)) * deltatime;
	}
	//Jump
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up * deltatime;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up * deltatime;
	}
	//rein Zoom
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		FOV = 25.0f;
		sensitivity = 50.0f;
	}
	//raus zoom
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE)
	{
		FOV = 90.0f;
		sensitivity = 91.0f;
	}
	// Cursor sichtbar + mouse deaktiv
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		cursorVisible = true;
	}

	
	if (firstClick)
	{
		glfwSetCursorPos(window, (width / 2), (height / 2));
		firstClick = false;
	}
	
	double mouseX;
	double mouseY;
	
	glfwGetCursorPos(window, &mouseX, &mouseY);

	
	float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
	float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

	if (cursorVisible == false)
	{
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;
		glfwSetCursorPos(window, (width / 2), (height / 2));
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	if (cursorVisible == true)
	{
		rotX = 0.0f;
		rotY = 0.0f;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		cursorVisible = false;
		firstClick = true;
	}

	
	 glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

	
	 if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	 {
		Orientation = newOrientation;
	 }

	
	 Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
}