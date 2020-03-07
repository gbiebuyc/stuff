/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cell.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 20:40:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/07 20:40:23 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CELL_HPP
#define CELL_HPP

#include <iostream>

struct Cell {
    int x, y;

    bool operator==(const Cell& c) const {
        return (c.x == this->x && c.y == this->y);
    }
};

#endif
