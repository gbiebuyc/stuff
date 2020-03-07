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

#include <iostream>
#include <list>
#include <unistd.h>
#include "Cell.hpp"
#include "RawTerm.hpp"
#include "Food.hpp"
#include "Snake.hpp"

class Game {

public:
    void Loop() {
        while (true) {
            draw();
            usleep(150000);
            readInput();
            if (_snake.advanceSnake() == false)
                break;
            _snake.checkFood(_food);
        }
    }

    ~Game() { std::cout << "\nGame Over\n"; }

private:
    RawTerm _term;
    Snake _snake;
    Food _food;

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
            else if (c == 'h') _snake.setDirection(LEFT);
            else if (c == 'j') _snake.setDirection(DOWN);
            else if (c == 'k') _snake.setDirection(UP);
            else if (c == 'l') _snake.setDirection(RIGHT);
        }
    }

    void draw() const {
        _term.clear();
        for (int i = 0; i < 79; i++) std::cout << '#';
        for (int i = 0; i < 23; i++) std::cout << "#\e[1B\e[1D";
        for (int i = 0; i < 79; i++) std::cout << "#\e[1D\e[1D";
        for (int i = 0; i < 23; i++) std::cout << "#\e[1A\e[1D";
        std::cout << "\e[32m";
        for (auto const &elem : _snake.getCells()) {
            _term.putBlock(elem);
        }
        std::cout << "\e[91m";
        for (auto const &elem : _food.getCells()) {
            _term.putBlock(elem);
        }
        std::cout << "\e[m";
        _term.moveCursorBottomLeft();
    }
};

#endif
