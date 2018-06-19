/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPU.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:34:57 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/19 21:16:42 by pgritsen         ###   ########.fr       */
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

	private:
		Memory	_stack;
		IO		_io;
};

#endif
