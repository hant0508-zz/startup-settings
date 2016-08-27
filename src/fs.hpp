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

#ifndef FS_HPP
#define FS_HPP

#include <string>
#include <vector>
#include <regex>
#include "util.hpp"

class FS
{
public:

	static FS& inst()
	{
		static FS fs;
		return fs;
	}

	bool exists (const std::string &file, bool silent) const;
	void cd (const std::string &path);
	void print_vector (const std::vector<std::string> &result) const;
	void fs_mkdir(const std::string &path) const;

	std::string pwd () const;
	std::string home (const std::string &path) const;
	std::vector<std::string> ls (const std::string &path) const;
	std::vector<std::string> find (const std::regex &mask, const std::string &path);
	std::string find_in_file (const std::regex &mask, const std::string &fname);

private:
	FS () {}
	FS (const FS&) {}
	FS& operator= (const FS&);

	std::string WD_;
};

namespace fs
{
bool exists (const std::string &file, bool silent = false);
void cd (const std::string &path = FS::inst().home (S_EMPTY));
void print_vector (const std::vector<std::string> &results);
void mkdir(const std::string &path);

std::string pwd ();
std::string home (const std::string &path = S_EMPTY);
std::vector<std::string> ls (const std::string &path = FS::inst().pwd());
std::vector<std::string> find (const std::regex &mask, const std::string &path = FS::inst().pwd());
std::string find_in_file (const std::regex &mask, const std::string &fname);

} // namespace fs

#endif // FS_HPP
