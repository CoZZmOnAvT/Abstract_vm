/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:45:21 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/19 21:24:15 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IO.hpp"

IO::IO(void) : _exit_found(false) {}
IO::~IO(void) {}

void	IO::parse_file(const char *file_name, Memory & stack)
{
	(void)file_name;
	(void)stack;
}

void	IO::parse_stdi(Memory & stack)
{
	(void)stack;
	(void)this->_exit_found;
}
