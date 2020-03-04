/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:48:53 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/04 15:48:53 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

template <typename T>
int &easyfind(T container, int n) {
    typename T::iterator it = find(container.begin(), container.end(), n);
    if (it == container.end())
        throw std::runtime_error("not found");
    return *it;
}

#endif
