/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:21:57 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/04 17:21:57 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class Span {
public:
    Span(unsigned int);
    Span(Span const & src);
    virtual ~Span(void);
    Span &operator=(Span const &rhs);
    void addNumber(int);
    int shortestSpan(void) const;
    int longestSpan(void) const;
private:
    Span(void);
    std::vector<int> _v;
    unsigned int _n;
};

std::ostream &operator<<(std::ostream &o, Span const &rhs);

#endif
