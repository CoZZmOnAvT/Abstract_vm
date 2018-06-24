/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:21:08 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/24 15:26:55 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avm.hpp"
#include "IOperand.hpp"
#include "CPU.hpp"

int		main(int ac, char *av[])
{
	CPU		vm;

	vm.start(ac, av);
	return (0);
}
