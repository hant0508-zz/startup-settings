#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item
{
public:
	Item (std::string cmd, std::string name, std::string comment, bool term);

	void set_cmd (std::string cmd);
	void set_name (std::string name);
	void set_comment (std::string comment);
	void set_term (bool term);

	void set_id (std::string id);

	std::string get_cmd () const { return cmd_; }
	std::string get_name () const { return name_; }
	std::string get_comment () const { return comment_; }
	std::string get_term () const { return term_; }

	std::string get_id () const { return id_; }

private:
	std::string cmd_, name_, comment_, term_, id_;
};

#endif // ITEM_HPP
