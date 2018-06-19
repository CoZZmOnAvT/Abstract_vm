/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPU.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:27:59 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/19 21:17:42 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CPU.hpp"

CPU::CPU(void) {}

CPU::~CPU(void)
{
	
}

void	CPU::start(int ac, char *av[])
{
	if (ac != 2)
		this->_io.parse_stdi(this->_stack);
	else if (ac == 2)
		this->_io.parse_file(av[1], this->_stack);
	else
		std::cout << "AVM: Incorrect number of parameters!" << std::endl;
}
