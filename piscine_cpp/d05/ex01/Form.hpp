/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:28:18 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/01 20:28:18 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
private:
    Form(void);
    std::string const _name;
    bool _signed;
    int const _gradeRequiredToSign;
    int const _gradeRequiredToExec;
public:
    Form(std::string name, int gradeRequiredToSign, int gradeRequiredToExec);
    Form(Form const & src);
    virtual ~Form(void);
    Form &operator=(Form const &rhs);
    class GradeTooHighException : public std::exception {
    public:
        GradeTooHighException(void);
        GradeTooHighException(GradeTooHighException const & src);
        virtual ~GradeTooHighException(void);
        GradeTooHighException &operator=(GradeTooHighException const &rhs);
        virtual const char *what() const throw();
    };
    class GradeTooLowException : public std::exception {
    public:
        GradeTooLowException(void);
        GradeTooLowException(GradeTooLowException const & src);
        virtual ~GradeTooLowException(void);
        GradeTooLowException &operator=(GradeTooLowException const &rhs);
        virtual const char *what() const throw();
    };
    std::string getName(void) const;
    bool getSigned(void) const;
    int getGradeRequiredToSign(void) const;
    int getGradeRequiredToExec(void) const;
    void beSigned(Bureaucrat &b);
};

std::ostream &operator<<(std::ostream &o, Form const &rhs);

#endif
