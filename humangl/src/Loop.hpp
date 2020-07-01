/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 15:40:30 by nathan            #+#    #+#             */
/*   Updated: 2020/05/24 17:56:05 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LOOP_CLASS_H
# define LOOP_CLASS_H
#include <glfw3.h>

class Loop {
public:
	static void loop();
private:
	static void processInput();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool shouldStop;
	static double frameTime;
	const static double refreshingRate;
	static unsigned int animIndex;
	static unsigned int frameIndex;
};

#endif
