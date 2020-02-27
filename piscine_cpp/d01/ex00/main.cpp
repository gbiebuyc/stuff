/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:20:40 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 10:20:42 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pony.hpp"

void ponyOnTheHeap()
{
    Pony *p = new Pony();

    p->doSomething();
    delete p;
}

void ponyOnTheStack()
{
    Pony p;

    p.doSomething();
}

int main(void)
{
    ponyOnTheHeap();
    ponyOnTheStack();
}