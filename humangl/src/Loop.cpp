/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 15:40:25 by nathan            #+#    #+#             */
/*   Updated: 2020/05/24 17:57:54 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GL/glew.h>
#include "Loop.hpp"
#include <glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <unistd.h>
#include "Window.hpp"
#include "Skeleton.hpp"

bool Loop::shouldStop = false;
double Loop::frameTime = 0.0f;
const double Loop::refreshingRate = 1.0 / 30.0;

#define SEC_TO_MICROSEC 1000000


void Loop::loop()
{
	glfwSetTime(0);
	glfwSetKeyCallback(Window::getWindow(), (GLFWkeyfun)Loop::keyCallback);
	while (!glfwWindowShouldClose(Window::getWindow()))
	{
		double currentTimer = glfwGetTime();
		processInput();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		//update(frameTime);

		//render();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Skeleton::draw();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(Window::getWindow());

		frameTime = glfwGetTime() - currentTimer;
		if (frameTime < refreshingRate)
		{
			usleep((refreshingRate - frameTime) * SEC_TO_MICROSEC);
		}
	}
}

void Loop::processInput()
{
	glfwPollEvents();
}

void Loop::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	(void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
