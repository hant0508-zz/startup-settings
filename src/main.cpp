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
#include "autostart.hpp"
#include "item.hpp"

Autostart autostart;
GUI gui;

extern "C" void on_entry_key_press (GtkWidget *entry, GdkEvent*, gpointer box)
{
	gui.entry_changed (gtk_widget_get_name (GTK_WIDGET (entry)));
	gui.fill_entries (GTK_WIDGET (box));
}

extern "C" void on_entry_clipboard (GtkEntry *entry, gpointer box)
{
	gui.entry_changed (gtk_widget_get_name (GTK_WIDGET (entry)));
	gui.fill_entries (GTK_WIDGET (box));
}

extern "C" void on_command_changed (GtkEditable *entry, gpointer box)
{
	gui.fill_entries (GTK_WIDGET (box));
}

extern "C" void on_terminal_toggled (GtkToggleButton *term, gpointer box)
{
	gui.fill_entries (GTK_WIDGET (box));
}

extern "C" void on_remove_clicked (GtkButton *button, gpointer row)
{
	autostart.remove_element (gtk_widget_get_name (GTK_WIDGET (row)));
	gui.remove_row (GTK_WIDGET (row));
}

extern "C" void on_window_show (GtkWidget *window, gpointer listbox)
{
	gui.create_list (GTK_WIDGET (listbox), autostart.get_list());
}

extern "C" void on_command_clear_press (GtkEntry *cmd, GtkEntryIconPosition*, GdkEvent*, gpointer box)
{
	gtk_entry_set_text (cmd, "");
	gui.fill_entries (GTK_WIDGET (box));
}

extern "C" void on_entry_clear_press (GtkEntry *entry, GtkEntryIconPosition*, GdkEvent*, gpointer)
{
	gtk_entry_set_text (entry, "");
	gui.entry_changed (gtk_widget_get_name (GTK_WIDGET (entry)));
}

extern "C" void on_button_clicked (GtkButton *button, gpointer box)
{
	GtkWidget *wcmd, *wname, *wcomment, *wterm;

	gui.find_child (GTK_WIDGET (box), &wcmd, "command");
	gui.find_child (GTK_WIDGET (box), &wname, "name");
	gui.find_child (GTK_WIDGET (box), &wcomment, "comment");
	gui.find_child (GTK_WIDGET (box), &wterm, "terminal");

	const gchar *cmd = gtk_entry_get_text (GTK_ENTRY (wcmd));
	const gchar *name = gtk_entry_get_text (GTK_ENTRY (wname));
	const gchar *comment = gtk_entry_get_text (GTK_ENTRY (wcomment));
	const gboolean term = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (wterm));

	Item it (cmd, name, comment, term);

	if (!autostart.add_element (it)) return;
	gui.create_row (it, 0);
	gui.reset_entries (GTK_WIDGET (box));
}

int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	gui.create_window();

	gtk_main ();
}
