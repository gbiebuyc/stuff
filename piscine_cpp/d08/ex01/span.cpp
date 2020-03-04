/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:21:58 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/04 17:21:58 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "span.hpp"

Span::Span(void) {
}

Span::Span(unsigned int n) : _n(n) {
}

Span::Span(Span const &src) {
    *this = src;
}

Span::~Span(void) {
}

Span &Span::operator=(Span const &rhs) {
    // _foo = rhs.getFoo();
    return *this;
}

std::ostream &operator<<(std::ostream &o, Span const &rhs) {
    //o << "The value of _foo is: " << rhs.getFoo();
    return o;
}

void Span::addNumber(int n) {
    _v.push_back(n);
}

int Span::shortestSpan(void) const {
    if (_v.size() < 2)
        throw std::exception();
    std::vector<int> sorted = _v;
    sort(sorted.begin(), sorted.end());
    int minDiff = abs(sorted[0] - sorted[1]);
    int prev = sorted[1];
    std::vector<int>::iterator it;
    std::vector<int>::iterator end = sorted.end();
    for (it = sorted.begin() + 2; it < end; it++) {
        int diff = abs(*it - prev);
        if (diff < minDiff)
            minDiff = diff;
        prev = *it;
    }
    return minDiff;
}

int Span::longestSpan(void) const {
    if (_v.size() < 2)
        throw std::exception();
    return *max_element(_v.begin(), _v.end()) - *min_element(_v.begin(), _v.end());
}
