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

ShrubberyCreationForm::ShrubberyCreationForm(void) {
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &src) {
    *this = src;
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
