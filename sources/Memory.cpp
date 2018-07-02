/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Memory.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:45:32 by pgritsen          #+#    #+#             */
/*   Updated: 2018/07/02 14:54:08 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Memory.hpp"
#include "Operand.hpp"

typedef void FuncType(std::string const &, IOperand *) const;
typedef FuncType Memory::* memoryValueFunc;

Memory::Memory() {}
Memory::~Memory() {}

Memory::Memory(const Memory & obj)
{
	*this = obj;
}

Memory			& Memory::operator = (const Memory & obj)
{
	this->_data = obj._data;
	return (*this);
}

void			Memory::addValue(void)
{
	if (this->_data.size() < 2)
		throw std::runtime_error("Stack capacity is lower than 2");

	auto	a = this->_data.top();
	this->_data.pop();
	auto	b = this->_data.top();
	this->_data.pop();

	const IOperand	* result = *b + *a;

	this->_data.push(std::shared_ptr<const IOperand>(result));
}

void			Memory::subValue(void)
{
	if (this->_data.size() < 2)
		throw std::runtime_error("Stack capacity is lower than 2");

	auto	a = this->_data.top();
	this->_data.pop();
	auto	b = this->_data.top();
	this->_data.pop();

	const IOperand	* result = *b - *a;

	this->_data.push(std::shared_ptr<const IOperand>(result));
}

void			Memory::mulValue(void)
{
	if (this->_data.size() < 2)
		throw std::runtime_error("Stack capacity is lower than 2");

	auto	a = this->_data.top();
	this->_data.pop();
	auto	b = this->_data.top();
	this->_data.pop();

	const IOperand	* result = *b * *a;

	this->_data.push(std::shared_ptr<const IOperand>(result));
}

void			Memory::divValue(void)
{
	if (this->_data.size() < 2)
		throw std::runtime_error("Stack capacity is lower than 2");

	auto	a = this->_data.top();
	this->_data.pop();
	auto	b = this->_data.top();
	this->_data.pop();

	const IOperand	* result = *b / *a;

	this->_data.push(std::shared_ptr<const IOperand>(result));
}

void			Memory::modValue(void)
{
	if (this->_data.size() < 2)
		throw std::runtime_error("Stack capacity is lower than 2");

	auto	a = this->_data.top();
	this->_data.pop();
	auto	b = this->_data.top();
	this->_data.pop();

	const IOperand	* result = *b % *a;

	this->_data.push(std::shared_ptr<const IOperand>(result));
}

void			Memory::minValue(void)
{
	if (this->_data.size() < 2)
		throw std::runtime_error("Stack capacity is lower than 2");

	auto	a = this->_data.top();
	this->_data.pop();
	auto	b = this->_data.top();
	this->_data.pop();

	if (*a < *b)
		this->_data.push(a);
	else
		this->_data.push(b);
}

void			Memory::maxValue(void)
{
	if (this->_data.size() < 2)
		throw std::runtime_error("Stack capacity is lower than 2");

	auto	a = this->_data.top();
	this->_data.pop();
	auto	b = this->_data.top();
	this->_data.pop();

	if (*a > *b)
		this->_data.push(a);
	else
		this->_data.push(b);
}

void			Memory::avgValue(void)
{
	if (this->_data.size() < 2)
		throw std::runtime_error("Stack capacity is lower than 2");

	auto	a = this->_data.top();
	this->_data.pop();
	auto	b = this->_data.top();
	this->_data.pop();

	const IOperand	* result = b->avg(*a);

	this->_data.push(std::shared_ptr<const IOperand>(result));
}

void			Memory::powValue(void)
{
	if (this->_data.size() < 2)
		throw std::runtime_error("Stack capacity is lower than 2");

	auto	a = this->_data.top();
	this->_data.pop();
	auto	b = this->_data.top();
	this->_data.pop();

	const IOperand	* result = b->pow(*a);

	this->_data.push(std::shared_ptr<const IOperand>(result));
}

void			Memory::incValue(void)
{
	if (this->_data.size() < 1)
		throw std::runtime_error("Stack is empty");

	auto	a = this->_data.top();
	this->_data.pop();

	const IOperand	* result = *a + *this->createOperand(IOperand::Int8, "1");

	this->_data.push(std::shared_ptr<const IOperand>(result));
}

void			Memory::decValue(void)
{
	if (this->_data.size() < 1)
		throw std::runtime_error("Stack is empty");

	auto	a = this->_data.top();
	this->_data.pop();

	const IOperand	* result = *a - *this->createOperand(IOperand::Int8, "1");

	this->_data.push(std::shared_ptr<const IOperand>(result));
}

void			Memory::clearStack(void)
{
	if (this->_data.size() < 1)
		throw std::runtime_error("Stack is empty");

	while (!this->_data.empty())
		this->_data.pop();
}

void			Memory::dump(void)
{
	for (auto tmp = this->_data; !tmp.empty(); tmp.pop())
		std::cout << tmp.top()->toString() << std::endl;
}

void			Memory::print(void)
{
	if (this->_data.size() < 1)
		throw std::runtime_error("Stack is empty");

	std::shared_ptr<const IOperand>	* val = &this->_data.top();
	std::unordered_map < IOperand::eOperandType, std::string > types = {
		{IOperand::Int16, "int16"}, {IOperand::Int32, "int32"},
		{IOperand::Float, "float"}, {IOperand::Double, "double"},
	};

	if ((*val)->getType() != IOperand::Int8)
		throw std::runtime_error((std::string("Can't print element of type ") + types[(*val)->getType()]).c_str());
	std::cout << static_cast<char>(dynamic_cast < const Operand < int8_t > * > (val->get())->getValue());
}

void			Memory::pop(void)
{
	if (this->_data.size() < 1)
		throw std::runtime_error("Stack is empty");
	this->_data.pop();
}

void			Memory::pushValue(const IOperand * op)
{
	if (op != NULL)
		this->_data.push(std::shared_ptr<const IOperand>(op));
}


void			Memory::assertValue(const IOperand * op) const
{
	if (this->_data.size() < 1)
		throw std::runtime_error("Stack is empty");
	if (op != NULL && *op == *this->_data.top())
		return ;
}

void			Memory::runtimeOverflow(long double value, IOperand::eOperandType type) const
{
	if (type == IOperand::Float && (value < std::numeric_limits<float>::lowest() || value > std::numeric_limits<float>::max()))
		throw std::out_of_range((std::string("Overflow detected. Range (")
			+ std::to_string(std::numeric_limits<float>::lowest()) + "; "
			+ std::to_string(std::numeric_limits<float>::max()) + ")").c_str());
	else if (type == IOperand::Double && (value < std::numeric_limits<double>::lowest() || value > std::numeric_limits<double>::max()))
		throw std::out_of_range((std::string("Overflow detected. Range (")
			+ std::to_string(std::numeric_limits<double>::lowest()) + "; "
			+ std::to_string(std::numeric_limits<double>::max()) + ")").c_str());
}

void			Memory::runtimeOverflow(long long value, IOperand::eOperandType type) const
{
	if (type == IOperand::Int8 && value != std::clamp(static_cast<int32_t>(value), INT8_MIN, INT8_MAX))
		throw std::out_of_range((std::string("Overflow detected. Range (")
			+ std::to_string(INT8_MIN) + "; " + std::to_string(INT8_MAX) + ")").c_str());
	else if (type == IOperand::Int16 && value != std::clamp(static_cast<int32_t>(value), INT16_MIN, INT16_MAX))
		throw std::out_of_range((std::string("Overflow detected. Range (")
			+ std::to_string(INT16_MIN) + "; " + std::to_string(INT16_MAX) + ")").c_str());
	else if (type == IOperand::Int32 && (value < INT32_MIN || value > INT32_MAX))
		throw std::out_of_range((std::string("Overflow detected. Range (")
			+ std::to_string(INT32_MIN) + "; " + std::to_string(INT32_MAX) + ")").c_str());
}

const IOperand	*Memory::createOperand(IOperand::eOperandType type, std::string const & value) const
{
	IOperand																	*ret = NULL;
	std::unordered_map < IOperand::eOperandType, std::unique_ptr < IOperand > >	fabric;
	static std::unordered_map < IOperand::eOperandType, memoryValueFunc >		initialize = {
		{IOperand::Int8, reinterpret_cast < memoryValueFunc > (&Memory::_parse_int8)},
		{IOperand::Int16, reinterpret_cast < memoryValueFunc > (&Memory::_parse_int16)},
		{IOperand::Int32, reinterpret_cast < memoryValueFunc > (&Memory::_parse_int32)},
		{IOperand::Float, reinterpret_cast < memoryValueFunc > (&Memory::_parse_float)},
		{IOperand::Double, reinterpret_cast < memoryValueFunc > (&Memory::_parse_double)}
	};

	fabric[IOperand::Int8] = std::make_unique < Operand < int8_t > > ();
	fabric[IOperand::Int16] = std::make_unique < Operand < int16_t > > ();
	fabric[IOperand::Int32] = std::make_unique < Operand < int32_t > > ();
	fabric[IOperand::Float] = std::make_unique < Operand < float > > ();
	fabric[IOperand::Double] = std::make_unique < Operand < double > > ();

	this->_check_value(value, type);
	ret = fabric[type].release();
	(this->*(initialize[type]))(value, ret);

	return (ret);
}

void			Memory::_check_value(std::string const & value, IOperand::eOperandType type) const
{
	if (value.empty())
		throw std::invalid_argument("Enter value");
	else if (std::regex_search(value, std::regex("[^0-9.+-]")))
		throw std::invalid_argument("Use only digits, dots and signs for value");
	else if (static_cast<int>(type) < 3 && value.find('.') != std::string::npos)
		throw std::invalid_argument("A floating point not allowed for integer types");
	else if (std::regex_match(value, std::regex("([+-])?([0-9]+)(\\.[0-9]+)?")) == false)
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
		op->memptr = this;
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
		op->memptr = this;
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
		op->memptr = this;
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
		op->memptr = this;
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
		op->memptr = this;
	}
	catch (std::exception & e)
	{
		throw std::invalid_argument((std::string("Argument overflow detected. Range (")
			+ std::to_string(std::numeric_limits<double>::lowest()) + "; "
			+ std::to_string(std::numeric_limits<double>::max()) + ")").c_str());
	}
}
