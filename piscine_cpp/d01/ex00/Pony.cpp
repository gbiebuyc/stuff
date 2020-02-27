/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pony.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:15:02 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 10:15:02 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pony.hpp"

Pony::Pony(void) {
    std::cout << "Pony created\n";
}

Pony::~Pony(void) {
    std::cout << "Pony destroyed\n";
}

void Pony::doSomething(void) {
    std::cout << "Doing something\n";
}