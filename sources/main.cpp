/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:21:08 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/19 21:17:00 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avm.hpp"
#include "IOperand.hpp"
#include "CPU.hpp"

// int		main(void)
// {
// 	std::string s("add hada(42.42)");
// 	std::smatch sm;
// 	std::regex	expr("\\s*([^\\s()]+)(\\s*([^\\s()]*)\\(([^\\s())]*)\\))?\\s*");

// 	if (std::regex_match(s, sm, expr))
// 	{
// 		std::cout << "Nice! Parts:" << std::endl;
// 		for (size_t i = 0; i < sm.size(); i++)
// 			std::cout << sm[i] << std::endl;
// 	}
// 	else
// 	std::cout << "Error!" << std::endl;
// }

int		main(int ac, char *av[])
{
	CPU		vm;

	vm.start(ac, av);
	return (0);
}
