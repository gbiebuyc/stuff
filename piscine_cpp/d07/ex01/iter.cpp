/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:38:58 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/03/01 16:38:58 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

template <typename T>
void iter(T *arr, size_t len, void (*f)(T &)) {
	for (size_t i = 0; i < len; i++) {
		f(arr[i]);
	}
}

template <typename T>
void print(T &a) {
	std::cout << a << std::endl;
}

int main() {
	int a[] = {1, 2, 3, 4, 5};
	float b[] = {1.1, 2.2, 3.3, 4.4, 5.5};
	iter(a, sizeof(a) / sizeof(*a), &print);
	iter(b, sizeof(b) / sizeof(*b), &print);
}
