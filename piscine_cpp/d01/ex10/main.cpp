/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:01:44 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/28 10:02:07 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cerrno>

int main(int ac, char **av) {
    if (ac < 2)
        std::cout << std::cin.rdbuf();
    for (int i = 1; i < ac; i++) {
        std::ifstream fs(av[i]);
        if (!fs.good()) {
            std::cout << "cat: " << av[i] << ": " << strerror(errno) << std::endl;
            return (EXIT_FAILURE);
        }
        std::cout << fs.rdbuf();
        fs.close();
    }
}
