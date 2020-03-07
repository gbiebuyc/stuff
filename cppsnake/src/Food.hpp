/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Food.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 20:06:19 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/07 20:06:19 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FOOD_HPP
#define FOOD_HPP

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Food {
public:

    Food() {
        srand (time(NULL));
        spawnNewFood();
        spawnNewFood();
        spawnNewFood();
    }

    std::list<Cell> const &getCells() const {
        return _cells;
    }

    void eat(Cell const &food) {
        _cells.remove(food);
    }

    void spawnNewFood() {
        Cell newFood;
        newFood.x = rand() % 78 + 1;
        newFood.y = rand() % 22 + 1;
        _cells.push_back(newFood);
    }

private:
    std::list<Cell> _cells;

};

#endif
