/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 22:50:11 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/01 22:50:11 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) :
    Form("ShrubberyCreationForm", target, 145, 137) {
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &src) {
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &rhs) {
    // _foo = rhs.getFoo();
    return *this;
}

std::ostream &operator<<(std::ostream &o, ShrubberyCreationForm const &rhs) {
    //o << "The value of _foo is: " << rhs.getFoo();
    return o;
}

void ShrubberyCreationForm::_execute(void) const {
    std::cout << "executing" << std::endl;
}
