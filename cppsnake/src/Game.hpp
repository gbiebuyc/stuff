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

class Game {
public:
	void Loop() {
		for (int i = 0; i < 10; i++) std::cout << "\r\n";
		while (true) {
			std::cout << "\e[10A" << std::flush;
			std::cout << "\e[J" << std::flush;
			for (int i = 0; i < 5; i++) std::cout << "\r\n";
			for (int i = 0; i < _x; i++) std::cout << " ";
			std::cout << "hello" << std::flush;
			for (int i = 0; i < 5; i++) std::cout << "\r\n";
			sleep(1);
			_x++;
		}
	}
private:
	RawTerm _term;
	int _x = 0;
};

#endif
