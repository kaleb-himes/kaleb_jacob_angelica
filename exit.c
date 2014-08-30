/* Copyright 2014 Kaleb, Jacob, Third_person
 * 
 * This file is part of Artificially Intelligent Polar Tic Tac Toe game.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AI Polar Tic Tac Toe.  
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>
#include "exit.h"

gboolean delete_event (GtkWidget *widget, GdkEvent *event, gpointer data)
{
	
	return FALSE;
}

void destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}
