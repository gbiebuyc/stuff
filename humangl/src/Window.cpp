/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:55:16 by nathan            #+#    #+#             */
/*   Updated: 2020/05/24 15:23:38 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Window.hpp"

bool Window::initialized = false;
GLFWwindow* Window::window = nullptr;

int Window::init()
{
	if (!initialized)
	{
		// Initialise GLFW
		if( !glfwInit() )
		{
			std::cerr << "Failed to initialize GLFW, bad return code on glfwInit" << std::endl;
			return (0);
		}
		glfwWindowHint(GLFW_SAMPLES, 4); // antilia4ing x4
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // openGL 4.5
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // "
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // no support from old openGL
		// Open a window and create its OpenGL context
		window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "HumanGL", NULL, NULL);

		if( window == nullptr )
		{
			std::cerr << "Failed to create a glfw Window" << std::endl;
			glfwTerminate();
			return 0;
		}

		glfwMakeContextCurrent(window);
	}
	initialized = true;
	return (1);
}

GLFWwindow*	Window::getWindow()
{
	return window;
}
