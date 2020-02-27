/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:11:28 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 15:11:50 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>

int main(int ac, char **av) {
    if (ac < 4) {
        std::cout << "usage: filename needle replacement\n";
        return (1);
    }
    std::string needle(av[2]);
    if (needle.length() == 0) {
        std::cout << "needle must not be empty\n";
        return (1);
    }
    std::string infilename(av[1]);
    std::ifstream infile(infilename);
    if (!infile.good()) {
        std::cout << "open fail\n";
        return (1);
    }
    std::string outfilename = infilename + ".replace";
    std::ofstream outfile(outfilename);
    if (!outfile.good()) {
        std::cout << "open fail 2\n";
        return (1);
    }
    std::stringstream ss;
    ss << infile.rdbuf();
    std::string haystack(ss.str());
    std::size_t found = 0;
    while (1) {
        found = haystack.find(needle, found ? found + 1 : 0);
        if (found == std::string::npos)
            break;
        haystack.replace(found, needle.length(), av[3]);
    }
    outfile << haystack;
    infile.close();
    outfile.close();
}
