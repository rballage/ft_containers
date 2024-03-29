/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lower_bound.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:19:08 by mleblanc          #+#    #+#             */
/*   Updated: 2022/05/23 20:56:05 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::set<int> data;

    for (std::size_t i = 0; i < 10000; ++i) {
        data.insert(rand());
    }

    timer t;

    for (int i = 0; i < 100000; ++i) {
        NAMESPACE::set<int>::iterator it = data.lower_bound(rand());
        if (it != data.end()) {
            (void)*it;
        }
    }

    PRINT_TIME(t);
}
