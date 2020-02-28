/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:50:37 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/28 15:17:51 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

int main( void ) {
    // Fixed a;
    // Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
    // std::cout << a << std::endl;
    // std::cout << ++a << std::endl;
    // std::cout << a << std::endl;
    // std::cout << a++ << std::endl;
    // std::cout << a << std::endl;
    // std::cout << b << std::endl;
    // std::cout << Fixed::max( a, b ) << std::endl;
    // return 0;

    std::cout << Fixed(3.14f) / Fixed(2) << std::endl;
}
