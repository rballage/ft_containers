/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_prelude.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:18:30 by mleblanc          #+#    #+#             */
/*   Updated: 2022/08/22 11:07:41 by rballage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "utils.hpp"

#include "prelude.hpp"
#include "type_traits_impl.hpp"

#define PRINT_IS_INTEGRAL(type)                                                                    \
    std::cout << #type << " = " << SFINAE::is_integral<type>::value << std::endl;
