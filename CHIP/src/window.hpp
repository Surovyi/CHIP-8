#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Window
{
public:
	void init()
	{
		glfwSetErrorCallback(errorCallback);

		if (glfwInit() == GL_FALSE) {
			std::cerr << "GLFW setup failed!" << std::endl;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		m_window = glfwCreateWindow(640, 480, "CHIP-8", NULL, NULL);
		if (m_window == nullptr) {
			std::cerr << "GLFW Window creation failed!" << std::endl;
		}

		glfwMakeContextCurrent(m_window);
		gladLoadGL();

		glfwSetWindowCloseCallback(m_window, closeWindowCallback);
		glfwSetKeyCallback(m_window, keyCallback);
	}

	void run()
	{

	}

	void terminate()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

private:
	GLFWwindow* m_window;

	static void errorCallback(int error, const char* description)
	{
		std::cerr << "[" << error << "] " << description << std::endl;
	}

	static void closeWindowCallback(GLFWwindow* window)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
};