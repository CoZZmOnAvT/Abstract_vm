/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 20:30:49 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/19 20:41:19 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

enum	eOperandType
{
	INT8, INT16, INT32, FLOAT, DOUBLE
};

class IOperand
{
	public:
		virtual ~IOperand(void) {}

		virtual int getPrecision(void) const = 0;
		virtual eOperandType getType(void) const = 0;
		virtual IOperand const * operator + (IOperand const & rhs) const = 0;
		virtual IOperand const * operator - (IOperand const & rhs) const = 0;
		virtual IOperand const * operator * (IOperand const & rhs) const = 0;
		virtual IOperand const * operator / (IOperand const & rhs) const = 0;
		virtual IOperand const * operator % (IOperand const & rhs) const = 0;
		virtual std::string const & toString(void) const = 0;
};

#endif
