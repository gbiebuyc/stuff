/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 23:01:41 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/29 23:01:41 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "need 1 arg\n";
		return (1);
	}
	std::stringstream ss(av[1]);
	// char mychar;
	int myint;
	// float myfloat;
	// double mydouble;
	ss >> myint;
	std::cout << myint << std::endl;
}
