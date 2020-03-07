/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:58:43 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/06 18:58:43 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
#define GAME_HPP

#include "RawTerm.hpp"
#include <iostream>
#include <list>
#include <unistd.h>

#define UP 'A'
#define DOWN 'B'
#define RIGHT 'C'
#define LEFT 'D'

typedef struct { int x, y; } t_point;

class Game {

public:
    Game() {
        _snake.push_back({10, 10});
    }
    void Loop() {
        for (int i = 0; i < 24; i++) std::cout << "\r\n";
        while (true) {
            std::cout << "\e[23" << UP << "\e[J";
            drawSnake();
            std::cout << "\e[999" << DOWN;
            std::cout << "\e[999" << LEFT;
            std::cout << std::flush;
            usleep(500000);
            readInput();
            advanceSnake();
        }
    }

private:
    RawTerm _term;
    char _direction = RIGHT;
    std::list<t_point> _snake;

    void readInput() {
        char c;
        while (read(STDIN_FILENO, &c, 1) == 1){
            if (c == '\e') {
                if (read(STDIN_FILENO, &c, 1) != 1) continue;
                if (c != '[') continue;
                if (read(STDIN_FILENO, &c, 1) != 1) continue;
                if (c == UP) _direction = UP;
                else if (c == DOWN) _direction = DOWN;
                else if (c == RIGHT) _direction = RIGHT;
                else if (c == LEFT) _direction = LEFT;
            }
        }
    }

    void putBlock(t_point const &p) const {
        std::cout << "\e[999" << DOWN;
        std::cout << "\e[999" << LEFT;
        if (p.y) std::cout << "\e[" << 24 - p.y - 1 << UP;
        if (p.x) std::cout << "\e[" << p.x << RIGHT;
        std::cout << 'X' << std::flush;
    }

    void drawSnake() const {
        for (auto const &elem : _snake) {
            putBlock(elem);
        }
    }

    void advanceSnake() {
        t_point newHead = _snake.back();
        if (_direction == UP) newHead.y--;
        else if (_direction == DOWN) newHead.y++;
        else if (_direction == LEFT) newHead.x--;
        else if (_direction == RIGHT) newHead.x++;
        _snake.push_back(newHead);
        _snake.pop_front();
    }
};

#endif
