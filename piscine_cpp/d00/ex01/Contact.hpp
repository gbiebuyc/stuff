/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:45:00 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/25 11:45:01 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_H
# define CONTACT_H

# include <iostream>
# include <iomanip>

class Contact
{
private:
    std::string firstname;
    std::string lastname;
    std::string nickname;
    std::string login;
    std::string postalAddress;
    std::string email;
    std::string phone;
    std::string birthday;
    std::string favMeal;
    std::string underwearColor;
    std::string darkestSecret;

public:
    void print();
    void printRow(int index);
    void promptFields();
};

#endif
