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

#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <stdexcept>

class RawTerm {
public:
	RawTerm() {
		enableRawMode();
		doStuff(); 
	}
	~RawTerm() {
		disableRawMode();
	}
private:
	struct termios orig_termios;
	void disableRawMode() {
	  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
		throw std::runtime_error("tcsetattr");
	}
	void enableRawMode() {
	  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
		throw std::runtime_error("tcsetattr");
	  struct termios raw = orig_termios;
	  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	  raw.c_oflag &= ~(OPOST);
	  raw.c_cflag |= (CS8);
	  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	  raw.c_cc[VMIN] = 0;
	  raw.c_cc[VTIME] = 1;
	  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		throw std::runtime_error("tcsetattr");
	}
	void doStuff() {
		std::cout << "hello" << std::flush;
		sleep(1);
	}
};