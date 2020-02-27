/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex04.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:00:03 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 13:00:05 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(void) {
    std::string s("HI THIS IS BRAIN");
    std::string *ptr = &s;
    std::string &ref = s;
    std::cout << *ptr << std::endl;
    std::cout << ref << std::endl;
}