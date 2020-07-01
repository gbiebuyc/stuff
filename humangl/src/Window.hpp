/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nallani@student.s19.be>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 01:55:24 by nathan            #+#    #+#             */
/*   Updated: 2020/05/24 15:23:56 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef WINDOW_CLASS_H
# define WINDOW_CLASS_H

#include "Utilities.h"
#include <glfw3.h>

class Window {
public:
	static int init();
	//~Window(void);
	static GLFWwindow* getWindow();
private:
	static bool initialized;
	static GLFWwindow* window;
};

#endif
