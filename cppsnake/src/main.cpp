/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:48:44 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/06 16:48:44 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdexcept>
#include "RawTerm.hpp"

int main() {
	try {
		RawTerm t;
	}
	catch (std::exception &e) {
		std::cerr << "Snake: Exception: " << e.what() << std::endl;
	}
}
