/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:01:39 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/01 18:01:39 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name) {
    setGrade(grade);
}

Bureaucrat::Bureaucrat(void) {
}

Bureaucrat::Bureaucrat(Bureaucrat const &src) {
    *this = src;
}

Bureaucrat::~Bureaucrat(void) {
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &rhs) {
    _grade = rhs.getGrade();
    return *this;
}

std::ostream &operator<<(std::ostream &o, Bureaucrat const &rhs) {
    o << rhs.getName() << ", bureaucrat grade " << rhs.getGrade();
    return o;
}

std::string Bureaucrat::getName(void) const {
    return _name;
}

int Bureaucrat::getGrade(void) const {
    return _grade;
}

void Bureaucrat::setGrade(int grade) {
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException();
    if (grade > 150)
        throw Bureaucrat::GradeTooLowException();
    _grade = grade;
}

void Bureaucrat::signForm(Form &f) {
    try {
        f.beSigned(*this);
        std::cout << _name << " signs " << f.getName() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << _name << " cannot sign " << f.getName() << " because grade too low." << std::endl;
    }
}

void Bureaucrat::executeForm(Form const &f) {
    try {
        f.execute(*this);
        std::cout << _name << " executes " << f.getName() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << _name << " cannot execute " << f.getName() << " because grade too low." << std::endl;
    }
}

Bureaucrat::GradeTooHighException::GradeTooHighException() {
}

Bureaucrat::GradeTooHighException::~GradeTooHighException() {
}

Bureaucrat::GradeTooHighException
&Bureaucrat::GradeTooHighException::operator=(GradeTooHighException const &rhs) {
    return *this;
}

const char *Bureaucrat::GradeTooHighException::what() const throw() {
    return "GradeTooHighException happened";
}

Bureaucrat::GradeTooLowException::GradeTooLowException() {
}

Bureaucrat::GradeTooLowException::~GradeTooLowException() {
}

Bureaucrat::GradeTooLowException
&Bureaucrat::GradeTooLowException::operator=(GradeTooLowException const &rhs) {
    return *this;
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
    return "GradeTooLowException happened";
}
