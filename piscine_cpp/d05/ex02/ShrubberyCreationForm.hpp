/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 22:50:11 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/01 22:50:11 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include <iostream>
#include "Form.hpp"

class ShrubberyCreationForm : public Form {
public:
    ShrubberyCreationForm(std::string target);
    ShrubberyCreationForm(ShrubberyCreationForm const & src);
    virtual ~ShrubberyCreationForm(void);
    ShrubberyCreationForm &operator=(ShrubberyCreationForm const &rhs);
private:
    ShrubberyCreationForm(void);
    virtual void _execute(void) const;
};

std::ostream &operator<<(std::ostream &o, ShrubberyCreationForm const &rhs);

#endif
