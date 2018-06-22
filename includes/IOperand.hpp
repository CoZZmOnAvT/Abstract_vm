/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 20:30:49 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/22 13:15:26 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

class IOperand
{
	public:
		virtual ~IOperand(void) {}

		enum eOperandType
		{
			Int8 = 0, Int16, Int32, Float, Double
		};

		virtual int getPrecision(void) const = 0;
		virtual eOperandType getType(void) const = 0;
		// virtual IOperand const * operator + (IOperand const & rhs) const = 0;
		// virtual IOperand const * operator - (IOperand const & rhs) const = 0;
		// virtual IOperand const * operator * (IOperand const & rhs) const = 0;
		// virtual IOperand const * operator / (IOperand const & rhs) const = 0;
		// virtual IOperand const * operator % (IOperand const & rhs) const = 0;
		// virtual std::string const & toString(void) const = 0;
};

#endif
