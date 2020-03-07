/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RawTerm.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:03:20 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/06 17:03:20 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAWTERM_HPP
#define RAWTERM_HPP

#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>

class RawTerm {
public:
    RawTerm() {
        enableRawMode();
        for (int i = 0; i < 24; i++) std::cout << "\r\n";
    }

    ~RawTerm() {disableRawMode();}

    void putBlock(Cell const &p) const {
        moveCursorBottomLeft();
        if (p.y) std::cout << "\e[" << 24 - p.y - 1 << UP;
        if (p.x) std::cout << "\e[" << p.x << RIGHT;
        std::cout << 'X' << std::flush;
    }

    void moveCursorBottomLeft() const {
        std::cout << "\e[999" << DOWN << "\e[999" << LEFT << std::flush;
    }

    void moveCursorTopLeft() const {
        moveCursorBottomLeft();
        std::cout << "\e[23" << UP << std::flush;
    }

    void clear() const {
        moveCursorTopLeft();
        std::cout << "\e[J" << std::flush;
    }

private:
    struct termios _orig_termios;

    void disableRawMode() {
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &_orig_termios) == -1)
            throw std::runtime_error("tcsetattr");
        std::cout << std::endl;
    }

    void enableRawMode() {
        if (tcgetattr(STDIN_FILENO, &_orig_termios) == -1)
            throw std::runtime_error("tcsetattr");
        struct termios raw = _orig_termios;
        raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
        raw.c_oflag &= ~(OPOST);
        raw.c_cflag |= (CS8);
        raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 0;
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
            throw std::runtime_error("tcsetattr");
    }
};

#endif
