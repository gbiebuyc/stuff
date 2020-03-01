/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:11:59 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/01 18:11:59 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"

int main() {
	try {
		Bureaucrat b("toto", 42);
		ShrubberyCreationForm f("myForm", 50, 50);
		std::cout << b << std::endl;
		b.signForm(f);
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	try {
		Bureaucrat b("toto", 42);
		ShrubberyCreationForm f("myForm", 1, 1);
		std::cout << b << std::endl;
		b.signForm(f);
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
