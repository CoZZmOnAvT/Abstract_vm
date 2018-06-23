/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:48:36 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/23 19:08:48 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "avm.hpp"
#include "IOperand.hpp"

template <typename T>
class	Operand : public IOperand
{
	public:
		Operand();
		Operand(const Operand < T > & obj) { *this = obj; };
		virtual ~Operand() {};

		const Memory		* memptr;

		Operand < T >		& operator = (const Operand < T > & obj)
		{
			this->memptr = obj.memptr;
			this->_type = obj._type;
			this->_value = obj._value;
			return (*this);
		};

		int					getPrecision(void) const { return (static_cast<int>(this->_type)); };

		eOperandType		getType(void) const { return (this->_type); };
		T					getValue(void) const { return (this->_value); };
		long long			getValueInt(const IOperand * op) const;
		long double			getValueFloat(const IOperand * op) const;

		void				setValue(T v) { this->_value = v; }

		bool				operator == (IOperand const & rhs) const
		{
			auto	ptr1 = dynamic_cast < const Operand < int8_t > * >(&rhs);
			auto	ptr2 = dynamic_cast < const Operand < int16_t > * >(&rhs);
			auto	ptr3 = dynamic_cast < const Operand < int32_t > * >(&rhs);
			auto	ptr4 = dynamic_cast < const Operand < float > * >(&rhs);
			auto	ptr5 = dynamic_cast < const Operand < double > * >(&rhs);

			auto	compare = [&](auto *op) -> bool {
				if (op->getType() != this->getType())
					throw std::runtime_error("Assertion wrong. Types are not equal");
				else if (op->getValue() != this->getValue())
					throw std::runtime_error("Assertion wrong. Different values");
				return (true);
			};

			if (ptr1)
				return (compare(ptr1));
			else if (ptr2)
				return (compare(ptr2));
			else if (ptr3)
				return (compare(ptr3));
			else if (ptr4)
				return (compare(ptr4));
			else if (ptr5)
				return (compare(ptr5));
			else
				throw std::runtime_error("Unknown error");
		}

		const IOperand		* operator + (IOperand const & rhs) const
		{
			IOperand::eOperandType	type = static_cast<IOperand::eOperandType>(std::max(this->getPrecision(), rhs.getPrecision()));

			if (type == IOperand::Float || type == IOperand::Double)
			{
				long double	result = static_cast<long double>(this->getValue()) + this->getValueFloat(&rhs);
				this->memptr->runtimeOverflow(result, type);
				return (this->memptr->createOperand(type, std::to_string(result)));
			}
			else
			{
				long long	result = static_cast<long long>(this->getValue()) + this->getValueInt(&rhs);
				this->memptr->runtimeOverflow(result, type);
				return (this->memptr->createOperand(type, std::to_string(result)));
			}
		}

		const IOperand		* operator - (IOperand const & rhs) const
		{
			IOperand::eOperandType	type = static_cast<IOperand::eOperandType>(std::max(this->getPrecision(), rhs.getPrecision()));

			if (type == IOperand::Float || type == IOperand::Double)
			{
				long double	result = static_cast<long double>(this->getValue()) - this->getValueFloat(&rhs);
				this->memptr->runtimeOverflow(result, type);
				return (this->memptr->createOperand(type, std::to_string(result)));
			}
			else
			{
				long long	result = static_cast<long long>(this->getValue()) - this->getValueInt(&rhs);
				this->memptr->runtimeOverflow(result, type);
				return (this->memptr->createOperand(type, std::to_string(result)));
			}
		}

		const IOperand		* operator * (IOperand const & rhs) const
		{
			IOperand::eOperandType	type = static_cast<IOperand::eOperandType>(std::max(this->getPrecision(), rhs.getPrecision()));

			if (type == IOperand::Float || type == IOperand::Double)
			{
				long double	result = static_cast<long double>(this->getValue()) * this->getValueFloat(&rhs);
				this->memptr->runtimeOverflow(result, type);
				return (this->memptr->createOperand(type, std::to_string(result)));
			}
			else
			{
				long long	result = static_cast<long long>(this->getValue()) * this->getValueInt(&rhs);
				this->memptr->runtimeOverflow(result, type);
				return (this->memptr->createOperand(type, std::to_string(result)));
			}
		}

		const IOperand		* operator / (IOperand const & rhs) const
		{
			IOperand::eOperandType	type = static_cast<IOperand::eOperandType>(std::max(this->getPrecision(), rhs.getPrecision()));

			if (type == IOperand::Float || type == IOperand::Double)
			{
				long double	b =  this->getValueFloat(&rhs);
				if (b == 0)
					throw std::runtime_error("Division by zero detected");
				long double	result = static_cast<long double>(this->getValue()) / b;
				this->memptr->runtimeOverflow(result, type);
				return (this->memptr->createOperand(type, std::to_string(result)));
			}
			else
			{
				long long	b = this->getValueInt(&rhs);
				if (b == 0)
					throw std::runtime_error("Division by zero detected");
				long long	result = static_cast<long long>(this->getValue()) / b;
				this->memptr->runtimeOverflow(result, type);
				return (this->memptr->createOperand(type, std::to_string(result)));
			}
		}

		const IOperand		* operator % (IOperand const & rhs) const
		{
			IOperand::eOperandType	type = static_cast<IOperand::eOperandType>(std::max(this->getPrecision(), rhs.getPrecision()));

			if (type == IOperand::Float || type == IOperand::Double)
				throw std::runtime_error("Invalid operands to binary expression");
			else
			{
				long long	b = this->getValueInt(&rhs);
				if (b == 0)
					throw std::runtime_error("Division by zero detected");
				long long	result = static_cast<long long>(this->getValue()) % b;
				this->memptr->runtimeOverflow(result, type);
				return (this->memptr->createOperand(type, std::to_string(result)));
			}
		}

		const std::string 	& toString(void) const
		{
			static														std::string	val;
			char														buf[1024];
			std::unordered_map < IOperand::eOperandType, const char * >	flags = {
				{IOperand::Int8, "%hhd"}, {IOperand::Int16, "%hd"},
				{IOperand::Int32, "%d"}, {IOperand::Float, "%g"},
				{IOperand::Double, "%g"}
			};

			sprintf(buf, flags[this->_type], this->_value);
			return (val.assign(buf));
		}

	private:
		IOperand::eOperandType	_type;
		T						_value;
};

template <typename T>
Operand<T>::Operand()
{
	std::unordered_map<std::type_index, IOperand::eOperandType>	type_names = {
		{std::type_index(typeid(int8_t)),	IOperand::Int8	},
		{std::type_index(typeid(int16_t)),	IOperand::Int16	},
		{std::type_index(typeid(int32_t)),	IOperand::Int32	},
		{std::type_index(typeid(float)),	IOperand::Float	},
		{std::type_index(typeid(double)),	IOperand::Double}
	};

	if (type_names.find(std::type_index(typeid(T))) != type_names.end())
		this->_type = type_names[std::type_index(typeid(T))];
}

template <typename T>
long long		Operand<T>::getValueInt(const IOperand * op) const
{
	auto	ptr1 = dynamic_cast < const Operand < int8_t > * >(op);
	auto	ptr2 = dynamic_cast < const Operand < int16_t > * >(op);
	auto	ptr3 = dynamic_cast < const Operand < int32_t > * >(op);
	auto	ptr4 = dynamic_cast < const Operand < float > * >(op);
	auto	ptr5 = dynamic_cast < const Operand < double > * >(op);

	if (ptr1)
		return (static_cast<long long>(ptr1->getValue()));
	else if (ptr2)
		return (static_cast<long long>(ptr2->getValue()));
	else if (ptr3)
		return (static_cast<long long>(ptr3->getValue()));
	else if (ptr4)
		return (static_cast<long long>(ptr4->getValue()));
	else if (ptr5)
		return (static_cast<long long>(ptr5->getValue()));
	else
		throw std::runtime_error("Unknown error");
}

template <typename T>
long double		Operand<T>::getValueFloat(const IOperand * op) const
{
	auto	ptr1 = dynamic_cast < const Operand < int8_t > * >(op);
	auto	ptr2 = dynamic_cast < const Operand < int16_t > * >(op);
	auto	ptr3 = dynamic_cast < const Operand < int32_t > * >(op);
	auto	ptr4 = dynamic_cast < const Operand < float > * >(op);
	auto	ptr5 = dynamic_cast < const Operand < double > * >(op);

	if (ptr1)
		return (static_cast<long double>(ptr1->getValue()));
	else if (ptr2)
		return (static_cast<long double>(ptr2->getValue()));
	else if (ptr3)
		return (static_cast<long double>(ptr3->getValue()));
	else if (ptr4)
		return (static_cast<long double>(ptr4->getValue()));
	else if (ptr5)
		return (static_cast<long double>(ptr5->getValue()));
	else
		throw std::runtime_error("Unknown error");
}

#endif
