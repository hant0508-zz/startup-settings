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

#include <gtk/gtk.h>

#include "gui.hpp"
#include "fs.hpp"
#include "item.hpp"
#include "util.hpp"

extern "C" void on_remove_clicked (GtkButton *button, gpointer row);

void GUI::create_window() const
{
	GtkBuilder *builder; 
	builder = gtk_builder_new();

	std::string path;
	if (fs::exists (std::string ("gui.glade"), true))
		path = std::string ("gui.glade");
	else if (fs::exists (std::string ("src/gui.glade"), true))
		path = std::string ("src/gui.glade");
	else path = S_SETTINGS_PATH;

	if (!fs::exists (path)) exit (1);

	gtk_builder_add_from_file (builder, path.c_str(), NULL);
	gtk_builder_connect_signals (builder, NULL);

	GtkWidget *window;
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));

	if (!window) exit (1);
	gtk_window_set_title (GTK_WINDOW (window), "Startup Settings");
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_widget_show (window);
}

void GUI::create_list (GtkWidget *listbox, const std::map<std::string, Item> &items)
{
	list_ = listbox;

	for (auto i = items.begin(); i != items.end(); ++i)
		create_row (i->second, -1);

	gtk_widget_show_all (list_);
}

void GUI::create_row (const Item &it, int pos)
{
	std::string sname = it.get_name();
	std::string scmd = it.get_cmd();
	std::string scomment = it.get_comment();
	std::string sid = it.get_id ();
	const gchar *name = sname.c_str(); 
	const gchar *cmd = scmd.c_str(); 
	const gchar *comment = scomment.c_str(); 
	const gchar *id = sid.c_str(); 

	GtkWidget *row = gtk_list_box_row_new();
	GtkWidget *grid = gtk_grid_new();
	GtkWidget *box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	GtkWidget *button = gtk_button_new_with_label ("Remove");
	GtkWidget *l1 = gtk_label_new (name);
	GtkWidget *l2 = gtk_label_new (cmd);
	GtkWidget *l3 = gtk_label_new (comment);

	gtk_widget_set_halign (l1, GTK_ALIGN_START);
	gtk_widget_set_halign (l2, GTK_ALIGN_START);
	gtk_widget_set_halign (l3, GTK_ALIGN_START);

	PangoAttrList *atl = pango_attr_list_new();
	pango_attr_list_change (atl, pango_attr_weight_new (PANGO_WEIGHT_SEMIBOLD));
	pango_attr_list_change (atl, pango_attr_size_new (17000));
	gtk_label_set_attributes (GTK_LABEL (l1), atl);

	gtk_label_set_line_wrap (GTK_LABEL (l3), true);
	gtk_label_set_line_wrap_mode (GTK_LABEL (l3), PANGO_WRAP_CHAR);
	gtk_label_set_line_wrap (GTK_LABEL (l2), true);
	gtk_label_set_line_wrap_mode (GTK_LABEL (l2), PANGO_WRAP_CHAR);

	gtk_label_set_selectable (GTK_LABEL (l1), true);
	gtk_label_set_selectable (GTK_LABEL (l2), true);
	gtk_label_set_selectable (GTK_LABEL (l3), true);

	gtk_container_add (GTK_CONTAINER (box), l1);
	gtk_container_add (GTK_CONTAINER (box), l2);
	gtk_container_add (GTK_CONTAINER (box), l3);

	gtk_widget_set_hexpand (button, true);
	gtk_widget_set_halign (button, GTK_ALIGN_END);

	gtk_grid_attach (GTK_GRID (grid), box, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);
	gtk_widget_set_margin_start (grid, 3);
	gtk_widget_set_margin_end (grid, 3);
	gtk_widget_set_margin_top (grid, 2);

	gtk_widget_set_name (row, id);

	gtk_container_add (GTK_CONTAINER (row), grid);
	gtk_list_box_insert (GTK_LIST_BOX (list_), row, pos);

	g_signal_connect (button, "clicked", G_CALLBACK (on_remove_clicked), row);

	gtk_widget_show_all (list_);
}

void GUI::remove_row (GtkWidget *row)
{
	gtk_container_remove (GTK_CONTAINER (list_), row);
	gtk_widget_show_all (list_);
}

void GUI::fill_entries (GtkWidget *box)
{
	GtkWidget *wcmd, *wname, *wcomment, *wterm;

	find_child (box, &wcmd, "command");
	find_child (box, &wname, "name");
	find_child (box, &wcomment, "comment");
	find_child (box, &wterm, "terminal");

	std::string cmd = gtk_entry_get_text (GTK_ENTRY (wcmd));
	if (cmd == S_SPACE) cmd = S_EMPTY;
	else if (cmd.substr(0, 7) == S_LOCAL_FILE) cmd = cmd.substr(7);

	for (size_t i = 1; i < cmd.size(); ++i)
		if ((cmd.at(i) == '(' || cmd.at(i) == ')') && cmd.at(i - 1) != '\\')
		{
			cmd.insert(i, 1, '\\');
			++i;
		}

	cmd = regex_replace (cmd, std::regex("%20"), "\\ ");
	cmd = regex_replace (cmd, std::regex("\n"), "");
	cmd = regex_replace (cmd, std::regex("\r"), "");

	std::string name = cmd;
	std::string comment = S_EMPTY;

	bool active = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (wterm));
	std::string term = (active ? std::string (" in terminal") : S_EMPTY);

	if (!name.empty() && name.at(0) == '/') name.erase(0, 1);

	for (size_t i = 1; i < name.size(); ++i)
	{
		if (name.at(i) == '/' && (name.at(i - 1) == ' ' || name.at(i - 1) == '\"'))
			break;

		else if (name.at(i) == '/' && name.at(i - 1) != ' ' && name.at(i - 1) != '\"')
		{
			name = name.substr (i + 1);
			i = 0;
		}
	}

	if (name_is_edited_) name = gtk_entry_get_text (GTK_ENTRY (wname));
	if (name != S_EMPTY) comment = std::string ("Run ") + name + term;

	gtk_entry_set_text (GTK_ENTRY (wcmd), cmd.c_str()); 
	if (!comment_is_edited_) gtk_entry_set_text (GTK_ENTRY (wcomment), comment.c_str()); 
	gtk_entry_set_text (GTK_ENTRY (wname), name.c_str());
}

void GUI::reset_entries (GtkWidget *box)
{
	name_is_edited_ = false;
	comment_is_edited_ = false;

	GtkWidget *wcmd, *wname, *wcomment;
	find_child (box, &wcmd, "command");
	find_child (box, &wname, "name");
	find_child (box, &wcomment, "comment");

	gtk_entry_set_text (GTK_ENTRY (wcmd), "");
	gtk_entry_set_text (GTK_ENTRY (wname), "");
	gtk_entry_set_text (GTK_ENTRY (wcomment), "");
}

void GUI::entry_changed (const gchar *name)
{
	if (std::string (name) == std::string ("name"))
		name_is_edited_ = true;
	else comment_is_edited_ = true;
}

void GUI::find_child (GtkWidget *parent, GtkWidget **aim, const gchar *name) const
{
	if (std::string(gtk_widget_get_name (parent)) == std::string(name))
		*aim = parent;

	else if (GTK_IS_BIN (parent))
	{
		GtkWidget *child = gtk_bin_get_child (GTK_BIN(parent));
		find_child (child, aim, name);
	}

	else if (GTK_IS_CONTAINER (parent))
	{
		GList *children = gtk_container_get_children (GTK_CONTAINER (parent));
		while (children != NULL)
		{
			GtkWidget *child = GTK_WIDGET(children->data);
			find_child (child, aim, name);
			children = g_list_next (children);
		}
	}
}
