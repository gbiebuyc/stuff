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

#define UP 'A'
#define DOWN 'B'
#define RIGHT 'C'
#define LEFT 'D'
typedef struct { int x, y; } t_point;

#include <iostream>
#include <list>
#include <unistd.h>
#include "RawTerm.hpp"
#include "Snake.hpp"

class Game {

public:
    void Loop() {
        while (true) {
            draw();
            usleep(500000);
            readInput();
            _snake.advanceSnake();
        }
    }

private:
    RawTerm _term;
    Snake _snake;

    void readInput() {
        char c;
        while (read(STDIN_FILENO, &c, 1) == 1){
            if (c == '\e') {
                if (read(STDIN_FILENO, &c, 1) != 1) continue;
                if (c != '[') continue;
                if (read(STDIN_FILENO, &c, 1) != 1) continue;
                if (c == UP) _snake.setDirection(UP);
                else if (c == DOWN) _snake.setDirection(DOWN);
                else if (c == RIGHT) _snake.setDirection(RIGHT);
                else if (c == LEFT) _snake.setDirection(LEFT);
            }
        }
    }

    void draw() const {
        _term.clear();
        for (int i = 0; i < 79; i++) std::cout << '#';
        for (int i = 0; i < 23; i++) std::cout << "#\e[1B\e[1D";
        for (int i = 0; i < 79; i++) std::cout << "#\e[1D\e[1D";
        for (int i = 0; i < 23; i++) std::cout << "#\e[1A\e[1D";
        for (auto const &elem : _snake.getCells()) {
            std::cout << "\e[32m";
            _term.putBlock(elem);
            std::cout << "\e[m";
        }
        _term.moveCursorBottomLeft();
    }
};

#endif
