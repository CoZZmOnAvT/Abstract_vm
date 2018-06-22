/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Memory.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:46:20 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/22 19:04:18 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_HPP
# define MEMORY_HPP

#include "avm.hpp"
#include "Operand.hpp"

class Memory
{
	public:
		Memory();
		~Memory();

		const IOperand	*createOperand(IOperand::eOperandType type, std::string const & value) const;
		void			addValue(const IOperand * op);
	private:
		std::vector < const IOperand * > _data;

		void			_check_value(std::string const & value, IOperand::eOperandType type) const;

		void			_parse_int8(std::string const & value, Operand <int8_t> * op) const;
		void			_parse_int16(std::string const & value, Operand <int16_t> * op) const;
		void			_parse_int32(std::string const & value, Operand <int32_t> * op) const;
		void			_parse_float(std::string const & value, Operand <float> * op) const;
		void			_parse_double(std::string const & value, Operand <double> * op) const;
};

#endif
