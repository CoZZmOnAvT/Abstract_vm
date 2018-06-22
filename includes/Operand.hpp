/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:48:36 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/22 13:21:48 by pgritsen         ###   ########.fr       */
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
		virtual ~Operand() {};

	int				getPrecision(void) const { return (static_cast<int>(this->_type)); };

	eOperandType	getType(void) const { return (this->_type); };

	private:
		IOperand::eOperandType	_type;
		T						_value;
};

template <typename T>
Operand<T>::Operand()
{
	std::unordered_map<std::type_index, IOperand::eOperandType>	type_names;

	type_names[std::type_index(typeid(int8_t))] = IOperand::Int8;
	type_names[std::type_index(typeid(int16_t))] = IOperand::Int16;
	type_names[std::type_index(typeid(int32_t))] = IOperand::Int32;
	type_names[std::type_index(typeid(float))] = IOperand::Float;
	type_names[std::type_index(typeid(double))] = IOperand::Double;
	if (type_names.find(std::type_index(typeid(T))) != type_names.end())
		this->_type = type_names[std::type_index(typeid(T))];
}

#endif
