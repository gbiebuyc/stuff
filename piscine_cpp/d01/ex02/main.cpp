/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:50:04 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 10:50:06 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include "ZombieEvent.hpp"

int main(void) {
    ZombieEvent ze;
    ze.setZombieType("Cunt");
    Zombie *z1 = ze.randomChump();
    Zombie *z2 = ze.randomChump();
    Zombie *z3 = ze.randomChump();
    Zombie *z4 = ze.randomChump();
    Zombie *z5 = ze.randomChump();
    delete z1;
    delete z2;
}