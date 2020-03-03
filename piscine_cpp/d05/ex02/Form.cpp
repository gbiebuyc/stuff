/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:28:19 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/01 20:28:19 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form(void) :
    _gradeRequiredToSign(0),
    _gradeRequiredToExec(0) {
}

Form::Form(std::string name, std::string target, int gradeRequiredToSign, int gradeRequiredToExec) :
    _name(name),
    _target(target),
    _signed(false),
    _gradeRequiredToSign(gradeRequiredToSign),
    _gradeRequiredToExec(gradeRequiredToExec) {
    if (_gradeRequiredToSign < 1 || _gradeRequiredToExec < 1)
        throw Form::GradeTooHighException();
    if (_gradeRequiredToSign > 150 || _gradeRequiredToExec > 150)
        throw Form::GradeTooLowException();
}

Form::Form(Form const &src) :
    _gradeRequiredToSign(0),
    _gradeRequiredToExec(0) {
    *this = src;
}

Form::~Form(void) {
}

Form &Form::operator=(Form const &rhs) {
    return *this;
}

std::ostream &operator<<(std::ostream &o, Form const &rhs) {
    o << "Form signed: " << rhs.getSigned();
    return o;
}

std::string Form::getName(void) const {
    return _name;
}

bool Form::getSigned(void) const {
    return _signed;
}

int Form::getGradeRequiredToSign(void) const {
    return _gradeRequiredToSign;
}

int Form::getGradeRequiredToExec(void) const {
    return _gradeRequiredToSign;
}

void Form::beSigned(Bureaucrat &b) {
    if (b.getGrade() > _gradeRequiredToSign)
        throw Form::GradeTooLowException();
    _signed = true;
}

void Form::execute(Bureaucrat const &b) const {
    if (!_signed)
        throw Form::NotSignedException();
    if (b.getGrade() > _gradeRequiredToExec)
        throw Form::GradeTooLowException();
    _execute();
}

Form::GradeTooHighException::GradeTooHighException() {
}

Form::GradeTooHighException::~GradeTooHighException() {
}

Form::GradeTooHighException
&Form::GradeTooHighException::operator=(GradeTooHighException const &rhs) {
    return *this;
}

const char *Form::GradeTooHighException::what() const throw() {
    return "GradeTooHighException happened";
}

Form::GradeTooLowException::GradeTooLowException() {
}

Form::GradeTooLowException::~GradeTooLowException() {
}

Form::GradeTooLowException
&Form::GradeTooLowException::operator=(GradeTooLowException const &rhs) {
    return *this;
}

const char *Form::GradeTooLowException::what() const throw() {
    return "GradeTooLowException happened";
}

Form::NotSignedException::NotSignedException() {
}

Form::NotSignedException::~NotSignedException() {
}

Form::NotSignedException
&Form::NotSignedException::operator=(NotSignedException const &rhs) {
    return *this;
}

const char *Form::NotSignedException::what() const throw() {
    return "NotSignedException happened";
}
