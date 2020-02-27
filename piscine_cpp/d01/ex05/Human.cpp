/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:56:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 13:56:23 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Human.hpp"

Human::Human(void) {
}

Human::~Human(void) {
}

std::string Human::identify() {
    return (_brain.identify());
}

Brain const &Human::getBrain() {
    return (_brain);
}