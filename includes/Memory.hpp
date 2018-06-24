/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Memory.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:46:20 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/24 18:42:00 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_HPP
# define MEMORY_HPP

#include "avm.hpp"
#include "IOperand.hpp"

template <typename T>
class	Operand;

class Memory
{
	public:
		Memory();
		Memory(const Memory & obj);
		virtual ~Memory();

		Memory			& operator = (const Memory & obj);

		const IOperand	*createOperand(IOperand::eOperandType type, std::string const & value) const;
		void			addValue(void);
		void			subValue(void);
		void			mulValue(void);
		void			divValue(void);
		void			modValue(void);
		void			minValue(void);
		void			maxValue(void);
		void			avgValue(void);
		void			powValue(void);
		void			incValue(void);
		void			decValue(void);
		void			clearStack(void);
		void			dump(void);
		void			print(void);
		void			pop(void);
		void			pushValue(const IOperand * op);
		void			assertValue(const IOperand * op) const;
		void			runtimeOverflow(long double value, IOperand::eOperandType type) const;
		void			runtimeOverflow(long long value, IOperand::eOperandType type) const;
	private:
		std::deque < std::unique_ptr<const IOperand> > _data;

		void			_check_value(std::string const & value, IOperand::eOperandType type) const;

		void			_parse_int8(std::string const & value, Operand <int8_t> * op) const;
		void			_parse_int16(std::string const & value, Operand <int16_t> * op) const;
		void			_parse_int32(std::string const & value, Operand <int32_t> * op) const;
		void			_parse_float(std::string const & value, Operand <float> * op) const;
		void			_parse_double(std::string const & value, Operand <double> * op) const;
};

#endif
