/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:46:12 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/23 19:08:59 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_HPP
# define IO_HPP

#include "avm.hpp"

class CPU;

class IO
{
	public:
		IO(void);
		IO(const IO & elem);
		virtual ~IO(void);

		IO	& operator = (const IO & elem);

		bool	verbose;
		bool	quit;

		void	parse(std::string file_name, CPU & cpu);
		void	parse(CPU & cpu);
		void	reset_state(void);

	private:
		size_t		_line;
		size_t		_cmds;
		std::string	_source_name;

		std::string					& _trim(std::string & s);
		std::vector<std::string>	_explode(const std::string & s, char delim);
		void						_analyze_flags(std::string file_name);
		void						_display_usage(void);
		void						_display_usage(std::string msg);
};

#endif
