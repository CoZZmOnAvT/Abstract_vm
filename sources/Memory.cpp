/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Memory.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:45:32 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/22 19:04:40 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Memory.hpp"

typedef void FuncType(std::string const &, IOperand *) const;
typedef FuncType Memory::* memoryValueFunc;

Memory::Memory() {}
Memory::~Memory() {}

void			Memory::addValue(const IOperand * op)
{
	if (op != NULL)
		this->_data.push_back(op);
}

const IOperand	*Memory::createOperand(IOperand::eOperandType type, std::string const & value) const
{
	IOperand																			*ret = NULL;
	static std::unordered_map < IOperand::eOperandType, std::unique_ptr < IOperand > >	fabric;
	static std::unordered_map < IOperand::eOperandType, memoryValueFunc >				initialize = {
		{IOperand::Int8, reinterpret_cast < memoryValueFunc > (&Memory::_parse_int8)},
		{IOperand::Int16, reinterpret_cast < memoryValueFunc > (&Memory::_parse_int16)},
		{IOperand::Int32, reinterpret_cast < memoryValueFunc > (&Memory::_parse_int32)},
		{IOperand::Float, reinterpret_cast < memoryValueFunc > (&Memory::_parse_float)},
		{IOperand::Double, reinterpret_cast < memoryValueFunc > (&Memory::_parse_double)}
	};


	if (fabric.empty())
	{
		fabric[IOperand::Int8] = std::make_unique < Operand < int8_t > > ();
		fabric[IOperand::Int16] = std::make_unique < Operand < int16_t > > ();
		fabric[IOperand::Int32] = std::make_unique < Operand < int32_t > > ();
		fabric[IOperand::Float] = std::make_unique < Operand < float > > ();
		fabric[IOperand::Double] = std::make_unique < Operand < double > > ();
	}

	ret = fabric[type].release();

	this->_check_value(value, type);
	(this->*(initialize[type]))(value, ret);

	return (ret);
}

void			Memory::_check_value(std::string const & value, IOperand::eOperandType type) const
{
	if (value.empty())
		throw std::invalid_argument("Enter value");
	else if (std::regex_search(value, std::regex("[^0-9.]")))
		throw std::invalid_argument("Use only digits and dots for value");
	else if (static_cast<int>(type) < 3 && value.find('.') != std::string::npos)
		throw std::invalid_argument("A floating point not allowed for integer types");
	else if (std::regex_match(value, std::regex("([0-9]+)(\\.[0-9]+)?")) == false)
		throw std::invalid_argument("Incorrect value");
}

void			Memory::_parse_int8(std::string const & value, Operand <int8_t> * op) const
{
	try
	{
		int32_t		tmp = std::stoi(value);

		if (tmp != std::clamp(tmp, INT8_MIN, INT8_MAX))
			throw std::exception();
		op->setValue(tmp);
	}
	catch (std::exception & e)
	{
		throw std::invalid_argument((std::string("Argument overflow detected. Range (")
			+ std::to_string(INT8_MIN) + "; "
			+ std::to_string(INT8_MAX) + ")").c_str());
	}
}

void			Memory::_parse_int16(std::string const & value, Operand <int16_t> * op) const
{
	try
	{
		int32_t		tmp = std::stoi(value);

		if (tmp != std::clamp(tmp, INT16_MIN, INT16_MAX))
			throw std::exception();
		op->setValue(tmp);
	}
	catch (std::exception & e)
	{
		throw std::invalid_argument((std::string("Argument overflow detected. Range (")
			+ std::to_string(INT16_MIN) + "; "
			+ std::to_string(INT16_MAX) + ")").c_str());
	}
}

void			Memory::_parse_int32(std::string const & value, Operand <int32_t> * op) const
{
	try
	{
		op->setValue(std::stoi(value));
	}
	catch (std::exception & e)
	{
		throw std::invalid_argument((std::string("Argument overflow detected. Range (")
			+ std::to_string(INT32_MIN) + "; "
			+ std::to_string(INT32_MAX) + ")").c_str());
	}
}

void			Memory::_parse_float(std::string const & value, Operand <float> * op) const
{
	try
	{
		op->setValue(std::stof(value));
	}
	catch (std::exception & e)
	{
		throw std::invalid_argument((std::string("Argument overflow detected. Range (")
			+ std::to_string(std::numeric_limits<float>::lowest()) + "; "
			+ std::to_string(std::numeric_limits<float>::max()) + ")").c_str());
	}
}

void			Memory::_parse_double(std::string const & value, Operand <double> * op) const
{
	try
	{
		op->setValue(std::stod(value));
	}
	catch (std::exception & e)
	{
		throw std::invalid_argument((std::string("Argument overflow detected. Range (")
			+ std::to_string(std::numeric_limits<double>::lowest()) + "; "
			+ std::to_string(std::numeric_limits<double>::max()) + ")").c_str());
	}
}
