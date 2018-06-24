/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPU.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:27:59 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/24 18:41:13 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CPU.hpp"

CPU::CPU(void) {}

CPU::CPU(const CPU & elem) { *this = elem; }

CPU::~CPU(void) {}

CPU		& CPU::operator = (const CPU & elem)
{
	this->_stack = elem._stack;
	this->_io = elem._io;
	return (*this);
}

void	CPU::start(int ac, char *av[])
{
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
			std::cerr << "AVM: " << e.what() << std::endl;
		exit(-1);
	}
}

void	CPU::analyze(const std::string & s)
{
	if (s.empty())
		return ;

	std::regex	expr("\\s*([^\\s();]+)(\\s+([^\\s();]*)\\(([^\\s();)]*)\\))?\\s*(;.*)?");
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
	{
		this->_io.quit = true;
		return ;
	}
	std::unordered_map < std::string, void(Memory::*)() >	cmds = {
		{"add",   &Memory::addValue},   {"sub",   &Memory::subValue},
		{"mul",   &Memory::mulValue},   {"div",   &Memory::divValue},
		{"mod",   &Memory::modValue},   {"dump",  &Memory::dump    },
		{"print", &Memory::print   },   {"pop",   &Memory::pop     },
		{"min",   &Memory::minValue},   {"max",   &Memory::maxValue},
		{"avg",   &Memory::avgValue},   {"pow",   &Memory::powValue},
		{"inc++", &Memory::incValue},   {"dec--", &Memory::decValue},
		{"clear", &Memory::clearStack}
	};

	auto	it = cmds.find(cmd);
	if (it == cmds.end())
		throw std::invalid_argument((std::string("Invalid command name '") + cmd + "'").c_str());
	(this->_stack.*(cmds[cmd]))();
}

void	CPU::_action(std::string cmd, std::string type, std::string value)
{
	static const std::unordered_map < std::string, IOperand::eOperandType >	types = {
		{"int8", IOperand::Int8}, {"int16", IOperand::Int16},
		{"int32", IOperand::Int32}, {"float", IOperand::Float},
		{"double", IOperand::Double}
	};

	auto	it = types.find(type);
	if (it == types.end())
		throw std::invalid_argument((std::string("Unknown type name '") + type + "'").c_str());

	std::unique_ptr <const IOperand>	op = std::unique_ptr < const IOperand > (this->_stack.createOperand(it->second, value));

	if (cmd == "push")
		this->_stack.pushValue(op.release());
	else if (cmd == "assert")
		this->_stack.assertValue(op.get());
	else
		throw std::invalid_argument((std::string("Invalid command name '") + cmd + "'").c_str());
}
