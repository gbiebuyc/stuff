/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:48:44 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/06 16:48:44 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        Game game;
        game.loop();
    }
    catch (std::exception &e) {
        std::cerr << "Snake: Exception: " << e.what() << std::endl;
    }
}
