#include <iostream>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include "fs.hpp"

bool FS::exists (const std::string &file, bool silent = false) const
{
	bool ex = (access (file.c_str(), F_OK ) != -1);
	if (!ex && !silent) std::cerr << ERR_NF + file << std::endl;
	return ex;
}

void FS::cd (const std::string &path)
{
	WD_ = path;
}

void FS::print_vector (const std::vector<std::string> &results) const
{
	for (size_t i = 0; i < results.size(); ++i)
		std::cout << results.at(i) << std::endl;
}

void FS::fs_mkdir(const std::string &path) const
{
	if (!fs::exists (path, true))
		mkdir (path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

std::string FS::pwd () const
{
	return WD_;
}

std::string FS::home (const std::string &path) const
{
	std::string home = getpwuid (getuid())->pw_dir;
	return std::string (home + S_SLASH + path);
}

std::vector<std::string> FS::ls (const std::string &path) const
{
	std::vector<std::string> out;

	if (!exists (path))
	{
		out.push_back (ERR_NF + path);
		return out;
	}

	DIR *dir = opendir (path.c_str());
	struct dirent *ent;

	while ((ent = readdir (dir)) != NULL)
		out.push_back (std::string(ent->d_name));

	closedir (dir);
	return out;
}

std::vector<std::string> FS::find (const std::regex &mask, const std::string &path)
{
	std::vector<std::string> out, input = ls (path);

	if (!exists (path))
	{
		out.push_back (ERR_NF + path);
		return out;
	}

	for (size_t i = 0; i < input.size(); ++i)
		if (regex_match (input.at(i), mask))
		out.push_back (input.at(i));

	return out;
}

std::string FS::find_in_file (const std::regex &mask, const std::string &fname)
{
	if (!exists (fname)) return ERR_NF + fname;

	std::string out;
	std::ifstream input (fname);

	if (!input) return S_EMPTY;

	while (getline (input, out))
		if (regex_match (out, mask))
			return out;

	return S_EMPTY;
}

// namespace fs

bool fs::exists (const std::string &file, bool silent)
{
	return FS::inst().exists (file, silent);
}

void fs::cd (const std::string &path)
{
	FS::inst().cd (path);
}

void fs::print_vector (const std::vector<std::string> &results)
{
	FS::inst().print_vector (results);
}

void fs::mkdir(const std::string &path)
{
	FS::inst().fs_mkdir (path);
}

std::string fs::pwd ()
{
	return FS::inst().pwd();
}

std::string fs::home (const std::string &path)
{
   	return FS::inst().home (path);
}

std::vector<std::string> fs::ls (const std::string &path)
{
   	return FS::inst().ls (path);
}

std::vector<std::string> fs::find (const std::regex &mask, const std::string &path)
{
   	return FS::inst().find (mask, path);
}

std::string fs::find_in_file (const std::regex &mask, const std::string &fname)
{
	return FS::inst().find_in_file (mask, fname);
}
