/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:52:06 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 10:52:06 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ZombieEvent.hpp"

ZombieEvent::ZombieEvent(void) {
    std::srand(std::time(NULL));
}

ZombieEvent::~ZombieEvent(void) {
}

std::string ZombieEvent::_randomNames[6] = {
    "hey",
    "yolo",
    "bruh",
    "foo",
    "bar",
    "dick"
};

void ZombieEvent::setZombieType(std::string type) {
    _zombieType = type;
}

Zombie *ZombieEvent::newZombie(std::string name) {
    return (new Zombie(_zombieType, name));
}

Zombie *ZombieEvent::randomChump() {
    Zombie *z = newZombie(_randomNames[std::rand() % 6]);
    z->announce();
    return (z);
}
