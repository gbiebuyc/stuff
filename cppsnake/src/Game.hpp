/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:58:43 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/06 18:58:43 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
#define GAME_HPP

#include "RawTerm.hpp"
#include <iostream>
#include <unistd.h>

class Game {
public:
	void Loop() {
		for (int i = 0; i < 10; i++) std::cout << "\r\n";
		while (true) {
			std::cout << "\e[10A" << std::flush;
			std::cout << "\e[J" << std::flush;
			for (int i = 0; i < 5; i++) std::cout << "\r\n";
			for (int i = 0; i < _x; i++) std::cout << " ";
			std::cout << _direction << std::flush;
			for (int i = 0; i < 5; i++) std::cout << "\r\n";
			sleep(1);
			readInput();
			sleep(1);
			_x++;
		}
	}
private:
	RawTerm _term;
	int _x = 0;
	std::string _direction;
	void readInput() {
		char c;
		while (read(STDIN_FILENO, &c, 1) == 1){
			std::cout << "read" << std::flush;
			if (c == '\e') {
			    if (read(STDIN_FILENO, &c, 1) != 1) continue;
				if (c != '[') continue;
			    if (read(STDIN_FILENO, &c, 1) != 1) continue;
			    if (c == 'A') _direction = "up";
			    else if (c == 'B') _direction = "down";
			    else if (c == 'C') _direction = "right";
			    else if (c == 'D') _direction = "left";
			}
		}
	}
};

#endif
