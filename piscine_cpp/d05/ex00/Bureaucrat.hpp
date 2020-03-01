/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:01:39 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/01 18:01:39 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>

class Bureaucrat {
private:
    Bureaucrat(void);
    std::string const _name;
    int _grade;
    void setGrade(int grade);
public:
    Bureaucrat(std::string name, int grade);
    Bureaucrat(Bureaucrat const & src);
    ~Bureaucrat(void);
    Bureaucrat &operator=(Bureaucrat const &rhs);
    class GradeTooHighException : public std::exception {
    public:
        GradeTooHighException(void);
        GradeTooHighException(GradeTooHighException const & src);
        ~GradeTooHighException(void);
        GradeTooHighException &operator=(GradeTooHighException const &rhs);
        virtual const char *what() const throw();
    };
    class GradeTooLowException : public std::exception {
    public:
        GradeTooLowException(void);
        GradeTooLowException(GradeTooLowException const & src);
        ~GradeTooLowException(void);
        GradeTooLowException &operator=(GradeTooLowException const &rhs);
        virtual const char *what() const throw();
    };
    std::string getName(void) const;
    int getGrade(void) const;
    void incrementGrade(void);
    void decrementGrade(void);
};

std::ostream &operator<<(std::ostream &o, Bureaucrat const &rhs);

#endif
