/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 12:48:36 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/22 16:32:55 by pgritsen         ###   ########.fr       */
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
	T				getValue(void) const;

	void			setValue(T v);

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
T		Operand<T>::getValue(void) const { return (this->_value); }

template <typename T>
void		Operand<T>::setValue(T v) { this->_value = v; }


#endif
