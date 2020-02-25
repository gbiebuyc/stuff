/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:44:18 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/25 11:44:20 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "Contact.hpp"

int main()
{
    Contact     contacts[8];
    int         numContacts = 0;;
    std::string line;

    while (1)
    {
        std::getline(std::cin, line);
        if (line == "EXIT")
            exit(0);
        else if (line == "ADD" && numContacts == 8)
            std::cout << "Error: max 8 contacts.\n";
        else if (line == "ADD")
            contacts[numContacts++].promptFields();
        else if (line == "SEARCH") {
            for (int i = 0; i < numContacts; i++) {
                contacts[i].printRow(i);
            }
        }
    }
}
