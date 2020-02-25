/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:44:43 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/25 11:44:45 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void Contact::print()
{
    std::cout << "First name: " << this->firstname << std::endl;
    std::cout << "Last name: " << this->lastname << std::endl;
    std::cout << "Nickname: " << this->nickname << std::endl;
    std::cout << "Login: " << this->login << std::endl;
    std::cout << "Postal address: " << this->postalAddress << std::endl;
}

void Contact::printRow(int index)
{
    std::cout << std::setw(10) << index << '|';
    std::cout << std::setw(10) << std::setw(10);
    std::cout << std::setw(10) << firstname << '|';
    std::cout << std::setw(10) << lastname << '|';
    std::cout << std::setw(10) << nickname << std::endl;
}

void Contact::promptFields()
{
    std::string s;

    std::cout << "First name: ";
    getline(std::cin, s);
    this->firstname = s;
    std::cout << "Last name: ";
    getline(std::cin, s);
    this->lastname = s;
    std::cout << "Nickname: ";
    getline(std::cin, s);
    this->nickname = s;
    std::cout << "Login: ";
    getline(std::cin, s);
    this->login = s;
    std::cout << "Postal address: ";
    getline(std::cin, s);
    this->postalAddress = s;
    std::cout << "Email address: ";
    getline(std::cin, s);
    this->email = s;
    std::cout << "Phone number: ";
    getline(std::cin, s);
    this->phone = s;
    std::cout << "Birthday date: ";
    getline(std::cin, s);
    this->birthday = s;
    std::cout << "Favorite meal: ";
    getline(std::cin, s);
    this->favMeal = s;
    std::cout << "Underwear color: ";
    getline(std::cin, s);
    this->underwearColor = s;
    std::cout << "Darkest secret: ";
    getline(std::cin, s);
    this->darkestSecret = s;
}
