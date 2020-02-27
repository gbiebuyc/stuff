/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:48:05 by gbiebuyc          #+#    #+#             */
/*   Updated: 2020/02/27 17:48:27 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Human.hpp"


void Human::meleeAttack(std::string const & target) {
    std::cout << "melee attack " << target << std::endl;
}
void Human::rangedAttack(std::string const & target) {
    std::cout << "ranged attack " << target << std::endl;
}
void Human::intimidatingShout(std::string const & target) {
    std::cout << "intimidating attack " << target << std::endl;
}
void Human::action(std::string const & action_name, std::string const & target) {
    _f[0] = &Human::meleeAttack;
    _f[1] = &Human::rangedAttack;
    _f[2] = &Human::intimidatingShout;
    std::string actions[] = {
        "melee",
        "ranged",
        "intimidating"
    };
    for (int i = 0; i < 3; i++) {
        if (action_name == actions[i])
            (this->*_f[i])(target);
    }
    
}
