/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 12:00:59 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 12:00:59 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIEHORDE_HPP
# define ZOMBIEHORDE_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Zombie.hpp"

class ZombieHorde
{
private:
    static std::string _randomNames[6];
    Zombie *_zombies;
    int _numZombies;
public:
    ZombieHorde(int n);
    ~ZombieHorde();
    void announce();
};

#endif
