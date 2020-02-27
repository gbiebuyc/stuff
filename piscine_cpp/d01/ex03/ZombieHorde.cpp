/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 12:00:59 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 12:00:59 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieHorde.hpp"

std::string ZombieHorde::_randomNames[6] = {
    "Hey",
    "Yolo",
    "Bruh",
    "Foo",
    "Bar",
    "Dick"
};

ZombieHorde::ZombieHorde(int n) {
    std::srand(std::time(NULL));
    _zombies = new Zombie[n];
    for (int i = 0; i < n; i++) {
        _zombies[i].setName(_randomNames[std::rand() % 6]);
        _zombies[i].setType("mytype");
    }
    _numZombies = n;
}

ZombieHorde::~ZombieHorde(void) {
    delete [] _zombies;
}

void ZombieHorde::announce(void) {
    for (int i = 0; i < _numZombies; i++) {
        _zombies[i].announce();
    }
}