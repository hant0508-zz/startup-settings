#ifndef AUTOSTART_HPP
#define AUTOSTART_HPP

#include <map>
#include <string>

class Item;

class Autostart
{
public:
	Autostart();

	std::string file_name (Item & it) const;
	void scan_folder ();
	bool add_element (Item &it);
	void remove_element (const std::string &id);

	std::map<std::string, Item> get_list () const { return list_; }

private:
	std::map<std::string, Item> list_;
};

#endif // AUTOSTART_HPP
