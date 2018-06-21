/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:46:12 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/21 20:08:59 by pgritsen         ###   ########.fr       */
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
		virtual ~IO(void);

		bool	verbose;

		void	parse(std::string file_name, CPU & cpu);
		void	parse(CPU & cpu);
		void	reset_state(void);

	private:
		bool		_exit_found;
		size_t		_line;
		std::string	_source_name;

		std::string					& _trim(std::string & s);
		std::vector<std::string>	_explode(const std::string & s, char delim);
		void						_analyze_flags(std::string file_name);
		void						_display_usage(void);
		void						_display_usage(std::string msg);
};

#endif
