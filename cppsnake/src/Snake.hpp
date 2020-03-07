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
        _cells.push_back({10, 10});
    }

    void advanceSnake() {
        t_point newHead = _cells.back();
        if (_direction == UP) newHead.y--;
        else if (_direction == DOWN) newHead.y++;
        else if (_direction == LEFT) newHead.x--;
        else if (_direction == RIGHT) newHead.x++;
        _cells.push_back(newHead);
        _cells.pop_front();
    }

    std::list<t_point> const &getCells() const {
        return _cells;
    }

    void setDirection(char direction) {
        _direction = direction;
    }

private:
    std::list<t_point> _cells;
    char _direction = RIGHT;

};

#endif
