#include "item.hpp"
#include <cstdio>

Item::Item (std::string cmd, std::string name, std::string comment, bool term)
{
	set_cmd (cmd);
	set_name (name);
	set_comment (comment);
	set_term (term);
}

void Item::set_cmd (std::string cmd)
{
	cmd_ = cmd;
}

void Item::set_name (std::string name)
{
	name_ = name;
}

void Item::set_comment (std::string comment)
{
	comment_ = comment; // TODO
}

void Item::set_term (bool term)
{
	term_ = (term ? std::string ("true") : std::string ("false"));
}

void Item::set_id (std::string id)
{
	id_ = id;
}
