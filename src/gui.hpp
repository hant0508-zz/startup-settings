#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <map>

class Item;

class GUI
{
public:
	GUI(): name_is_edited_ (false), comment_is_edited_ (false) {}

	void create_window () const;
	void create_list (GtkWidget *listbox, std::map<std::string, Item>);
	void create_row (Item it, int pos);
	void remove_row (GtkWidget *row);
	void fill_entries (GtkWidget *box);
	void reset_entries (GtkWidget *box);

	void entry_changed (const gchar *name);
	void find_child (GtkWidget *parent, GtkWidget **aim, const gchar *name) const;

private:
	GtkWidget *list_;
	bool name_is_edited_, comment_is_edited_;
};

#endif // GUI_HPP
