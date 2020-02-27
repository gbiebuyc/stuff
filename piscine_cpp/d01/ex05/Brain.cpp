/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:11:34 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 13:11:34 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(void) {
}

Brain::~Brain(void) {
}

std::string Brain::identify() const {
    std::stringstream ss;
    ss << "0x";
    ss << std::uppercase << std::hex;
    ss << (uintptr_t)this;
    return (ss.str());
}