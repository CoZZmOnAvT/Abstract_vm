/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:46:12 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/19 21:20:30 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_HPP
# define IO_HPP

#include "avm.hpp"
#include "Memory.hpp"

class IO
{
	public:
		IO(void);
		~IO(void);

		void	parse_file(const char *file_name, Memory & stack);
		void	parse_stdi(Memory & stack);

	private:
		CPU		&_cpu;
		IO();
};

#endif
