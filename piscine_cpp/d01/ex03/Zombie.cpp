/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:36:12 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 10:36:12 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(void) {
}

Zombie::~Zombie(void) {
}

void Zombie::announce(void) {
    std::cout << "<" << _name << " (" << _type << ")> Braiiiiiiinnnssss...\n";
}

void Zombie::setName(std::string name) {
    _name = name;
}

void Zombie::setType(std::string type) {
    _type = type;
}