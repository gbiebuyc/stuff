/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:52:06 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 10:52:06 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIEEVENT_HPP
# define ZOMBIEEVENT_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Zombie.hpp"

class ZombieEvent
{
private:
    std::string _zombieType;
    static std::string _randomNames[6];
public:
    ZombieEvent();
    ~ZombieEvent();
    void setZombieType(std::string type);
    Zombie* newZombie(std::string name);
    Zombie* randomChump();
};

#endif