/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:41:32 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/07 00:41:32 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <iostream>

class Snake {
public:
    Snake() {
        _cells.push_front({10, 10});
        _cells.push_front({11, 10});
        _cells.push_front({12, 10});
    }

    bool advanceSnake() {
        Cell newHead = _cells.front();
        if (_direction == UP) newHead.y--;
        else if (_direction == DOWN) newHead.y++;
        else if (_direction == LEFT) newHead.x--;
        else if (_direction == RIGHT) newHead.x++;
        if (newHead.x < 1 || newHead.x > 78 ||
                newHead.y < 1 || newHead.y > 22)
            return false;
        if (std::find(_cells.begin(), _cells.end(), newHead) != _cells.end())
            return false;
        _cells.push_front(newHead);
        _cells.pop_back();
        return true;
    }

    void checkFood(Food &food) {
        Cell &head = _cells.front();
        auto &foods = food.getCells();
        auto it = std::find(foods.begin(), foods.end(), head);
        if (it == foods.end())
            return;
        food.eat(*it);
        food.spawnNewFood();
        Cell &tail = _cells.back();
        _cells.push_back(tail);
        _cells.push_back(tail);
        _cells.push_back(tail);
    }

    std::list<Cell> const &getCells() const {
        return _cells;
    }

    void setDirection(char direction) {
        _direction = direction;
    }

private:
    std::list<Cell> _cells;
    char _direction = RIGHT;

};

#endif
