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
