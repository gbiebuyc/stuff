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
	Bureaucrat b("toto", 145);
	ShrubberyCreationForm f("myTarget");
	std::cout << b << std::endl;
	b.signForm(f);
	b.executeForm(f);
}
