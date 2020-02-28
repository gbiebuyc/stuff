/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:45:44 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/28 12:45:44 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void) : _value(0) {
    std::cout << "Default constructor called\n";
}

Fixed::Fixed(Fixed const &src) {
    std::cout << "Copy constructor called\n";
    *this = src;
}

Fixed::~Fixed(void) {
}

Fixed &Fixed::operator=(Fixed const &rhs) {
    std::cout << "Assignation operator called\n";
    _value = rhs.getRawBits();
    return *this;
}

std::ostream &operator<<(std::ostream &o, Fixed const &rhs) {
    //o << "The value of _foo is: " << rhs.getFoo();
    return o;
}

int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called\n";
    return (_value);
}

void Fixed::setRawBits(int raw) {
    std::cout << "setRawBits member function called\n";
    _value = raw;
}