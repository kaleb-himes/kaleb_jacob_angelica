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

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "exit.h"
#include "winlogic.h"
#include "initboard.h"

void set_up_board ();

int i_location [2];
char board_location[19][19] = {
 {'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N'},
 {'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N'},
 {'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N'},
 {'N','N','N','N','E','N','N','N','N','E','N','N','N','N','E','N','N','N','N'},
 {'N','N','N','E','N','E','N','N','N','E','N','N','N','E','N','E','N','N','N'},
 {'N','N','N','N','E','N','E','N','N','E','N','N','E','N','E','N','N','N','N'},
 {'N','N','N','N','N','E','N','E','N','E','N','E','N','E','N','N','N','N','N'},
 {'N','N','N','N','N','N','E','N','E','E','E','N','E','N','N','N','N','N','N'},
 {'N','N','N','N','N','N','N','E','N','N','N','E','N','N','N','N','N','N','N'},
 {'N','N','N','E','E','E','E','E','N','N','N','E','E','E','E','E','N','N','N'},
 {'N','N','N','N','N','N','N','E','N','N','N','E','N','N','N','N','N','N','N'},
 {'N','N','N','N','N','N','E','N','E','E','E','N','E','N','N','N','N','N','N'},
 {'N','N','N','N','N','E','N','E','N','E','N','E','N','E','N','N','N','N','N'},
 {'N','N','N','N','E','N','E','N','N','E','N','N','E','N','E','N','N','N','N'},
 {'N','N','N','E','N','E','N','N','N','E','N','N','N','E','N','E','N','N','N'},
 {'N','N','N','N','E','N','N','N','N','E','N','N','N','N','E','N','N','N','N'},
 {'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N'},
 {'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N'},
 {'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N'},
    };
char player_turn = 'X';
GtkWidget *window_main;
GtkWidget *fixed_main;

static gboolean x_coordinate (GtkWidget *widget, GdkEvent *event, gpointer data)
{
	i_location [0] = (int) data;
	
	return FALSE;
}

static gboolean y_coordinate (GtkWidget *widget, GdkEvent *event, gpointer data)
{
	i_location [1] = (int) data;
	
	return FALSE;
}



static gboolean moved (GtkWidget *widget, GdkEvent *event, gpointer data)
{
	bool bWon;
	int i = 0;
	int x = 0, y = 0;
	int x_position = 0;
	int y_position = 0;
	GtkWidget *player;
	GtkWidget *dialog_win;
    /* this is the widget that used to pop up for invalid move. 
     * we can use it for something else if needed. */

    /* GtkWidget *dialog_invalid; */

	char image_location [16] = "./images/";
	strcat (image_location, &player_turn);
	strcat (image_location, ".png");
	
	if (board_location [i_location [0]][i_location [1]] == 'E')
	{
		board_location [i_location [0]][i_location [1]] = player_turn;
	
	
		while (x < i_location [0])
		{
			
			x_position += 31.6;
			x++;
		}
			
		while (y < i_location [1])
		{
			
			y_position += 31.6;
			y++;
		}
			
		player = gtk_image_new_from_file (image_location);
		gtk_fixed_put (GTK_FIXED (fixed_main), player, x_position, y_position);
		gtk_widget_show (player);
		
		bWon = check_win (player_turn, board_location);
		
		if (bWon == true)
		{
			printf ("%c Won the game\n", player_turn);
			
			dialog_win = gtk_message_dialog_new (NULL,
												GTK_DIALOG_MODAL,
												GTK_MESSAGE_INFO,
												GTK_BUTTONS_CLOSE,
												"%c has won the game\n", player_turn);
												
			/* gtk_message_dialog_format_secondary_text (GTK_DIALOG (dialog_win), "test"); */						
			gtk_dialog_run (GTK_DIALOG (dialog_win));
			gtk_widget_destroy (dialog_win);
			
			/* code to clear game board */
			clear_board (board_location, &player_turn, &bWon);
			gtk_widget_destroy (fixed_main);
			set_up_board ();
		}
		else
		{
		
			if (player_turn == 'X')
				player_turn = 'O';
			else
				player_turn = 'X';
		}
		
		/* if no one wins, close the game */
		for (y = 0; y < 20; y++)
		{
			for (x = 0; x < 20; x++)
			{
				if (board_location [x][y] == 'E')
				{
					i++;
					break;
				}
			}
			if (i > 0)
				break;
		}
		
		if (i == 0)
		{
			dialog_win = gtk_message_dialog_new (NULL,
												GTK_DIALOG_MODAL,
												GTK_MESSAGE_INFO,
												GTK_BUTTONS_CLOSE,
												"No one has won\n");
												
			gtk_dialog_run (GTK_DIALOG (dialog_win));
			gtk_widget_destroy (dialog_win);
			
			clear_board (board_location, &player_turn, &bWon);
			gtk_widget_destroy (fixed_main);
			set_up_board ();
		}
	}
	return TRUE;
}

void set_up_board ()
{
	
	int x, y;
	int x_position = 0;
	int y_position = 0;
	GtkWidget *image_board;
	GtkWidget *eventbox_main;

	printf ("set_up_board\n");
	
	image_board = gtk_image_new_from_file ("./images/full_board.png");
	
	fixed_main = gtk_fixed_new ();
	gtk_container_add (GTK_CONTAINER (window_main), fixed_main);
	gtk_fixed_put (GTK_FIXED (fixed_main), image_board, 0, 0);
	
	
	for (y = 0; y < 20; y++)
	{
		for (x = 0; x < 20; x++)
		{
			eventbox_main = gtk_event_box_new ();
			g_signal_connect (G_OBJECT (eventbox_main), "button_press_event", G_CALLBACK (x_coordinate), (gpointer) x);
			g_signal_connect (G_OBJECT (eventbox_main), "button_press_event", G_CALLBACK (y_coordinate), (gpointer) y);
			g_signal_connect (G_OBJECT (eventbox_main), "button_press_event", G_CALLBACK (moved), NULL);
			gtk_widget_set_size_request (eventbox_main, 31.6, 31.6);
			gtk_fixed_put (GTK_FIXED (fixed_main), eventbox_main, x_position, y_position);
			gtk_event_box_set_visible_window (GTK_EVENT_BOX (eventbox_main), FALSE);			
			gtk_widget_show (eventbox_main);
			
			
			x_position +=31.6;
		}
		y_position += 31.6;
		x_position = 0;
	}
	
	gtk_widget_show (image_board);
	gtk_widget_show (fixed_main);
	gtk_widget_show (window_main);
}


int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	
	window_main = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect (G_OBJECT (window_main), "delete_event", G_CALLBACK (delete_event), NULL);
	g_signal_connect (G_OBJECT (window_main), "destroy", G_CALLBACK (destroy), NULL);
	gtk_window_set_title (GTK_WINDOW (window_main), "Tic-Tac-Toe");
	
	set_up_board ();
		
	gtk_main();


	return 0;
}
