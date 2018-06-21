/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPU.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:27:59 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/21 20:36:02 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CPU.hpp"

CPU::CPU(void) {}

CPU::~CPU(void) {}

void	CPU::start(int ac, char *av[])
{
	(void)this->_stack;
	try
	{
		if (ac == 1)
			this->_io.parse(*this);
		else
			for (int i = 1; i < ac; i++)
			{
				this->_io.reset_state();
				this->_io.parse(av[i], *this);
			}
	}
	catch (std::exception & e)
	{
		if (std::string(e.what()).empty() == false)
			std::cout << "AVM: " << e.what() << std::endl;
		exit(-1);
	}
}

void	CPU::analyze(const std::string & s)
{
	if (s.empty())
		return ;

	std::regex	expr("\\s*([^\\s()]+)(\\s*([^\\s()]*)\\(([^\\s())]*)\\))?\\s*");
	std::smatch sm;

	if (std::regex_match(s, sm, expr))
	{
		if (static_cast<std::string>(sm[2]).empty())
			this->_action(sm[1]);
		else
			this->_action(sm[1], sm[3], sm[4]);
	}
	else
		throw std::invalid_argument("Warning: Syntax error");
}

void	CPU::_action(std::string cmd)
{
	if (cmd == "exit")
		exit (0);
	// std::vector < std::tuple < std::string, void (*)(void *), void * > >	cmds = {
	// 	{ "exit", reinterpret_cast<void (*)(void *)>(&exit), (int []){0} }
	// };

	// auto	it = find_if(cmds.begin(), cmds.end(), [&cmd](const std::tuple < std::string, void (*)(void *), void * > & c){ return (std::get<0>(c) == cmd); });
	// if (it != cmds.end())
	// 	std::get<1>(*it)(std::get<2>(*it));
	// else
	// 	throw std::invalid_argument((std::string("Warning: Unknown command '") + cmd + "'").c_str());
}

void	CPU::_action(std::string cmd, std::string type, std::string value)
{
	std::cout << "Multiple: |" << cmd << "|: |" << type << "| -> |" << value << "|" << std::endl;
}
