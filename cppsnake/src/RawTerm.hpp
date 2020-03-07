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
    RawTerm() {enableRawMode();}
    ~RawTerm() {disableRawMode();}
private:
    struct termios _orig_termios;
    void disableRawMode() {
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &_orig_termios) == -1)
            throw std::runtime_error("tcsetattr");
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
