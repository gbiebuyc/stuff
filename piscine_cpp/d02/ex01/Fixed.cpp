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
#include <math.h>

Fixed::Fixed(void) : _value(0) {
    std::cout << "Default constructor called\n";
}

Fixed::Fixed(Fixed const &src) {
    std::cout << "Copy constructor called\n";
    *this = src;
}

Fixed::~Fixed(void) {
    std::cout << "Destructor called\n";
}

Fixed &Fixed::operator=(Fixed const &rhs) {
    std::cout << "Assignation operator called\n";
    _value = rhs.getRawBits();
    return *this;
}

std::ostream &operator<<(std::ostream &o, Fixed const &rhs) {
    o << rhs.toFloat();
    return o;
}

int Fixed::getRawBits(void) const {
    return (_value);
}

void Fixed::setRawBits(int raw) {
    std::cout << "setRawBits member function called\n";
    _value = raw;
}

const int Fixed::_numFractBits = 8;

Fixed::Fixed(int const i) {
    std::cout << "Int constructor called\n";
    _value = i << _numFractBits;
}

Fixed::Fixed(float const f) {
    std::cout << "Float constructor called\n";
    _value = (int)(f * (1 << _numFractBits));
}

float Fixed::toFloat(void) const {
    return ((float)_value / (float)(1 << _numFractBits));
}

int Fixed::toInt(void) const {
    return (_value >> _numFractBits);
}
