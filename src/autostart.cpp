/*
	Copyright (c) 2016 Dmitry Ivanov <hant0508@gmail.com>
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <vector>
#include <cstdio>
#include <fstream>

#include "item.hpp"
#include "autostart.hpp"
#include "fs.hpp"
#include "util.hpp"

Autostart::Autostart ()
{
	if  (!fs::exists (fs::home (S_CONFIG_PATH), true))
		fs::mkdir (fs::home (S_CONFIG_PATH));
	fs::cd (fs::home (S_CONFIG_PATH));
	scan_folder();
}

std::string Autostart::file_name (Item &it) const
{
	std::string fname = it.get_name() + S_EXTENSION;

	for (size_t i = 0; i < fname.size(); ++i)
		if (fname.at(i) == '/') fname.at(i) = '_';

	for (int i = 1; fs::exists (fs::pwd() + fname, true); ++i)
		fname = it.get_name() + std::to_string (i) + S_EXTENSION;

	it.set_id (fname);
	return fname;
}

bool Autostart::add_element (Item &it)
{
	if (it.get_cmd() == S_EMPTY) return false;
	if (it.get_name() == S_EMPTY) it.set_name ("unnamed");

	std::string fname = file_name (it);

	std::ofstream file (fs::pwd() + fname);

	file << "[Desktop Entry]\n";
	file << "Name=" << it.get_name() << "\n";
	file << "Comment=" << it.get_comment() << "\n";
	file << "Exec=" << it.get_cmd() << "\n";
	file << "Terminal=" << it.get_term() << "\n";
	file << "Type=Application";

	file.close();

	list_.emplace (std::make_pair (fname, it));

	return true;
}

void Autostart::remove_element (const std::string &id)
{
	std::remove (std::string (fs::pwd() + id).c_str());

	for (auto i = list_.begin(); i != list_.end(); ++i)
        if (i->first == id)
		{
			i = list_.erase (i);
			break;
		}
}

void Autostart::scan_folder ()
{
	std::vector<std::string> f, files;
	f = fs::ls();

	for (size_t i = 0; i < f.size(); ++i)
	{
		std::string fname = f.at(i);
		std::string test1 = fs::find_in_file (std::regex ("\\[Desktop Entry\\]"), fs::pwd() + fname);
		std::string test2 = fs::find_in_file (std::regex ("X\\-.*\\-Autostart\\-enabled=false"), fs::pwd() + fname);

		if (test1 != S_EMPTY && test2 == S_EMPTY) files.push_back (fname);
	}

	for (size_t i = 0; i < files.size(); ++i)
	{
		std::string cmd = fs::find_in_file (std::regex ("Exec=.*"), fs::pwd() + files.at(i));
		std::string name = fs::find_in_file (std::regex ("Name=.*"), fs::pwd() + files.at(i));
		std::string comment = fs::find_in_file (std::regex ("Comment=.*"), fs::pwd() + files.at(i));
		std::string sterm = fs::find_in_file (std::regex ("Terminal= *true"), fs::pwd() + files.at(i));

		if (cmd != S_EMPTY) cmd = cmd.substr (5);
		if (name != S_EMPTY) name = name.substr (5);
		if (comment != S_EMPTY) comment = comment.substr (8);
		bool term = (sterm == S_EMPTY ? false : true);

		Item it (cmd, name, comment, term);
		it.set_id (files.at(i));
		list_.emplace (std::make_pair (files.at(i), it));
	}
}
