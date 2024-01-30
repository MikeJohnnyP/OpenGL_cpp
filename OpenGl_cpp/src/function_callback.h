#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int witdh, int height);
void processInput(GLFWwindow* window);


void framebuffer_size_callback(GLFWwindow* window, int witdh, int height) {
	glViewport(0, 0, witdh, height);
};


// define GLFW_PRESS 1
// define GLFW_RELEASES 0
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == 1) {
		std::cout << "Window is passed away" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == 1) {
		std::cout << "Space is PRESS!!!" << '\n';
	}
	if (glfwGetKey(window, GLFW_KEY_ENTER) == 1) {
		std::cout << "Enter is PRESS" << '\n';
	}
};
