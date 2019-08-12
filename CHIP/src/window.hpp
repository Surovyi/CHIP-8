#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Window
{
public:
	//is window able to render
	static bool isRunning;

	void init()
	{

		// --------------- GLFW --------------- 
		glfwSetErrorCallback(errorCallback);

		if (glfwInit() == GL_FALSE) {
			std::cerr << "[GLFW]: Setup failed!" << std::endl;
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CHIP-8", NULL, NULL);
		if (m_Window == NULL) {
			std::cerr << "[GLFW]: Window creation failed!" << std::endl;
			return;
		}

		glfwMakeContextCurrent(m_Window);

		glfwSetWindowCloseCallback(m_Window, closeWindowCallback);
		glfwSetKeyCallback(m_Window, keyCallback);

		// --------------- GLAD --------------- 

		if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == NULL) {
			std::cerr << "[GLAD]: Setup failed!" << std::endl;
			return;
		}

		std::cout << "OpenGL Info:\n";
		std::cout << "   Vendor: " << glGetString(GL_VENDOR) << "\n";
		std::cout << "   Renderer: " << glGetString(GL_RENDERER) << "\n";
		std::cout << "   Version: " << glGetString(GL_VERSION) << "\n";

		// --------------- OpenGL -------------

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glfwSetFramebufferSizeCallback(m_Window, windowSizeCallback);

		// --------------- Preparing ----------

		glGenTextures(1, &m_RenderTexture);
		glBindTexture(GL_TEXTURE_2D, m_RenderTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindTexture(GL_TEXTURE_2D, 0);

		isRunning = true;
	}

	void run()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void terminate()
	{
		isRunning = false;
		glfwTerminate();
	}

private:
	GLFWwindow* m_Window;
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	GLuint m_RenderTexture;

	static void errorCallback(int error, const char* description)
	{
		std::cerr << "[" << error << "] " << description << std::endl;
	}

	static void windowSizeCallback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	static void closeWindowCallback(GLFWwindow* window)
	{
		isRunning = false;
		glfwTerminate();
	}

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
};

bool Window::isRunning = false;