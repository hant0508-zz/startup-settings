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
	void create_list (GtkWidget *listbox, const std::map<std::string, Item> &items);
	void create_row (const Item &it, int pos);
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
