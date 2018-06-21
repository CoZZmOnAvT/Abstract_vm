/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IO.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:45:21 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/21 20:14:13 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IO.hpp"
#include "CPU.hpp"

IO::IO(void) : verbose(true), _exit_found(false), _line(0) {}
IO::~IO(void)
{
	if (this->verbose)
	{
		if (this->_line == 0)
			std::cout << "AVM: Warning: Empty input" << std::endl;
		else if (this->_exit_found == false)
			std::cout << "AVM: Fatal Error: No exit statement found!" << std::endl;
	}
}

void						IO::parse(std::string file_name, CPU & cpu)
{
	this->_analyze_flags(this->_trim(file_name));

	std::ifstream				file;
	std::vector<std::string>	file_parts = this->_explode(file_name, '.');

	this->_source_name = file_name;
	if (this->verbose && (file_parts.size() < 2 || file_parts.back() != "avm"))
		std::cout << "AVM: Warning: Incorrect file extension" << std::endl;
	file.open(file_name);
	if (file.good())
	{
		std::string		line;

		while (getline(file, line))
			try
			{
				this->_line++;
				cpu.analyze(this->_trim(line));
			}
			catch (std::exception & e)
			{
				if (this->verbose)
					std::cout << "AVM: '" << file_name << "': Line " << this->_line << ": " << e.what() << std::endl;
			}
	}
	else if (this->verbose)
		std::cout << "AVM: " << file_name << ": No such file or directory!" << std::endl;
	file.close();
}

void						IO::parse(CPU & cpu)
{
	(void)cpu;
	this->_source_name.erase(this->_source_name.begin(), this->_source_name.end());
}

void						IO::reset_state(void)
{
	this->_line = 0;
	this->_exit_found = 0;
}

std::string					& IO::_trim(std::string & s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
				std::not1(std::ptr_fun<int, int>(std::isspace))));
	s.erase(std::find_if(s.rbegin(), s.rend(),
				std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return (s);
}

std::vector<std::string>	IO::_explode(const std::string & s, char delim)
{
	std::vector<std::string>	ret;
	std::istringstream			iss(s);

	for (std::string token; std::getline(iss, token, delim); )
		ret.push_back(std::move(token));

	return (ret);
}

void						IO::_analyze_flags(std::string file_name)
{
	const static std::vector < std::tuple < char, bool &, bool > >			flags = {
		{'s', this->verbose, false}
	};
	const static std::vector < std::pair < std::string, void (IO::*)() > >	complicated_flags = {
		{"help", &IO::_display_usage}
	};

	if (file_name[0] == '-' && file_name[1] == '-')
	{
		std::string	flag_name = file_name.substr(2);
		auto	it = std::find_if(complicated_flags.begin(), complicated_flags.end(), [&flag_name](const std::pair < std::string, void (IO::*)() > & flag){ return (flag.first == flag_name); });
		if (it != complicated_flags.end())
			(this->*((*it).second))();
		else
			this->_display_usage(std::string("Fatal Error: ") + "Illegal option -- \"" + flag_name + "\"");
	}
	else if (file_name[0] == '-')
	{
		for (size_t j = 1; j < file_name.size(); j++)
		{
			auto	it = std::find_if(flags.begin(), flags.end(), [&file_name, &j](const std::tuple < char, bool &, bool > & flag){ return (std::get<0>(flag) == file_name[j]); });
			if (it != flags.end())
				std::get<1>(*it) = std::get<2>(*it);
			else
				this->_display_usage(std::string("Fatal Error: ") + "Illegal option -- '" + file_name[j] + "'");
		}
	}
}

void						IO::_display_usage(void)
{
	std::cout << "Usage: ./avm [-s | --help] [file_name ...]" << std::endl;
	throw std::logic_error("");
}

void						IO::_display_usage(std::string msg)
{
	std::cout << "Usage: ./avm [-s | --help] [file_name ...]" << std::endl;
	throw std::logic_error(msg.c_str());
}
