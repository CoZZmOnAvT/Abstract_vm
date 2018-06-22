/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPU.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:34:57 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/22 12:57:40 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_HPP
# define CPU_HPP

# include "avm.hpp"
# include "Memory.hpp"
# include "IO.hpp"

class CPU
{
	public:
		CPU(void);
		~CPU(void);

		void	start(int ac, char *av[]);
		void	analyze(const std::string & s);

	private:
		Memory	_stack;
		IO		_io;

		void	_action(std::string cmd);
		void	_action(std::string cmd, std::string type, std::string value);
};

#endif
