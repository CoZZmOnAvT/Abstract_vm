/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPU.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:34:57 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/23 19:12:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_HPP
# define CPU_HPP

# include "avm.hpp"
# include "Memory.hpp"
# include "Operand.hpp"
# include "IO.hpp"

class CPU
{
	public:
		CPU(void);
		CPU(const CPU & elem);
		virtual ~CPU(void);

		CPU	& operator = (const CPU & elem);

		void	start(int ac, char *av[]);
		void	analyze(const std::string & s);

	private:
		Memory	_stack;
		IO		_io;

		void	_action(std::string cmd);
		void	_action(std::string cmd, std::string type, std::string value);
};

#endif
