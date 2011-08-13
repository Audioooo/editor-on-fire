#include <allegro.h>
#include "../agup/agup.h"
#include "../undo.h"
#include "../dialog.h"
#include "../mix.h"
#include "../main.h"	//Inclusion for eof_custom_snap_measure
#include "../dialog/proc.h"
#include "edit.h"
#include "song.h"

#ifdef USEMEMWATCH
#include "../memwatch.h"
#endif

MENU eof_edit_paste_from_menu[] =
{
    {"&Supaeasy", eof_menu_edit_paste_from_supaeasy, NULL, 0, NULL},
    {"&Easy", eof_menu_edit_paste_from_easy, NULL, 0, NULL},
    {"&Medium", eof_menu_edit_paste_from_medium, NULL, 0, NULL},
    {"&Amazing", eof_menu_edit_paste_from_amazing, NULL, 0, NULL},
    {"", NULL, NULL, 0, NULL},
    {"&Catalog", eof_menu_edit_paste_from_catalog, NULL, 0, NULL},
    {NULL, NULL, NULL, 0, NULL}
};

MENU eof_edit_snap_menu[] =
{
    {"1/4", eof_menu_edit_snap_quarter, NULL, 0, NULL},
    {"1/8", eof_menu_edit_snap_eighth, NULL, 0, NULL},
    {"1/16", eof_menu_edit_snap_sixteenth, NULL, 0, NULL},
    {"1/32", eof_menu_edit_snap_thirty_second, NULL, 0, NULL},
    {"", NULL, NULL, 0, NULL},
    {"1/12", eof_menu_edit_snap_twelfth, NULL, 0, NULL},
    {"1/24", eof_menu_edit_snap_twenty_fourth, NULL, 0, NULL},
    {"1/48", eof_menu_edit_snap_forty_eighth, NULL, 0, NULL},
    {"", NULL, NULL, 0, NULL},
    {"&Custom", eof_menu_edit_snap_custom, NULL, 0, NULL},
    {"", NULL, NULL, 0, NULL},
    {"Off\tG", eof_menu_edit_snap_off, NULL, D_SELECTED, NULL},
    {NULL, NULL, NULL, 0, NULL}
};

MENU eof_edit_claps_menu[] =
{
    {"&All", eof_menu_edit_claps_all, NULL, D_SELECTED, NULL},
    {"&Green", eof_menu_edit_claps_green, NULL, 0, NULL},
    {"&Red", eof_menu_edit_claps_red, NULL, 0, NULL},
    {"&Yellow", eof_menu_edit_claps_yellow, NULL, 0, NULL},
    {"&Blue", eof_menu_edit_claps_blue, NULL, 0, NULL},
    {"&Purple", eof_menu_edit_claps_purple, NULL, 0, NULL},
    {"&Orange", eof_menu_edit_claps_orange, NULL, 0, NULL},
    {NULL, NULL, NULL, 0, NULL}
};

MENU eof_edit_hopo_menu[] =
{
    {"&RF", eof_menu_edit_hopo_rf, NULL, D_SELECTED, NULL},
    {"&FOF", eof_menu_edit_hopo_fof, NULL, 0, NULL},
    {"&Off", eof_menu_edit_hopo_off, NULL, 0, NULL},
    {"&Manual", eof_menu_edit_hopo_manual, NULL, 0, NULL},
    {NULL, NULL, NULL, 0, NULL}
};

MENU eof_edit_zoom_menu[] =
{
    {"1/1&0", eof_menu_edit_zoom_10, NULL, D_SELECTED, NULL},
    {"1/&9", eof_menu_edit_zoom_9, NULL, 0, NULL},
    {"1/&8", eof_menu_edit_zoom_8, NULL, 0, NULL},
    {"1/&7", eof_menu_edit_zoom_7, NULL, 0, NULL},
    {"1/&6", eof_menu_edit_zoom_6, NULL, 0, NULL},
    {"1/&5", eof_menu_edit_zoom_5, NULL, 0, NULL},
    {"1/&4", eof_menu_edit_zoom_4, NULL, 0, NULL},
    {"1/&3", eof_menu_edit_zoom_3, NULL, 0, NULL},
    {"1/&2", eof_menu_edit_zoom_2, NULL, 0, NULL},
    {"1/&1", eof_menu_edit_zoom_1, NULL, 0, NULL},
    {NULL, NULL, NULL, 0, NULL}
};

MENU eof_edit_playback_menu[] =
{
    {"&100%", eof_menu_edit_playback_100, NULL, D_SELECTED, NULL},
    {"&75%", eof_menu_edit_playback_75, NULL, 0, NULL},
    {"&50%", eof_menu_edit_playback_50, NULL, 0, NULL},
    {"&25%", eof_menu_edit_playback_25, NULL, 0, NULL},
    {"&Custom", eof_menu_edit_playback_custom, NULL, 0, NULL},
    {NULL, NULL, NULL, 0, NULL}
};

MENU eof_edit_speed_menu[] =
{
    {"&Slow", eof_menu_edit_speed_slow, NULL, D_SELECTED, NULL},
    {"&Medium", eof_menu_edit_speed_medium, NULL, 0, NULL},
    {"&Fast", eof_menu_edit_speed_fast, NULL, 0, NULL},
    {NULL, NULL, NULL, 0, NULL}
};

MENU eof_edit_bookmark_menu[] =
{
    {"&0\tCtrl+Num 0", eof_menu_edit_bookmark_0, NULL, 0, NULL},
    {"&1\tCtrl+Num 1", eof_menu_edit_bookmark_1, NULL, 0, NULL},
    {"&2\tCtrl+Num 2", eof_menu_edit_bookmark_2, NULL, 0, NULL},
    {"&3\tCtrl+Num 3", eof_menu_edit_bookmark_3, NULL, 0, NULL},
    {"&4\tCtrl+Num 4", eof_menu_edit_bookmark_4, NULL, 0, NULL},
    {"&5\tCtrl+Num 5", eof_menu_edit_bookmark_5, NULL, 0, NULL},
    {"&6\tCtrl+Num 6", eof_menu_edit_bookmark_6, NULL, 0, NULL},
    {"&7\tCtrl+Num 7", eof_menu_edit_bookmark_7, NULL, 0, NULL},
    {"&8\tCtrl+Num 8", eof_menu_edit_bookmark_8, NULL, 0, NULL},
    {"&9\tCtrl+Num 9", eof_menu_edit_bookmark_9, NULL, 0, NULL},
    {NULL, NULL, NULL, 0, NULL}
};

MENU eof_edit_selection_menu[] =
{
    {"&Select All\tCtrl+A", eof_menu_edit_select_all, NULL, 0, NULL},
    {"Select &Like\tCtrl+L", eof_menu_edit_select_like, NULL, 0, NULL},
    {"Select &Rest\tShift+End", eof_menu_edit_select_rest, NULL, 0, NULL},
    {"&Deselect All\tCtrl+D", eof_menu_edit_deselect_all, NULL, 0, NULL},
    {"Select &Previous\tShift+Home", eof_menu_edit_select_previous, NULL, 0, NULL},
    {NULL, NULL, NULL, 0, NULL}
};

MENU eof_edit_menu[] =
{
    {"&Undo\tCtrl+Z", eof_menu_edit_undo, NULL, D_DISABLED, NULL},
    {"&Redo\tCtrl+R", eof_menu_edit_redo, NULL, D_DISABLED, NULL},
    {"", NULL, NULL, 0, NULL},
    {"&Copy\tCtrl+C", eof_menu_edit_copy, NULL, 0, NULL},
    {"&Paste\tCtrl+V", eof_menu_edit_paste, NULL, 0, NULL},
    {"Old Paste\tCtrl+P", eof_menu_edit_old_paste, NULL, 0, NULL},
    {"Paste &From", NULL, eof_edit_paste_from_menu, 0, NULL},
    {"", NULL, NULL, 0, NULL},
    {"&Grid Snap", NULL, eof_edit_snap_menu, 0, NULL},
    {"&Zoom", NULL, eof_edit_zoom_menu, 0, NULL},
    {"Preview Sp&eed", NULL, eof_edit_speed_menu, 0, NULL},
    {"Playback R&ate", NULL, eof_edit_playback_menu, 0, NULL},
    {"Preview &HOPO", NULL, eof_edit_hopo_menu, 0, NULL},
    {"", NULL, NULL, 0, NULL},
    {"&Metronome\tM", eof_menu_edit_metronome, NULL, 0, NULL},
    {"Claps\tC", eof_menu_edit_claps, NULL, 0, NULL},
    {"Clap &Notes", NULL, eof_edit_claps_menu, 0, NULL},
    {"&Vocal Tones\tV", eof_menu_edit_vocal_tones, NULL, 0, NULL},
    {"MIDI &Tones", eof_menu_edit_midi_tones, NULL, 0, NULL},
    {"", NULL, NULL, 0, NULL},
    {"&Bookmark", NULL, eof_edit_bookmark_menu, 0, NULL},
    {"", NULL, NULL, 0, NULL},
    {"&Selection", NULL, eof_edit_selection_menu, 0, NULL},
    {NULL, NULL, NULL, 0, NULL}
};

DIALOG eof_custom_snap_dialog[] =
{
   /* (proc)				(x)		(y)		(w)		(h)  		(fg)	(bg) (key) (flags)	(d1) (d2) (dp)			(dp2) (dp3) */
   { d_agup_shadow_box_proc,32,		68,		170, 	72 + 8 +15,	2,		23,  0,    0,		0,   0,   NULL,			NULL, NULL },
   { d_agup_text_proc,		56,		84,		64,		8,			2,		23,  0,    0,		0,   0,   "Intervals:",	NULL, NULL },
   { eof_verified_edit_proc,112,	80,		66,		20,			2,		23,  0,    0,		8,   0,   eof_etext2,	"0123456789", NULL },
   { d_agup_radio_proc,		42,		105,	68,		15,			2,		23,  0,    0,		0,   0,   "beat",		NULL, NULL },
   { d_agup_radio_proc,		120,	105,	68,		15,			2,		23,  0,    0,		0,   0,   "measure",	NULL, NULL },
   { d_agup_button_proc,	42,		125,	68,		28,			2,		23,  '\r', D_EXIT,	0,   0,   "OK",			NULL, NULL },
   { d_agup_button_proc,	120,	125,	68,		28,			2,		23,  0,    D_EXIT,	0,   0,   "Cancel",		NULL, NULL },
   { NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL }
};

DIALOG eof_custom_speed_dialog[] =
{
   /* (proc)			(x)	(y)	(w)		(h)  	(fg)	(bg) (key) (flags)	(d1) (d2) (dp)		(dp2) 		(dp3) */
   { d_agup_shadow_box_proc,	32,	68,	170, 	72 + 8 +15,	2,	23,  0,    0,		0,   0,   NULL,		NULL, 		NULL },
   { d_agup_text_proc,		56,	84,	64,		8,	2,	23,  0,    0,		0,   0,   "Percent:",	NULL, 		NULL },
   { eof_verified_edit_proc,	112,	80,	66,		20,	2,	23,  0,    0,		8,   0,   eof_etext2,	"0123456789",	NULL },
   { d_agup_button_proc,	42,	125,	68,		28,	2,	23,  '\r', D_EXIT,	0,   0,   "OK",		NULL, 		NULL },
   { d_agup_button_proc,	120,	125,	68,		28,	2,	23,  0,    D_EXIT,	0,   0,   "Cancel",	NULL, 		NULL },
   { NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL }
};

void eof_prepare_edit_menu(void)
{
	int i;
	unsigned long tracknum;
	int vselected = 0;

	if(eof_song && eof_song_loaded)
	{
		tracknum = eof_song->track[eof_selected_track]->tracknum;

		/* undo */
		if(eof_undo_count > 0)
		{
			eof_edit_menu[0].flags = 0;
		}
		else
		{
			eof_edit_menu[0].flags = D_DISABLED;
		}

		/* redo */
		if(eof_redo_count)
		{
			eof_edit_menu[1].flags = 0;
		}
		else
		{
			eof_edit_menu[1].flags = D_DISABLED;
		}

		/* copy */
		vselected = eof_count_selected_notes(NULL, 1);
		if(vselected)
		{
			eof_edit_menu[3].flags = 0;		//copy
			eof_edit_selection_menu[1].flags = 0;	//select like

			/* select rest */
			if(eof_selection.current != (eof_get_track_size(eof_song, eof_selected_track) - 1))
			{	//If the selected note isn't the last in the track
				eof_edit_selection_menu[2].flags = 0;
			}
			else
			{
				eof_edit_selection_menu[2].flags = D_DISABLED;
			}

			/* deselect all */
			eof_edit_selection_menu[3].flags = 0;

			if(eof_selection.current != 0)
			{
				eof_edit_selection_menu[4].flags = 0;	//select previous
			}
			else
			{
				eof_edit_selection_menu[4].flags = D_DISABLED;	//Select previous cannot be used when the first note/lyric was just selected
			}
		}
		else
		{
			eof_edit_menu[3].flags = D_DISABLED;		//copy
			eof_edit_selection_menu[1].flags = D_DISABLED;	//select like
			eof_edit_selection_menu[2].flags = D_DISABLED;	//select rest
			eof_edit_selection_menu[3].flags = D_DISABLED;	//deselect all
			eof_edit_selection_menu[4].flags = D_DISABLED;	//select previous
		}

		/* paste, paste old */
		if(eof_vocals_selected)
		{
			if(exists("eof.vocals.clipboard"))
			{
				eof_edit_menu[4].flags = 0;
				eof_edit_menu[5].flags = 0;
			}
			else
			{
				eof_edit_menu[4].flags = D_DISABLED;
				eof_edit_menu[5].flags = D_DISABLED;
			}
		}
		else
		{
			if(exists("eof.clipboard"))
			{
				eof_edit_menu[4].flags = 0;
				eof_edit_menu[5].flags = 0;
			}
			else
			{
				eof_edit_menu[4].flags = D_DISABLED;
				eof_edit_menu[5].flags = D_DISABLED;
			}
		}

		/* select all, selection */
		if(eof_vocals_selected)
		{
			if(eof_song->vocal_track[tracknum]->lyrics > 0)
			{
				eof_edit_selection_menu[0].flags = 0;
				eof_edit_menu[22].flags = 0;
			}
			else
			{
				eof_edit_selection_menu[0].flags = D_DISABLED;
				eof_edit_menu[22].flags = D_DISABLED;
			}
		}
		else
		{
			if(eof_note_type_name[eof_note_type][0] == '*')
			{
				eof_edit_selection_menu[0].flags = 0;
				eof_edit_menu[22].flags = 0;
			}
			else
			{
				eof_edit_selection_menu[0].flags = D_DISABLED;
				eof_edit_menu[22].flags = D_DISABLED;
			}
		}

		/* zoom */
		for(i = 0; i < 9; i++)
		{
			eof_edit_zoom_menu[i].flags = 0;
		}
		eof_edit_zoom_menu[10 - eof_zoom].flags = D_SELECTED;

		/* hopo */
		for(i = 0; i < 3; i++)
		{
			eof_edit_hopo_menu[i].flags = 0;
		}
		eof_edit_hopo_menu[(int)eof_hopo_view].flags = D_SELECTED;

		/* speed */
		for(i = 0; i < 3; i++)
		{
			eof_edit_speed_menu[i].flags = 0;
		}
		switch(eof_zoom_3d)
		{
			case 5:
			{
				eof_edit_speed_menu[0].flags = D_SELECTED;
				break;
			}
			case 3:
			{
				eof_edit_speed_menu[1].flags = D_SELECTED;
				break;
			}
			case 2:
			{
				eof_edit_speed_menu[2].flags = D_SELECTED;
				break;
			}
		}

		/* paste from difficulty */
		for(i = 0; i < 4; i++)	//For each of the four difficulties
		{
			if((eof_note_type_name[i][0] == '*') && (i != eof_note_type) && !eof_vocals_selected)	//If the difficulty is populated, isn't the active difficulty and PART VOCALS isn't active
			{
				eof_edit_paste_from_menu[i].flags = 0;		//Enable paste from the difficulty
			}
			else
			{
				eof_edit_paste_from_menu[i].flags = D_DISABLED;	//(Paste from difficulty isn't supposed to be usable in PART VOCALS)
			}
		}

		/* paste from catalog */
		if(eof_selected_catalog_entry < eof_song->catalog->entries)
		{
			if((eof_music_pos >= eof_song->catalog->entry[eof_selected_catalog_entry].start_pos) && (eof_music_pos <= eof_song->catalog->entry[eof_selected_catalog_entry].end_pos) && (eof_song->catalog->entry[eof_selected_catalog_entry].track == eof_selected_track) && (eof_song->catalog->entry[eof_selected_catalog_entry].type == eof_note_type))
			{
				eof_edit_paste_from_menu[5].flags = D_DISABLED;
			}
			else if((eof_song->catalog->entry[eof_selected_catalog_entry].track == EOF_TRACK_VOCALS) && !eof_vocals_selected)
			{
				eof_edit_paste_from_menu[5].flags = D_DISABLED;
			}
			else if((eof_song->catalog->entry[eof_selected_catalog_entry].track != EOF_TRACK_VOCALS) && eof_vocals_selected)
			{
				eof_edit_paste_from_menu[5].flags = D_DISABLED;
			}
/*cnotes was never set to anything besides 0, so this can be removed
			else if(cnotes > 0)
			{
				eof_edit_paste_from_menu[5].flags = D_DISABLED;
			}
*/
			else
			{
				eof_edit_paste_from_menu[5].flags = 0;
			}
		}
		else
		{
			eof_edit_paste_from_menu[5].flags = D_DISABLED;
		}

		/* paste from */
		eof_edit_menu[6].flags = D_DISABLED;
		for(i = 0; i < 6; i++)
		{
			if((i != 4) && (eof_edit_paste_from_menu[i].flags == 0))
			{
				eof_edit_menu[6].flags = 0;
			}
		}

		/* selection */
		for(i = 0; i < 12; i++)
		{
			eof_edit_snap_menu[i].flags = 0;
		}
		switch(eof_snap_mode)
		{
			case EOF_SNAP_QUARTER:
			{
				eof_edit_snap_menu[0].flags = D_SELECTED;
				break;
			}
			case EOF_SNAP_EIGHTH:
			{
				eof_edit_snap_menu[1].flags = D_SELECTED;
				break;
			}
			case EOF_SNAP_SIXTEENTH:
			{
				eof_edit_snap_menu[2].flags = D_SELECTED;
				break;
			}
			case EOF_SNAP_THIRTY_SECOND:
			{
				eof_edit_snap_menu[3].flags = D_SELECTED;
				break;
			}
			case EOF_SNAP_TWELFTH:
			{
				eof_edit_snap_menu[5].flags = D_SELECTED;
				break;
			}
			case EOF_SNAP_TWENTY_FOURTH:
			{
				eof_edit_snap_menu[6].flags = D_SELECTED;
				break;
			}
			case EOF_SNAP_FORTY_EIGHTH:
			{
				eof_edit_snap_menu[7].flags = D_SELECTED;
				break;
			}
			case EOF_SNAP_CUSTOM:
			{
				eof_edit_snap_menu[9].flags = D_SELECTED;
				break;
			}
			case EOF_SNAP_OFF:
			{
				eof_edit_snap_menu[11].flags = D_SELECTED;
				break;
			}
		}

		/* MIDI tones */
		if(!eof_midi_initialized)
			eof_edit_menu[18].flags = D_DISABLED;
	}
}

int eof_menu_edit_undo(void)
{
	eof_undo_apply();
	eof_redo_toggle = 1;
	if((eof_catalog_menu[0].flags & D_SELECTED) && (eof_song->catalog->entries > 0))
	{
		eof_music_catalog_pos = eof_song->catalog->entry[eof_selected_catalog_entry].start_pos + eof_av_delay;
	}
	return 1;
}

int eof_menu_edit_redo(void)
{
	eof_redo_apply();
	eof_redo_toggle = 0;
	if((eof_catalog_menu[0].flags & D_SELECTED) && (eof_song->catalog->entries > 0))
	{
		eof_music_catalog_pos = eof_song->catalog->entry[eof_selected_catalog_entry].start_pos + eof_av_delay;
	}
	return 1;
}

int eof_menu_edit_copy_vocal(void)
{
	unsigned long i;
	unsigned long tracknum = eof_song->track[eof_selected_track]->tracknum;
	int first_pos = -1;
	long first_beat = -1;
	char note_check = 0;
	int copy_notes = 0;
	float tfloat;
	PACKFILE * fp;

	if(!eof_vocals_selected)
		return 1;	//Return error

	/* first, scan for selected notes */
	for(i = 0; i < eof_song->vocal_track[tracknum]->lyrics; i++)
	{
		if((eof_selection.track == EOF_TRACK_VOCALS) && eof_selection.multi[i])
		{
			copy_notes++;
			if(eof_song->vocal_track[tracknum]->lyric[i]->pos < first_pos)
			{
				first_pos = eof_song->vocal_track[tracknum]->lyric[i]->pos;
			}
			if(first_beat == -1)
			{
				first_beat = eof_get_beat(eof_song, eof_song->vocal_track[tracknum]->lyric[i]->pos);
			}
		}
	}
	if(copy_notes <= 0)
	{
		return 1;
	}

	/* get ready to write clipboard to disk */
	fp = pack_fopen("eof.vocals.clipboard", "w");
	if(!fp)
	{
		allegro_message("Clipboard error!");
		return 1;
	}
	pack_iputl(copy_notes, fp);
	pack_iputl(first_beat, fp);

	for(i = 0; i < eof_song->vocal_track[tracknum]->lyrics; i++)
	{
		if((eof_selection.track == EOF_TRACK_VOCALS) && eof_selection.multi[i])
		{

			/* check for accidentally moved note */
			if(!note_check)
			{
				if(eof_song->beat[eof_get_beat(eof_song, eof_song->vocal_track[tracknum]->lyric[i]->pos) + 1]->pos - eof_song->vocal_track[tracknum]->lyric[i]->pos <= 10)
				{
					if(alert(NULL, "First note appears to be off.", "Adjust?", "&Yes", "&No", 'y', 'n') == 1)
					{
						eof_song->vocal_track[tracknum]->lyric[i]->pos = eof_song->beat[eof_get_beat(eof_song, eof_song->vocal_track[tracknum]->lyric[i]->pos) + 1]->pos;
					}
					eof_clear_input();
				}
				note_check = 1;
			}

			/* write note data to disk */
			pack_putc(eof_song->vocal_track[tracknum]->lyric[i]->note, fp);
			pack_iputl(eof_song->vocal_track[tracknum]->lyric[i]->pos - first_pos, fp);
			pack_iputl(eof_get_beat(eof_song, eof_song->vocal_track[tracknum]->lyric[i]->pos), fp);
			pack_iputl(eof_get_beat(eof_song, eof_song->vocal_track[tracknum]->lyric[i]->pos + eof_song->vocal_track[tracknum]->lyric[i]->length), fp);
			pack_iputl(eof_song->vocal_track[tracknum]->lyric[i]->length, fp);
			tfloat = eof_get_porpos(eof_song->vocal_track[tracknum]->lyric[i]->pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
			tfloat = eof_get_porpos(eof_song->vocal_track[tracknum]->lyric[i]->pos + eof_song->vocal_track[tracknum]->lyric[i]->length);
			pack_fwrite(&tfloat, sizeof(float), fp);
			pack_iputw(ustrlen(eof_song->vocal_track[tracknum]->lyric[i]->text), fp);
			pack_fwrite(eof_song->vocal_track[tracknum]->lyric[i]->text, ustrlen(eof_song->vocal_track[tracknum]->lyric[i]->text), fp);
		}
	}
	pack_fclose(fp);
	return 1;
}

/* delete lyrics which overlap the specified range */
/*
static void eof_menu_edit_paste_clear_range_vocal(unsigned long start, unsigned long end)
{
	unsigned long i;
	unsigned long tracknum = eof_song->track[eof_selected_track]->tracknum;

	if(!eof_vocals_selected)
		return;

	for(i = eof_song->vocal_track[tracknum]->lyrics; i > 0; i--)
	{
		if((eof_song->vocal_track[tracknum]->lyric[i-1]->pos >= start) && (eof_song->vocal_track[tracknum]->lyric[i-1]->pos <= end))
		{
			eof_track_delete_note(eof_song, eof_selected_track, i-1);
		}
		else if((eof_song->vocal_track[tracknum]->lyric[i-1]->pos + eof_song->vocal_track[tracknum]->lyric[i-1]->length >= start) && (eof_song->vocal_track[tracknum]->lyric[i-1]->pos + eof_song->vocal_track[tracknum]->lyric[i-1]->length <= end))
		{
			eof_track_delete_note(eof_song, eof_selected_track, i-1);
		}
	}
}
*/

int eof_menu_edit_paste_vocal_logic(int oldpaste)
{
	unsigned long i, j, t;
	unsigned long tracknum = eof_song->track[eof_selected_track]->tracknum;
	unsigned long paste_pos[EOF_MAX_NOTES] = {0};
	long paste_count = 0;
	long first_beat = 0;
	long this_beat = eof_get_beat(eof_song, eof_music_pos - eof_av_delay);
	long copy_notes;
	long new_pos = -1;
	long new_end_pos = -1;
	long last_pos = -1;
	EOF_EXTENDED_LYRIC temp_lyric;
	EOF_LYRIC * new_lyric = NULL;
	PACKFILE * fp;

	if(!eof_vocals_selected)
		return 1;	//Return error

	/* open the file */
	fp = pack_fopen("eof.vocals.clipboard", "r");
	if(!fp)
	{
		allegro_message("Clipboard error!\nNothing to paste!");
		return 1;
	}
	if(!oldpaste && (first_beat + this_beat >= eof_song->beats - 1))
	{	//If new paste logic is being used, return from function if the first lyric would paste after the last beat
		return 1;
	}
	eof_prepare_undo(EOF_UNDO_TYPE_NOTE_SEL);
	copy_notes = pack_igetl(fp);
	first_beat = pack_igetl(fp);
	memset(eof_selection.multi, 0, sizeof(eof_selection.multi));
	eof_selection.current = EOF_MAX_NOTES - 1;
	eof_selection.current_pos = 0;

	for(i = 0; i < copy_notes; i++)
	{
		/* read the note */
		temp_lyric.note = pack_getc(fp);
		temp_lyric.pos = pack_igetl(fp);
		temp_lyric.beat = pack_igetl(fp);
		if(!oldpaste && (temp_lyric.beat - first_beat + this_beat >= eof_song->beats - 1))
		{	//If new paste logic is being used, return from function if this lyric (and the subsequent lyrics) would paste after the last beat
			break;
		}
		temp_lyric.endbeat = pack_igetl(fp);
		temp_lyric.length = pack_igetl(fp);
		pack_fread(&temp_lyric.porpos, sizeof(float), fp);
		pack_fread(&temp_lyric.porendpos, sizeof(float), fp);
		t = pack_igetw(fp);
		pack_fread(temp_lyric.text, t, fp);
		temp_lyric.text[t] = '\0';

		if(eof_music_pos + temp_lyric.pos - eof_av_delay < eof_music_length)
		{
			if(last_pos >= 0)
			{
				last_pos = new_end_pos + 1;
			}
			if(!oldpaste)
			{	//If new paste logic is being used, this lyric pastes into a position relative to the start and end of a beat marker
				new_pos = eof_put_porpos(temp_lyric.beat - first_beat + this_beat, temp_lyric.porpos, 0.0);
				new_end_pos = eof_put_porpos(temp_lyric.endbeat - first_beat + this_beat, temp_lyric.porendpos, 0.0);
			}
			else
			{	//If old paste logic is being used, this lyric pastes into a position relative to the previous pasted note
				new_pos = eof_music_pos + temp_lyric.pos - eof_av_delay;
				new_end_pos = new_pos + temp_lyric.length;
			}
			if(last_pos < 0)
			{
				last_pos = new_pos;
			}
			eof_menu_edit_paste_clear_range(eof_selected_track, eof_note_type, last_pos, new_end_pos);

			if(!oldpaste)
			{	//If new paste logic is being used, this lyric pastes into a position relative to the start and end of a beat marker
				new_lyric = eof_track_add_create_note(eof_song, eof_selected_track, temp_lyric.note, new_pos, new_end_pos - new_pos, 0, temp_lyric.text);
			}
			else
			{	//If old paste logic is being used, this lyric pastes into a position relative to the previous pasted note
				new_lyric = eof_track_add_create_note(eof_song, eof_selected_track, temp_lyric.note, new_pos, temp_lyric.length, 0, temp_lyric.text);
			}
			if(new_lyric)
			{
				paste_pos[paste_count] = new_lyric->pos;
				paste_count++;
			}
		}
	}
	pack_fclose(fp);
	eof_track_sort_notes(eof_song, eof_selected_track);
	eof_track_fixup_notes(eof_song, eof_selected_track, 0);
	if((paste_count > 0) && (eof_selection.track != EOF_TRACK_VOCALS))
	{
		eof_selection.track = EOF_TRACK_VOCALS;
		memset(eof_selection.multi, 0, sizeof(eof_selection.multi));
	}
	for(i = 0; i < paste_count; i++)
	{
		for(j = 0; j < eof_song->vocal_track[tracknum]->lyrics; j++)
		{
			if(eof_song->vocal_track[tracknum]->lyric[j]->pos == paste_pos[i])
			{
				eof_selection.multi[j] = 1;
				break;
			}
		}
	}
	return 1;
}

int eof_menu_edit_paste_vocal(void)
{
	return eof_menu_edit_paste_vocal_logic(0);	//Use new paste logic
}

int eof_menu_edit_old_paste_vocal(void)
{
	return eof_menu_edit_paste_vocal_logic(1);	//Use old paste logic
}

int eof_menu_edit_cut(unsigned long anchor, int option, float offset)
{
	unsigned long i, j, tracknum;
	char first_pos_found[EOF_TRACKS_MAX] = {0};
	unsigned long first_pos[EOF_TRACKS_MAX] = {0};
	char first_beat_found[EOF_TRACKS_MAX] = {0};
	unsigned long first_beat[EOF_TRACKS_MAX] = {0};
	unsigned long start_pos, end_pos;
	long last_anchor, next_anchor;
	unsigned long copy_notes[EOF_TRACKS_MAX] = {0};
	float tfloat;
	PACKFILE * fp;
	EOF_PHRASE_SECTION *sectionptr = NULL;
	unsigned long notepos=0;
	long notelength;
	float noterelativestart=0.0,noterelativeend=0.0;

	/* set boundary */
	for(i = 0; i < EOF_TRACKS_MAX; i++)
	{
		eof_anchor_diff[i] = 0;
	}
	last_anchor = eof_find_previous_anchor(eof_song, anchor);
	next_anchor = eof_find_next_anchor(eof_song, anchor);
	start_pos = eof_song->beat[last_anchor]->pos;
	if((next_anchor < 0) || (option == 1))
	{
		end_pos = eof_song->beat[eof_song->beats - 1]->pos - 1;
	}
	else
	{
		end_pos = eof_song->beat[next_anchor]->pos;
	}

	for(j = 1; j < eof_song->tracks; j++)
	{	//For each track
		for(i = 0; i < eof_get_track_size(eof_song, j); i++)
		{	//For each note in the track
			notepos = eof_get_note_pos(eof_song, j, i);
			notelength = eof_get_note_length(eof_song, j, i);
			if((notepos + notelength >= start_pos) && (notepos < end_pos))
			{
				copy_notes[j]++;
				if(!first_pos_found[j])
				{
					first_pos[j] = notepos;
					first_pos_found[j] = 1;
					eof_anchor_diff[j] = eof_get_beat(eof_song, notepos) - last_anchor;
				}
				if(notepos < first_pos[j])
				{
					first_pos[j] = notepos;
					eof_anchor_diff[j] = eof_get_beat(eof_song, notepos) - last_anchor;
				}
				if(!first_beat_found[j])
				{
					first_beat[j] = eof_get_beat(eof_song, notepos);
					first_beat_found[j] = 1;
				}
			}
		}
	}

	/* get ready to write clipboard to disk */
	fp = pack_fopen("eof.autoadjust", "w");
	if(!fp)
	{
		allegro_message("Clipboard error!");
		return 1;
	}

	/* copy all tracks */
	for(j = 1; j < eof_song->tracks; j++)
	{	//For each track
		/* notes */
		pack_iputl(copy_notes[j], fp);
		pack_iputl(first_beat[j], fp);

		for(i = 0; i < eof_get_track_size(eof_song, j); i++)
		{	//For each note in this track
			notepos = eof_get_note_pos(eof_song, j, i);
			notelength = eof_get_note_length(eof_song, j, i);
			if((notepos + notelength >= start_pos) && (notepos < end_pos))
			{	//If this note falls within the start->end time range
				pack_iputl(eof_get_note_type(eof_song, j, i), fp);
				pack_iputl(eof_get_note_note(eof_song, j, i), fp);
				pack_iputl(notepos - first_pos[j], fp);
				noterelativestart = eof_get_porpos(notepos);
				pack_fwrite(&noterelativestart, sizeof(float), fp);
				noterelativeend = eof_get_porpos(notepos + notelength);
				pack_fwrite(&noterelativeend, sizeof(float), fp);
				pack_iputl(eof_get_beat(eof_song, notepos), fp);
				pack_iputl(eof_get_beat(eof_song, notepos + notelength), fp);
				pack_iputl(notelength, fp);
				pack_iputl(eof_get_note_flags(eof_song, j, i), fp);

				eof_save_song_string_pf(eof_get_note_name(eof_song, j, i), fp);	//Write the note/lyric name/text

				if(eof_song->track[j]->track_format == EOF_PRO_GUITAR_TRACK_FORMAT)
				{	//If this is a pro guitar track
					tracknum = eof_song->track[j]->tracknum;
					pack_fwrite(eof_song->pro_guitar_track[tracknum]->note[i]->frets, 6, fp);	//Write the fret values for the six usable strings
					pack_putc(eof_song->pro_guitar_track[tracknum]->note[i]->legacymask, fp);	//Write the legacy bitmask
				}
			}
		}
		/* star power */
		for(i = 0; i < eof_get_num_star_power_paths(eof_song, j); i++)
		{	//For each star power path in the track
			/* which beat */
			sectionptr = eof_get_star_power_path(eof_song, j, i);
			pack_iputl(eof_get_beat(eof_song, sectionptr->start_pos), fp);
			tfloat = eof_get_porpos(sectionptr->start_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
			pack_iputl(eof_get_beat(eof_song, sectionptr->end_pos), fp);
			tfloat = eof_get_porpos(sectionptr->end_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
		}

		/* solos */
		for(i = 0; i < eof_get_num_solos(eof_song, j); i++)
		{	//For each solo section in the track
			/* which beat */
			sectionptr = eof_get_solo(eof_song, j, i);
			pack_iputl(eof_get_beat(eof_song, sectionptr->start_pos), fp);
			tfloat = eof_get_porpos(sectionptr->start_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
			pack_iputl(eof_get_beat(eof_song, sectionptr->end_pos), fp);
			tfloat = eof_get_porpos(sectionptr->end_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
		}

		/* lyric lines */
		for(i = 0; i < eof_get_num_lyric_sections(eof_song, j); i++)
		{	//For each lyric section in the track
			/* which beat */
			sectionptr = eof_get_lyric_section(eof_song, j, i);
			pack_iputl(eof_get_beat(eof_song, sectionptr->start_pos), fp);
			tfloat = eof_get_porpos(sectionptr->start_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
			pack_iputl(eof_get_beat(eof_song, sectionptr->end_pos), fp);
			tfloat = eof_get_porpos(sectionptr->end_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
		}

		/* trills */
		for(i = 0; i < eof_get_num_trills(eof_song, j); i++)
		{	//For each trill section in the track
			/* which beat */
			sectionptr = eof_get_trill(eof_song, j, i);
			pack_iputl(eof_get_beat(eof_song, sectionptr->start_pos), fp);
			tfloat = eof_get_porpos(sectionptr->start_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
			pack_iputl(eof_get_beat(eof_song, sectionptr->end_pos), fp);
			tfloat = eof_get_porpos(sectionptr->end_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
		}

		/* tremolos */
		for(i = 0; i < eof_get_num_tremolos(eof_song, j); i++)
		{	//For each tremolo section in the track
			/* which beat */
			sectionptr = eof_get_tremolo(eof_song, j, i);
			pack_iputl(eof_get_beat(eof_song, sectionptr->start_pos), fp);
			tfloat = eof_get_porpos(sectionptr->start_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
			pack_iputl(eof_get_beat(eof_song, sectionptr->end_pos), fp);
			tfloat = eof_get_porpos(sectionptr->end_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
		}

		/* arpeggios */
		for(i = 0; i < eof_get_num_arpeggios(eof_song, j); i++)
		{	//For each tremolo section in the track
			/* which beat */
			sectionptr = eof_get_arpeggio(eof_song, j, i);
			pack_iputl(eof_get_beat(eof_song, sectionptr->start_pos), fp);
			tfloat = eof_get_porpos(sectionptr->start_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
			pack_iputl(eof_get_beat(eof_song, sectionptr->end_pos), fp);
			tfloat = eof_get_porpos(sectionptr->end_pos);
			pack_fwrite(&tfloat, sizeof(float), fp);
		}
	}//For each track
	pack_fclose(fp);
	return 1;
}

int eof_menu_edit_cut_paste(unsigned long anchor, int option, float offset)
{
	unsigned long i, j, b, tracknum, notenum;
	unsigned long first_beat[EOF_TRACKS_MAX] = {0};
	unsigned long this_beat[EOF_TRACKS_MAX] = {0};
	unsigned long start_pos, end_pos;
	long last_anchor, next_anchor;
	PACKFILE * fp;
	unsigned long copy_notes[EOF_TRACKS_MAX];
	EOF_EXTENDED_NOTE temp_note;
	EOF_NOTE * new_note = NULL;
	float tfloat;
	EOF_PHRASE_SECTION *sectionptr = NULL;
	char text[EOF_MAX_LYRIC_LENGTH+1] = {0};
	unsigned long notepos=0;
	long notelength=0;

	for(i = 0; i < EOF_TRACKS_MAX; i++)
	{
		this_beat[i] = eof_find_previous_anchor(eof_song, anchor) + eof_anchor_diff[i];
	}

	/* set boundary */
	last_anchor = eof_find_previous_anchor(eof_song, anchor);
	next_anchor = eof_find_next_anchor(eof_song, anchor);
	start_pos = eof_song->beat[last_anchor]->pos;
	if((next_anchor < 0) || (option == 1))
	{
		end_pos = eof_song->beat[eof_song->beats - 1]->pos - 1;
	}
	else
	{
		end_pos = eof_song->beat[next_anchor]->pos;
	}

	fp = pack_fopen("eof.autoadjust", "r");
	if(!fp)
	{
		allegro_message("Clipboard error!");
		return 1;
	}
	for(j = 1; j < eof_song->tracks; j++)
	{	//For each track
		for(i = eof_get_track_size(eof_song, j); i > 0; i--)
		{	//For each note in the track, starting from the last note
			notepos = eof_get_note_pos(eof_song, j, i-1);
			if((notepos + eof_get_note_length(eof_song, j, i-1) >= start_pos) && (notepos < end_pos))
			{	//If the note's end position is after the target beat or if the note's start position is before the target beat
				eof_track_delete_note(eof_song, j, i-1);	//Delete the note
			}
		}
	}

	memset(eof_selection.multi, 0, sizeof(eof_selection.multi));
	for(j = 1; j < eof_song->tracks; j++)
	{	//For each track
		copy_notes[j] = pack_igetl(fp);
		first_beat[j] = pack_igetl(fp);
		for(i = 0; i < copy_notes[j]; i++)
		{
		/* read the note */
			temp_note.type = pack_igetl(fp);
			temp_note.note = pack_igetl(fp);
			temp_note.pos = pack_igetl(fp);
			pack_fread(&temp_note.porpos, sizeof(float), fp);
			pack_fread(&temp_note.porendpos, sizeof(float), fp);
			temp_note.beat = pack_igetl(fp);
			temp_note.endbeat = pack_igetl(fp);
			temp_note.length = pack_igetl(fp);
			temp_note.flags = pack_igetl(fp);	//Store the note flags
			eof_load_song_string_pf(text, fp, sizeof(text));	//Store the note/lyric name/text

			if(temp_note.pos + temp_note.length < eof_music_length)
			{
				notepos = eof_put_porpos(temp_note.beat - first_beat[j] + this_beat[j], temp_note.porpos, 0.0);
				notelength = eof_put_porpos(temp_note.endbeat - first_beat[j] + this_beat[j], temp_note.porendpos, 0.0) - notepos;
				new_note = eof_track_add_create_note(eof_song, j, temp_note.note, notepos, notelength, temp_note.type, text);

				if(new_note)
				{	//If the note was successfully created
					notenum = eof_get_track_size(eof_song, j) - 1;	//Get the index of the note that was just created
					eof_set_note_flags(eof_song, j, notenum, temp_note.flags);	//Set the last created note's flags

					if(eof_song->track[j]->track_format == EOF_PRO_GUITAR_TRACK_FORMAT)
					{	//If this is a pro guitar track
						tracknum = eof_song->track[j]->tracknum;
						pack_fread(eof_song->pro_guitar_track[tracknum]->note[notenum]->frets, 6, fp);		//Set the fret values for the six usable strings
						eof_song->pro_guitar_track[tracknum]->note[notenum]->legacymask = pack_getc(fp);	//Set the legacy bitmask
					}
				}
			}
		}
		eof_track_sort_notes(eof_song, j);

		/* star power */
		for(i = 0; i < eof_get_num_star_power_paths(eof_song, j); i++)
		{	//For each star power path in the active track
			/* which beat */
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr = eof_get_star_power_path(eof_song, j, i);
			sectionptr->start_pos = eof_put_porpos(b, tfloat, 0.0);
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr->end_pos = eof_put_porpos(b, tfloat, 0.0);
		}

		/* solos */
		for(i = 0; i < eof_get_num_solos(eof_song, j); i++)
		{	//For each solo section in the active track
			/* which beat */
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr = eof_get_solo(eof_song, j, i);
			sectionptr->start_pos = eof_put_porpos(b, tfloat, 0.0);
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr->end_pos = eof_put_porpos(b, tfloat, 0.0);
		}

		/* lyric lines */
		for(i = 0; i < eof_get_num_lyric_sections(eof_song, j); i++)
		{	//For each lyric section in the active track
			/* which beat */
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr = eof_get_lyric_section(eof_song, j, i);
			sectionptr->start_pos = eof_put_porpos(b, tfloat, 0.0);
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr->end_pos = eof_put_porpos(b, tfloat, 0.0);
		}

		/* trills */
		for(i = 0; i < eof_get_num_trills(eof_song, j); i++)
		{	//For each trill section in the active track
			/* which beat */
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr = eof_get_trill(eof_song, j, i);
			sectionptr->start_pos = eof_put_porpos(b, tfloat, 0.0);
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr->end_pos = eof_put_porpos(b, tfloat, 0.0);
		}

		/* tremolos */
		for(i = 0; i < eof_get_num_tremolos(eof_song, j); i++)
		{	//For each tremolo section in the active track
			/* which beat */
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr = eof_get_tremolo(eof_song, j, i);
			sectionptr->start_pos = eof_put_porpos(b, tfloat, 0.0);
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr->end_pos = eof_put_porpos(b, tfloat, 0.0);
		}

		/* arpeggios */
		for(i = 0; i < eof_get_num_arpeggios(eof_song, j); i++)
		{	//For each arpeggio section in the active track
			/* which beat */
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr = eof_get_arpeggio(eof_song, j, i);
			sectionptr->start_pos = eof_put_porpos(b, tfloat, 0.0);
			b = pack_igetl(fp);
			pack_fread(&tfloat, sizeof(float), fp);
			sectionptr->end_pos = eof_put_porpos(b, tfloat, 0.0);
		}
	}//For each track
	pack_fclose(fp);
	eof_fixup_notes(eof_song);
	eof_determine_phrase_status();
	return 1;
}

int eof_menu_edit_copy(void)
{
	if(eof_vocals_selected)
	{
		return eof_menu_edit_copy_vocal();
	}
	unsigned long i;
	unsigned long first_pos = 0, note_pos;
	long note_len;
	char first_pos_read = 0;
	long first_beat = 0;
	char first_beat_read = 0;
	char note_check = 0;
	unsigned long copy_notes = 0;
	float tfloat;
	PACKFILE * fp;
	unsigned char frets[16] = {0};	//Used to store NULL fret data to support copying legacy notes to a pro guitar track
	unsigned long tracknum = eof_song->track[eof_selected_track]->tracknum;

	/* first, scan for selected notes */
	for(i = 0; i < eof_get_track_size(eof_song, eof_selected_track); i++)
	{	//For each note in the active track
		if((eof_get_note_type(eof_song, eof_selected_track, i) == eof_note_type) && (eof_selection.track == eof_selected_track) && eof_selection.multi[i])
		{	//If this note is in the active difficulty, is in the active track and is selected
			copy_notes++;
			note_pos = eof_get_note_pos(eof_song, eof_selected_track, i);
			note_len = eof_get_note_length(eof_song, eof_selected_track, i);
			if(!first_pos_read || (note_pos < first_pos))
			{	//Track the position of the first note in the selection
				first_pos = note_pos;
				first_pos_read = 1;
			}
			if(!first_beat_read)
			{
				first_beat = eof_get_beat(eof_song, eof_get_note_pos(eof_song, eof_selected_track, i));
				first_beat_read = 1;
			}
		}
	}
	if(copy_notes == 0)
	{
		return 1;
	}

	/* get ready to write clipboard to disk */
	fp = pack_fopen("eof.clipboard", "w");
	if(!fp)
	{
		allegro_message("Clipboard error!");
		return 1;
	}
	pack_iputl(eof_selected_track, fp);	//Store the source track number
	pack_iputl(copy_notes, fp);			//Store the number of notes that will be stored to clipboard
	pack_iputl(first_beat, fp);			//Store the beat number of the first note that will be stored to clipboard

	for(i = 0; i < eof_get_track_size(eof_song, eof_selected_track); i++)
	{	//For each note in the active track
		if((eof_get_note_type(eof_song, eof_selected_track, i) == eof_note_type) && (eof_selection.track == eof_selected_track) && eof_selection.multi[i])
		{
			/* check for accidentally moved note */
			if(!note_check)
			{
				if(eof_song->beat[eof_get_beat(eof_song, eof_get_note_pos(eof_song, eof_selected_track, i)) + 1]->pos - eof_get_note_pos(eof_song, eof_selected_track, i) <= 10)
				{
					if(alert(NULL, "First note appears to be off.", "Adjust?", "&Yes", "&No", 'y', 'n') == 1)
					{
						eof_set_note_pos(eof_song, eof_selected_track, i, eof_song->beat[eof_get_beat(eof_song, eof_get_note_pos(eof_song, eof_selected_track, i)) + 1]->pos);
					}
					eof_clear_input();
				}
				note_check = 1;
			}

			/* write note data to disk */
			eof_save_song_string_pf(eof_get_note_name(eof_song, eof_selected_track, i), fp);	//Write the note's name
			pack_iputl(eof_get_note_note(eof_song, eof_selected_track, i), fp);					//Write the note bitmask value
			pack_iputl(eof_get_note_pos(eof_song, eof_selected_track, i) - first_pos, fp);		//Write the note's position relative to within the selection
			tfloat = eof_get_porpos(eof_get_note_pos(eof_song, eof_selected_track, i));
			pack_fwrite(&tfloat, sizeof(float), fp);	//Write the percent representing the note's start position within a beat
			tfloat = eof_get_porpos(eof_get_note_pos(eof_song, eof_selected_track, i) + eof_get_note_length(eof_song, eof_selected_track, i));
			pack_fwrite(&tfloat, sizeof(float), fp);	//Write the percent representing the note's end position within a beat
			pack_iputl(eof_get_beat(eof_song, eof_get_note_pos(eof_song, eof_selected_track, i)), fp);	//Write the beat the note starts in
			pack_iputl(eof_get_beat(eof_song, eof_get_note_pos(eof_song, eof_selected_track, i) + eof_get_note_length(eof_song, eof_selected_track, i)), fp);	//Write the beat the note ends in
			pack_iputl(eof_get_note_length(eof_song, eof_selected_track, i), fp);	//Write the note's length
			pack_iputl(eof_get_note_flags(eof_song, eof_selected_track, i), fp);	//Write the note's flags

			/* Write pro guitar specific data to disk, or zeroed data */
			if(eof_song->track[eof_selected_track]->track_format == EOF_PRO_GUITAR_TRACK_FORMAT)
			{	//If this is a pro guitar note
				pack_iputl(eof_song->pro_guitar_track[tracknum]->note[i]->legacymask, fp);				//Write the pro guitar note's legacy bitmask
				pack_fwrite(eof_song->pro_guitar_track[tracknum]->note[i]->frets, sizeof(frets), fp);	//Write the note's fret array
				pack_iputl(eof_song->pro_guitar_track[tracknum]->note[i]->ghost, fp);					//Write the note's ghost bitmask
			}
			else
			{
				pack_iputl(0, fp);	//Write a legacy bitmask indicating that the original note bitmask is to be used
				pack_fwrite(frets, sizeof(frets), fp);	//Write 0 data for the note's fret array (legacy notes pasted into a pro guitar track will be played open by default)
				pack_iputl(0, fp);	//Write a blank ghost bitmask (no strings are ghosted by default)
			}
		}
	}
	pack_fclose(fp);
	return 1;
}

int eof_menu_edit_paste_logic(int oldpaste)
{
	if(eof_vocals_selected)
	{	//The vocal track uses its own clipboard logic
		return eof_menu_edit_paste_vocal_logic(oldpaste);	//Call the old or new vocal paste logic accordingly
	}
	unsigned long i, j;
	unsigned long paste_pos[EOF_MAX_NOTES] = {0};
	unsigned long paste_count = 0;
	unsigned long first_beat = 0;
	long this_beat = eof_get_beat(eof_song, eof_music_pos - eof_av_delay);
	unsigned long copy_notes;
	PACKFILE * fp;
	EOF_EXTENDED_NOTE temp_note, first_note, last_note;
	EOF_NOTE * new_note = NULL;
	unsigned long sourcetrack = 0;	//Will store the track that this clipboard data was from
	unsigned long tracknum = eof_song->track[eof_selected_track]->tracknum;

	/* open the file */
	fp = pack_fopen("eof.clipboard", "r");
	if(!fp)
	{
		allegro_message("Clipboard error!\nNothing to paste!");
		return 1;
	}
	if(!oldpaste && (first_beat + this_beat >= eof_song->beats - 1))
	{	//If new paste logic is being used, return from function if the first note would paste after the last beat
		return 1;
	}
	sourcetrack = pack_igetl(fp);		//Read the source track of the clipboard data
	copy_notes = pack_igetl(fp);		//Read the number of notes on the clipboard
	first_beat = pack_igetl(fp);		//Read the original beat number of the first note that was copied
	if(!copy_notes)
	{	//If there are 0 notes on the clipboard, return without making an undo
		return 1;
	}
	eof_prepare_undo(EOF_UNDO_TYPE_NOTE_SEL);

	memset(eof_selection.multi, 0, sizeof(eof_selection.multi));
	eof_selection.current = EOF_MAX_NOTES - 1;
	eof_selection.current_pos = 0;

	if(eof_paste_erase_overlap)
	{	//If the user decided to delete existing notes that are between the start and end of the pasted notes
		unsigned long clear_start, clear_end;

		eof_menu_paste_read_clipboard_note(fp, &first_note);	//Read the first note on the clipboard
		for(i = 1; i < copy_notes; i++)
		{	//Parse the other notes on the clipboard
			eof_menu_paste_read_clipboard_note(fp, &last_note);
		}
		//At this point, last_note contains the data for the last note on the clipboard.  Determine the time span of notes that would need to be cleared
		if(!oldpaste)
		{	//If new paste logic is being used, this note pastes into a position relative to the start and end of a beat marker
			clear_start = eof_put_porpos(first_note.beat - first_beat + this_beat, first_note.porpos, 0.0);		//The position that "new paste" would paste the first note at
			clear_end = eof_put_porpos(last_note.endbeat - first_beat + this_beat, last_note.porendpos, 0.0);	//The position to which "new paste" would extend the last pasted note
		}
		else
		{	//If old paste logic is being used, this note pastes into a position relative to the previous pasted note
			clear_start = eof_music_pos + first_note.pos - eof_av_delay;	//The position that "old paste" would paste the first note at
			clear_end = eof_music_pos + last_note.pos - eof_av_delay + last_note.length;	//The position to which "old paste" would extend the last pasted note
		}
		eof_menu_edit_paste_clear_range(eof_selected_track, eof_note_type, clear_start, clear_end);
		//The packfile functions have no seek routine, so the file has to be closed, re-opened and repositioned to the first clipboard note for the actual paste logic
		pack_fclose(fp);
		fp = pack_fopen("eof.clipboard", "r");
		if(!fp)
		{
			allegro_message("Error re-opening clipboard");
			return 1;
		}
		sourcetrack = pack_igetl(fp);		//Read the source track of the clipboard data
		copy_notes = pack_igetl(fp);		//Read the number of notes on the clipboard
		first_beat = pack_igetl(fp);		//Read the original beat number of the first note that was copied
	}

	for(i = 0; i < copy_notes; i++)
	{	//For each note in the clipboard file
		eof_menu_paste_read_clipboard_note(fp, &temp_note);	//Read the note
		if(!oldpaste && ((temp_note.beat - first_beat + this_beat >= eof_song->beats - 1) || (temp_note.endbeat - first_beat + this_beat >= eof_song->beats - 1)))
		{	//If new paste logic is being used, return from function if this note (and the subsequent notes) would paste after the last beat
			break;
		}
		if((eof_song->track[eof_selected_track]->track_format != EOF_PRO_GUITAR_TRACK_FORMAT) && (temp_note.legacymask != 0))
		{	//If the copied note indicated that this overrides the original bitmask (pasting pro guitar into a legacy track)
			temp_note.note = temp_note.legacymask;
		}
		if((eof_song->track[eof_selected_track]->track_format == EOF_LEGACY_TRACK_FORMAT) && (temp_note.note & 32))
		{	//If the note being pasted uses lane 6 and the destination track is a legacy track
			if((eof_song->track[eof_selected_track]->flags & EOF_TRACK_FLAG_SIX_LANES) == 0)
			{	//If the sixth lane isn't currently enabled in the destination track
				temp_note.note &= ~32;	//Clear lane 6 from the pasted note
			}
		}
		eof_sanitize_note_flags(&temp_note.flags,eof_selected_track);	//Ensure the note flags are validated for the track being pasted into

		/* create the note */
		if(eof_music_pos + temp_note.pos + temp_note.length - eof_av_delay < eof_music_length)
		{
			if(!oldpaste)
			{	//If new paste logic is being used, this note pastes into a position relative to the start and end of a beat marker
				new_note = eof_track_add_create_note(eof_song, eof_selected_track, temp_note.note, eof_put_porpos(temp_note.beat - first_beat + this_beat, temp_note.porpos, 0.0), eof_put_porpos(temp_note.endbeat - first_beat + this_beat, temp_note.porendpos, 0.0) - eof_put_porpos(temp_note.beat - first_beat + this_beat, temp_note.porpos, 0.0), eof_note_type, temp_note.name);
			}
			else
			{	//If old paste logic is being used, this note pastes into a position relative to the previous pasted note
				new_note = eof_track_add_create_note(eof_song, eof_selected_track, temp_note.note, eof_music_pos + temp_note.pos - eof_av_delay, temp_note.length, eof_note_type, temp_note.name);
			}
			if(new_note)
			{
				eof_set_note_flags(eof_song, eof_selected_track, eof_get_track_size(eof_song, eof_selected_track) - 1, temp_note.flags);
				paste_pos[paste_count] = eof_get_note_pos(eof_song, eof_selected_track, eof_get_track_size(eof_song, eof_selected_track) - 1);
				paste_count++;
			}
		}

		/* process fret values */
		if(eof_song->track[eof_selected_track]->track_format == EOF_PRO_GUITAR_TRACK_FORMAT)
		{	//If this is a pro guitar track
			eof_song->pro_guitar_track[tracknum]->note[eof_song->pro_guitar_track[tracknum]->notes - 1]->legacymask = temp_note.legacymask;							//Copy the legacy bitmask to the last created pro guitar note
			memcpy(eof_song->pro_guitar_track[tracknum]->note[eof_song->pro_guitar_track[tracknum]->notes - 1]->frets, temp_note.frets, sizeof(temp_note.frets));	//Copy the fret array to the last created pro guitar note
			eof_song->pro_guitar_track[tracknum]->note[eof_song->pro_guitar_track[tracknum]->notes - 1]->ghost = temp_note.ghostmask;								//Copy the ghost bitmask to the last created pro guitar note
		}
	}
	pack_fclose(fp);
	eof_track_sort_notes(eof_song, eof_selected_track);
	eof_fixup_notes(eof_song);
	eof_determine_phrase_status();
	eof_detect_difficulties(eof_song);
	if((paste_count > 0) && (eof_selection.track != eof_selected_track))
	{
		eof_selection.track = eof_selected_track;
		memset(eof_selection.multi, 0, sizeof(eof_selection.multi));
	}
	for(i = 0; i < paste_count; i++)
	{
		for(j = 0; j < eof_get_track_size(eof_song, eof_selected_track); j++)
		{	//For each note in the active track
			if((eof_get_note_type(eof_song, eof_selected_track, j) == eof_note_type) && (eof_get_note_pos(eof_song, eof_selected_track, j) == paste_pos[i]))
			{
				eof_selection.multi[j] = 1;
				break;
			}
		}
	}
	return 1;
}

int eof_menu_edit_paste(void)
{
	return eof_menu_edit_paste_logic(0);	//Use new paste logic
}

int eof_menu_edit_old_paste(void)
{
	return eof_menu_edit_paste_logic(1);	//Use old paste logic
}

int eof_menu_edit_snap_quarter(void)
{
	eof_snap_mode = EOF_SNAP_QUARTER;
	return 1;
}

int eof_menu_edit_snap_eighth(void)
{
	eof_snap_mode = EOF_SNAP_EIGHTH;
	return 1;
}

int eof_menu_edit_snap_sixteenth(void)
{
	eof_snap_mode = EOF_SNAP_SIXTEENTH;
	return 1;
}

int eof_menu_edit_snap_thirty_second(void)
{
	eof_snap_mode = EOF_SNAP_THIRTY_SECOND;
	return 1;
}

int eof_menu_edit_snap_twelfth(void)
{
	eof_snap_mode = EOF_SNAP_TWELFTH;
	return 1;
}

int eof_menu_edit_snap_twenty_fourth(void)
{
	eof_snap_mode = EOF_SNAP_TWENTY_FOURTH;
	return 1;
}

int eof_menu_edit_snap_forty_eighth(void)
{
	eof_snap_mode = EOF_SNAP_FORTY_EIGHTH;
	return 1;
}

int eof_menu_edit_snap_custom(void)
{
	int last_interval = eof_snap_interval;
	eof_cursor_visible = 0;
	eof_render();
	eof_color_dialog(eof_custom_snap_dialog, gui_fg_color, gui_bg_color);
	centre_dialog(eof_custom_snap_dialog);
	sprintf(eof_etext2, "%d", eof_snap_interval);
	if(eof_custom_snap_measure == 0)
	{	//If the custom grid snap is per beats
		eof_custom_snap_dialog[3].flags = D_SELECTED;	//Activate "per beat" radio button by default
		eof_custom_snap_dialog[4].flags = 0;
	}
	else
	{
		eof_custom_snap_dialog[3].flags = 0;
		eof_custom_snap_dialog[4].flags = D_SELECTED;	//Activate "per measure" radio button by default
	}
	if(eof_popup_dialog(eof_custom_snap_dialog, 2) == 5)
	{
		eof_snap_interval = atoi(eof_etext2);

		if(eof_custom_snap_dialog[4].flags & D_SELECTED)	//If user selected per measure instead of per beat
		{
			eof_custom_snap_measure = 1;
		}
		else
		{
			eof_custom_snap_measure = 0;
		}

		if((eof_snap_interval > EOF_MAX_GRID_SNAP_INTERVALS) || (eof_snap_interval < 1))
		{
			eof_render();
			eof_snap_interval = last_interval;
			allegro_message("Invalid snap setting, must be between 1 and %d",EOF_MAX_GRID_SNAP_INTERVALS);
		}
		else
		{
			eof_snap_mode = EOF_SNAP_CUSTOM;
		}
	}
	printf("%d\n", eof_snap_interval);
	eof_cursor_visible = 1;
	eof_pen_visible = 1;
	eof_show_mouse(NULL);
	return 1;
}

int eof_menu_edit_zoom_helper_in(void)
{
	return eof_menu_edit_zoom_level(eof_zoom - 1);
}

int eof_menu_edit_zoom_helper_out(void)
{
	return eof_menu_edit_zoom_level(eof_zoom + 1);
}

int eof_menu_edit_zoom_10(void)
{
	return eof_menu_edit_zoom_level(10);
}

int eof_menu_edit_zoom_9(void)
{
	return eof_menu_edit_zoom_level(9);
}

int eof_menu_edit_zoom_8(void)
{
	return eof_menu_edit_zoom_level(8);
}

int eof_menu_edit_zoom_7(void)
{
	return eof_menu_edit_zoom_level(7);
}

int eof_menu_edit_zoom_6(void)
{
	return eof_menu_edit_zoom_level(6);
}

int eof_menu_edit_zoom_5(void)
{
	return eof_menu_edit_zoom_level(5);
}

int eof_menu_edit_zoom_4(void)
{
	return eof_menu_edit_zoom_level(4);
}

int eof_menu_edit_zoom_3(void)
{
	return eof_menu_edit_zoom_level(3);
}

int eof_menu_edit_zoom_2(void)
{
	return eof_menu_edit_zoom_level(2);
}

int eof_menu_edit_zoom_1(void)
{
	return eof_menu_edit_zoom_level(1);
}

int eof_menu_edit_zoom_level(int zoom)
{
	int i;
	if((zoom > 0) && (zoom <= EOF_NUM_ZOOM_LEVELS))
	{
		eof_zoom = zoom;
		for(i = 0; i < EOF_NUM_ZOOM_LEVELS; i++)
		{
			eof_edit_zoom_menu[i].flags = 0;
		}
		eof_edit_zoom_menu[EOF_NUM_ZOOM_LEVELS - zoom].flags = D_SELECTED;
	}

	return 1;
}

int eof_menu_edit_playback_speed_helper_faster(void)
{
	int i;

	for(i = 0; i < 5; i++)
	{
		eof_edit_playback_menu[i].flags = 0;
	}
	eof_playback_speed = (eof_playback_speed /250)*250;	//Account for custom playback rate (force to round down to a multiple of 250)
	eof_playback_speed += 250;
	if(eof_playback_speed > 1000)
	{
		if(eof_input_mode == EOF_INPUT_FEEDBACK)
		{
			eof_playback_speed = 250;
		}
		else
		{
			eof_playback_speed = 1000;
		}
	}
	eof_edit_playback_menu[(1000 - eof_playback_speed) / 250].flags = D_SELECTED;
	return 1;
}

int eof_menu_edit_playback_speed_helper_slower(void)
{
	int i;

	for(i = 0; i < 5; i++)
	{
		eof_edit_playback_menu[i].flags = 0;
	}
	eof_playback_speed = (eof_playback_speed /250)*250;	//Account for custom playback rate (force to round down to a multiple of 250)
	eof_playback_speed -= 250;
	if(eof_playback_speed < 250)
	{
		eof_playback_speed = 250;
	}
	eof_edit_playback_menu[(1000 - eof_playback_speed) / 250].flags = D_SELECTED;
	return 1;
}

int eof_menu_edit_playback_100(void)
{
	int i;

	for(i = 0; i < 5; i++)
	{
		eof_edit_playback_menu[i].flags = 0;
	}
	eof_edit_playback_menu[0].flags = D_SELECTED;
	eof_playback_speed = 1000;
	return 1;
}

int eof_menu_edit_playback_75(void)
{
	int i;

	for(i = 0; i < 5; i++)
	{
		eof_edit_playback_menu[i].flags = 0;
	}
	eof_edit_playback_menu[1].flags = D_SELECTED;
	eof_playback_speed = 750;
	return 1;
}

int eof_menu_edit_playback_50(void)
{
	int i;

	for(i = 0; i < 5; i++)
	{
		eof_edit_playback_menu[i].flags = 0;
	}
	eof_edit_playback_menu[2].flags = D_SELECTED;
	eof_playback_speed = 500;
	return 1;
}

int eof_menu_edit_playback_25(void)
{
	int i;

	for(i = 0; i < 5; i++)
	{
		eof_edit_playback_menu[i].flags = 0;
	}
	eof_edit_playback_menu[3].flags = D_SELECTED;
	eof_playback_speed = 250;
	return 1;
}

int eof_menu_edit_playback_custom(void)
{
	int i;
	int userinput=0;

	for(i = 0; i < 5; i++)
	{
		eof_edit_playback_menu[i].flags = 0;
	}
	eof_cursor_visible = 0;
	eof_render();
	eof_color_dialog(eof_custom_snap_dialog, gui_fg_color, gui_bg_color);
	centre_dialog(eof_custom_speed_dialog);
	sprintf(eof_etext2, "%d", eof_playback_speed/10);		//Load the current playback speed into a string
	if(eof_popup_dialog(eof_custom_speed_dialog, 2) == 3)		//If user activated "OK" from the custom speed dialog
	{
		userinput = atoi(eof_etext2);
//		if((userinput < 1) || (userinput > 99))			//User cannot specify to play at any speed not between 1% and 99%
//			return 1;

		eof_playback_speed = userinput * 10;
	}
	printf("%d\n", eof_playback_speed);
	eof_edit_playback_menu[4].flags = D_SELECTED;
	eof_cursor_visible = 1;
	eof_pen_visible = 1;
	eof_show_mouse(NULL);
	return 1;
}

int eof_menu_edit_speed_slow(void)
{
	int i;
	eof_zoom_3d = 5;
	for(i = 0; i < 3; i++)
	{
		eof_edit_speed_menu[i].flags = 0;
	}
	eof_edit_speed_menu[0].flags = D_SELECTED;
	return 1;
}

int eof_menu_edit_speed_medium(void)
{
	int i;
	eof_zoom_3d = 3;
	for(i = 0; i < 3; i++)
	{
		eof_edit_speed_menu[i].flags = 0;
	}
	eof_edit_speed_menu[1].flags = D_SELECTED;
	return 1;
}

int eof_menu_edit_speed_fast(void)
{
	int i;
	eof_zoom_3d = 2;
	for(i = 0; i < 3; i++)
	{
		eof_edit_speed_menu[i].flags = 0;
	}
	eof_edit_speed_menu[2].flags = D_SELECTED;
	return 1;
}

int eof_menu_edit_snap_off(void)
{
	eof_snap_mode = EOF_SNAP_OFF;
	return 1;
}

int eof_menu_edit_hopo_rf(void)
{
	return eof_menu_edit_hopo_helper(EOF_HOPO_RF);
}

int eof_menu_edit_hopo_fof(void)
{
	return eof_menu_edit_hopo_helper(EOF_HOPO_FOF);
}

int eof_menu_edit_hopo_off(void)
{
	return eof_menu_edit_hopo_helper(EOF_HOPO_OFF);
}

int eof_menu_edit_hopo_manual(void)
{
	return eof_menu_edit_hopo_helper(EOF_NUM_HOPO_MODES);
}

int eof_menu_edit_hopo_helper(int hopo_view)
{
	int i;
	if(hopo_view < EOF_NUM_HOPO_MODES)
	{
		for(i = 0; i < EOF_NUM_HOPO_MODES; i++)
		{
			eof_edit_hopo_menu[i].flags = 0;
		}
		eof_edit_hopo_menu[hopo_view].flags = D_SELECTED;
		eof_hopo_view = hopo_view;
		eof_determine_phrase_status();
	}
	return 1;
}

int eof_menu_edit_metronome(void)
{
	if(eof_mix_metronome_enabled)
	{
		eof_mix_metronome_enabled = 0;
		eof_edit_menu[14].flags = 0;
	}
	else
	{
		eof_mix_metronome_enabled = 1;
		eof_edit_menu[14].flags = D_SELECTED;
	}
	return 1;
}

int eof_menu_edit_claps_all(void)
{
	return eof_menu_edit_claps_helper(0,63);
}

int eof_menu_edit_claps_green(void)
{
	return eof_menu_edit_claps_helper(1,1);
}

int eof_menu_edit_claps_red(void)
{
	return eof_menu_edit_claps_helper(2,2);
}

int eof_menu_edit_claps_yellow(void)
{
	return eof_menu_edit_claps_helper(3,4);
}

int eof_menu_edit_claps_blue(void)
{
	return eof_menu_edit_claps_helper(4,8);
}

int eof_menu_edit_claps_purple(void)
{
	return eof_menu_edit_claps_helper(5,16);
}

int eof_menu_edit_claps_orange(void)
{
	return eof_menu_edit_claps_helper(6,32);
}

int eof_menu_edit_claps_helper(unsigned long menu_item,char claps_flag)
{
	int i;
	for(i = 0; i < 7; i++)
	{
		eof_edit_claps_menu[i].flags = 0;
	}
	eof_edit_claps_menu[menu_item].flags = D_SELECTED;
	eof_mix_claps_note = claps_flag;
	return 1;
}

int eof_menu_edit_claps(void)
{
	if(eof_mix_claps_enabled)
	{
		eof_mix_claps_enabled = 0;
		eof_edit_menu[15].flags = 0;
	}
	else
	{
		eof_mix_claps_enabled = 1;
		eof_edit_menu[15].flags = D_SELECTED;
	}
	return 1;
}

int eof_menu_edit_vocal_tones(void)
{
	if(eof_mix_vocal_tones_enabled)
	{
		eof_mix_vocal_tones_enabled = 0;
		eof_mix_percussion_enabled = 0;
		eof_edit_menu[17].flags = 0;
	}
	else
	{
		eof_mix_vocal_tones_enabled = 1;
		eof_mix_percussion_enabled = 1;
		eof_edit_menu[17].flags = D_SELECTED;
	}
	return 1;
}

int eof_menu_edit_midi_tones(void)
{
	if(eof_mix_midi_tones_enabled)
	{
		eof_mix_midi_tones_enabled = 0;
		eof_edit_menu[18].flags = 0;
	}
	else
	{
		eof_mix_midi_tones_enabled = 1;
		eof_edit_menu[18].flags = D_SELECTED;
	}
	return 1;
}

int eof_menu_edit_bookmark_helper(int b)
{
	if(eof_music_pos <= eof_av_delay)
		return 1;	//Do not place a bookmark at a negative or zero chart position

	eof_prepare_undo(EOF_UNDO_TYPE_NONE);
	if(eof_song->bookmark_pos[b] != eof_music_pos - eof_av_delay)
	{
		eof_song->bookmark_pos[b] = eof_music_pos - eof_av_delay;
	}
	else
	{
		eof_song->bookmark_pos[b] = 0;
	}
	return 1;
}

int eof_menu_edit_bookmark_0(void)
{
	return eof_menu_edit_bookmark_helper(0);
}

int eof_menu_edit_bookmark_1(void)
{
	return eof_menu_edit_bookmark_helper(1);
}

int eof_menu_edit_bookmark_2(void)
{
	return eof_menu_edit_bookmark_helper(2);
}

int eof_menu_edit_bookmark_3(void)
{
	return eof_menu_edit_bookmark_helper(3);
}

int eof_menu_edit_bookmark_4(void)
{
	return eof_menu_edit_bookmark_helper(4);
}

int eof_menu_edit_bookmark_5(void)
{
	return eof_menu_edit_bookmark_helper(5);
}

int eof_menu_edit_bookmark_6(void)
{
	return eof_menu_edit_bookmark_helper(6);
}

int eof_menu_edit_bookmark_7(void)
{
	return eof_menu_edit_bookmark_helper(7);
}

int eof_menu_edit_bookmark_8(void)
{
	return eof_menu_edit_bookmark_helper(8);
}

int eof_menu_edit_bookmark_9(void)
{
	return eof_menu_edit_bookmark_helper(9);
}

int eof_menu_edit_select_all(void)
{
	unsigned long i;

	for(i = 0; i < eof_get_track_size(eof_song, eof_selected_track); i++)
	{
		if(eof_get_note_type(eof_song, eof_selected_track, i) == eof_note_type)
		{
			eof_selection.track = eof_selected_track;
			eof_selection.multi[i] = 1;
		}
		else
		{
			eof_selection.multi[i] = 0;
		}
	}
	return 1;
}

int eof_menu_edit_select_like(void)
{
	unsigned long i, j, ntypes = 0;
	unsigned long ntype[100];	//This tracks each unique selected note to allow multiple dislike notes to be selected during a "select like" operation

	if(eof_selection.track != eof_selected_track)
	{
		return 1;
	}
	if(eof_selection.current >= eof_get_track_size(eof_song, eof_selected_track))
	{
		return 1;
	}
	//Make a list of all the unique selected notes
	for(i = 0; i < eof_get_track_size(eof_song, eof_selected_track); i++)
	{	//For each note in the active track
		if(eof_selection.multi[i] && (eof_get_note_type(eof_song, eof_selected_track, i) == eof_note_type))
		{	//If the note is selected and is in the active difficulty
			for(j = 0; j < ntypes; j++)
			{	//For each unique note number in the ntype array
				if(eof_note_compare(eof_selected_track, ntype[j], i) == 0)
				{	//If the stored unique note is the same as this note
					break;	//Break loop
				}
			}
			if(j == ntypes)
			{	//If no match was found
				if(ntypes < 100)
				{	//If the limit hasn't been reached
					ntype[ntypes] = i;	//Append this note's number to the ntype array
					ntypes++;
				}
			}
		}
	}
	memset(eof_selection.multi, 0, sizeof(eof_selection.multi));	//Clear the selected notes array
	for(i = 0; i < eof_get_track_size(eof_song, eof_selected_track); i++)
	{	//For each note in the active track
		for(j = 0; j < ntypes; j++)
		{	//For each note bitmask in the ntype array
			if((eof_get_note_type(eof_song, eof_selected_track, i) == eof_note_type) && (eof_note_compare(eof_selected_track, ntype[j], i) == 0))
			{	//If the note is in the active difficulty and matches one of the unique notes that are selected
				eof_selection.track = eof_selected_track;	//Change the selection's track to the active track
				eof_selection.multi[i] = 1;					//Mark the note as selected
			}
		}
	}
	return 1;
}

int eof_menu_edit_deselect_all(void)
{
	memset(eof_selection.multi, 0, sizeof(eof_selection.multi));
	eof_selection.current = EOF_MAX_NOTES - 1;
	eof_selection.current_pos = 0;
	return 1;
}

int eof_menu_edit_select_rest(void)
{
	unsigned long i;

	if(eof_count_selected_notes(NULL, 0) <= 0)
	{
		return 1;
	}
	if(eof_selection.current == EOF_MAX_NOTES - 1)	//No notes selected?
		return 1;	//Don't perform this operation

	for(i = eof_selection.current; i < eof_get_track_size(eof_song, eof_selected_track); i++)
	{	//For each note in the active track
		if(eof_get_note_type(eof_song, eof_selected_track, i) == eof_note_type)
		{
			eof_selection.multi[i] = 1;
		}
	}

	return 1;
}

int eof_menu_edit_paste_from_supaeasy(void)
{
	return eof_menu_edit_paste_from_difficulty(EOF_NOTE_SUPAEASY);
}

int eof_menu_edit_paste_from_easy(void)
{
	return eof_menu_edit_paste_from_difficulty(EOF_NOTE_EASY);
}

int eof_menu_edit_paste_from_medium(void)
{
	return eof_menu_edit_paste_from_difficulty(EOF_NOTE_MEDIUM);
}

int eof_menu_edit_paste_from_amazing(void)
{
	return eof_menu_edit_paste_from_difficulty(EOF_NOTE_AMAZING);
}

int eof_menu_edit_paste_from_difficulty(unsigned long source_difficulty)
{
	unsigned long i;
	EOF_NOTE * new_note = NULL;
	unsigned long pos, flags;
	long length;

	if((eof_note_type != source_difficulty) && (source_difficulty < EOF_MAX_DIFFICULTIES))
	{	//If the current difficulty is different than the source difficulty
		if(eof_note_type_name[eof_note_type][0] == '*')
		{	//If the current difficulty is populated
			if(alert(NULL, "Overwrite notes in this difficulty?", NULL, "&Yes", "&No", 'y', 'n') == 2)
			{
				return 1;
			}
		}
		eof_clear_input();
		eof_prepare_undo(EOF_UNDO_TYPE_NOTE_SEL);
		for(i = eof_get_track_size(eof_song, eof_selected_track); i > 0; i--)
		{	//For each note/lyric in this track, from last to first
			if(eof_get_note_type(eof_song, eof_selected_track, i-1) == eof_note_type)
			{	//If this note is in the current difficulty/lyric set
				eof_track_delete_note(eof_song, eof_selected_track, i - 1);	//Delete it
			}
		}
		for(i = 0; i < eof_get_track_size(eof_song, eof_selected_track); i++)
		{	//For each note in this instrument track
			if(eof_get_note_type(eof_song, eof_selected_track, i) == source_difficulty)
			{	//If this note is in the source difficulty
				pos = eof_get_note_pos(eof_song, eof_selected_track, i);
				length = eof_get_note_length(eof_song, eof_selected_track, i);
				flags = eof_get_note_flags(eof_song, eof_selected_track, i);
				new_note = eof_copy_note(eof_song, eof_selected_track, i, eof_selected_track, pos, length, eof_note_type);
			}
		}
		eof_detect_difficulties(eof_song);
	}
	return 1;
}

static unsigned long notes_in_beat(int beat)
{
	unsigned long count = 0;
	unsigned long i;

	if(beat > eof_song->beats - 2)
	{
		for(i = 0; i < eof_get_track_size(eof_song, eof_selected_track); i++)
		{	//For each note in the active track
			if((eof_get_note_type(eof_song, eof_selected_track, i) == eof_note_type) && (eof_get_note_pos(eof_song, eof_selected_track, i) >= eof_song->beat[beat]->pos))
			{
				count++;
			}
		}
	}
	else
	{
		for(i = 0; i < eof_get_track_size(eof_song, eof_selected_track); i++)
		{	//For each note in the active track
			if((eof_get_note_type(eof_song, eof_selected_track, i) == eof_note_type) && (eof_get_note_pos(eof_song, eof_selected_track, i) >= eof_song->beat[beat]->pos) && (eof_get_note_pos(eof_song, eof_selected_track, i) < eof_song->beat[beat + 1]->pos))
			{
				count++;
			}
		}
	}
	return count;
}

static int lyrics_in_beat(int beat)
{
	unsigned long count = 0;
	unsigned long i;

	if(beat > eof_song->beats - 2)
	{
		for(i = 0; i < eof_song->vocal_track[0]->lyrics; i++)
		{
			if(eof_song->vocal_track[0]->lyric[i]->pos >= eof_song->beat[beat]->pos)
			{
				count++;
			}
		}
	}
	else
	{
		for(i = 0; i < eof_song->vocal_track[0]->lyrics; i++)
		{
			if((eof_song->vocal_track[0]->lyric[i]->pos >= eof_song->beat[beat]->pos) && (eof_song->vocal_track[0]->lyric[i]->pos < eof_song->beat[beat + 1]->pos))
			{
				count++;
			}
		}
	}
	return count;
}

int eof_menu_edit_paste_from_catalog(void)
{
	unsigned long i, j;
	unsigned long paste_pos[EOF_MAX_NOTES] = {0};
	long paste_count = 0;
	unsigned long note_count = 0;
	long first = -1;
	long first_beat = -1;
	long start_beat = eof_get_beat(eof_song, eof_music_pos - eof_av_delay);
	long this_beat = -1;
	long current_beat = eof_get_beat(eof_song, eof_music_pos - eof_av_delay);
	long last_current_beat = current_beat;
	long end_beat = -1;
	float nporpos, nporendpos;
	EOF_NOTE * new_note = NULL;
	unsigned long newnotenum, sourcetrack;

	if((eof_selected_catalog_entry < eof_song->catalog->entries) && eof_song->catalog->entries)
	{	//If a valid catalog entry is selected
		/* make sure we can paste */
		if(eof_music_pos - eof_av_delay < eof_song->beat[0]->pos)
		{
			return 1;
		}

		sourcetrack = eof_song->catalog->entry[eof_selected_catalog_entry].track;

		/* make sure we can't paste inside of the catalog entry */
		if((sourcetrack == eof_selected_track) && (eof_song->catalog->entry[eof_selected_catalog_entry].type == eof_note_type) && (eof_music_pos - eof_av_delay >= eof_song->catalog->entry[eof_selected_catalog_entry].start_pos) && (eof_music_pos - eof_av_delay <= eof_song->catalog->entry[eof_selected_catalog_entry].end_pos))
		{
			return 1;
		}

		//Don't allow copying instrument track notes to PART VOCALS and vice versa
		if(((sourcetrack == EOF_TRACK_VOCALS) && (eof_selected_track != EOF_TRACK_VOCALS)) || ((sourcetrack != EOF_TRACK_VOCALS) && (eof_selected_track == EOF_TRACK_VOCALS)))
			return 1;

		for(i = 0; i < eof_get_track_size(eof_song, sourcetrack); i++)
		{	//For each note in the active catalog entry's track
			if((eof_get_note_type(eof_song, sourcetrack, i) == eof_song->catalog->entry[eof_selected_catalog_entry].type) && (eof_get_note_pos(eof_song, sourcetrack, i) >= eof_song->catalog->entry[eof_selected_catalog_entry].start_pos) && (eof_get_note_pos(eof_song, sourcetrack, i) + eof_get_note_length(eof_song, sourcetrack, i) <= eof_song->catalog->entry[eof_selected_catalog_entry].end_pos))
			{
				note_count++;
			}
		}
		if(note_count == 0)
		{
			return 1;
		}

		eof_prepare_undo(EOF_UNDO_TYPE_NOTE_SEL);
		for(i = 0; i < eof_get_track_size(eof_song, sourcetrack); i++)
		{	//For each note in the active catalog entry's track
			/* this note needs to be copied */
			if((eof_get_note_type(eof_song, sourcetrack, i) == eof_song->catalog->entry[eof_selected_catalog_entry].type) && (eof_get_note_pos(eof_song, sourcetrack, i) >= eof_song->catalog->entry[eof_selected_catalog_entry].start_pos) && (eof_get_note_pos(eof_song, sourcetrack, i) + eof_get_note_length(eof_song, sourcetrack, i) <= eof_song->catalog->entry[eof_selected_catalog_entry].end_pos))
			{
				if(first == -1)
				{
					first_beat = eof_get_beat(eof_song, eof_get_note_pos(eof_song, sourcetrack, i));
					first = 1;
				}
				this_beat = eof_get_beat(eof_song, eof_get_note_pos(eof_song, sourcetrack, i));
				if(this_beat < 0)
				{
					break;
				}
				last_current_beat = current_beat;
				current_beat = eof_get_beat(eof_song, eof_music_pos - eof_av_delay) + (this_beat - first_beat);
				if(current_beat >= eof_song->beats - 1)
				{
					break;
				}

				/* if we run into notes, abort */
				if((eof_vocals_selected) && (lyrics_in_beat(current_beat) && (last_current_beat != current_beat)))
				{
					break;
				}
				else if(notes_in_beat(current_beat) && (last_current_beat != current_beat))
				{
					break;
				}
				nporpos = eof_get_porpos(eof_get_note_pos(eof_song, sourcetrack, i));
				nporendpos = eof_get_porpos(eof_get_note_pos(eof_song, sourcetrack, i) + eof_get_note_length(eof_song, sourcetrack, i));
				end_beat = eof_get_beat(eof_song, eof_get_note_pos(eof_song, sourcetrack, i) + eof_get_note_length(eof_song, sourcetrack, i));
				if(end_beat < 0)
				{
					break;
				}

				/* paste the note */
				if(end_beat - first_beat + start_beat < eof_song->beats)
				{
					new_note = eof_copy_note(eof_song, sourcetrack, i, eof_selected_track, eof_put_porpos(current_beat, nporpos, 0.0), eof_put_porpos(end_beat - first_beat + start_beat, nporendpos, 0.0) - eof_put_porpos(current_beat, nporpos, 0.0), eof_note_type);
					if(new_note)
					{	//If the note was successfully created
						newnotenum = eof_get_track_size(eof_song, eof_selected_track) - 1;	//The index of the new note
						paste_pos[paste_count] = eof_get_note_pos(eof_song, eof_selected_track, newnotenum);
						paste_count++;
					}
				}
			}
		}//For each note in the active catalog entry's track

		eof_track_sort_notes(eof_song, eof_selected_track);
		eof_track_fixup_notes(eof_song, eof_selected_track, 0);
		eof_determine_phrase_status();
		eof_detect_difficulties(eof_song);
		eof_selection.current_pos = 0;
		memset(eof_selection.multi, 0, sizeof(eof_selection.multi));
		for(i = 0; i < paste_count; i++)
		{	//For each of the pasted notes
			for(j = 0; j < eof_get_track_size(eof_song, eof_selected_track); j++)
			{	//For each note in the destination track
				if((eof_get_note_pos(eof_song, eof_selected_track, j) == paste_pos[i]) && (eof_get_note_type(eof_song, eof_selected_track, j) == eof_note_type))
				{	//If this note is in the current difficulty and matches the position of one of the pasted notes
					eof_selection.track = eof_selected_track;	//Mark the note as selected
					eof_selection.multi[j] = 1;
					break;
				}
			}
		}
	}//If a valid catalog entry is selected
	return 1;
}

int eof_menu_edit_select_previous(void)
{
	unsigned long i;

	if(eof_count_selected_notes(NULL, 0) <= 0)	//If no notes are selected
	{
		return 1;
	}
	if(eof_selection.current == EOF_MAX_NOTES - 1)	//No notes selected?
		return 1;	//Don't perform this operation

	for(i = 0; (i < eof_selection.current) && (i < eof_get_track_size(eof_song, eof_selected_track)); i++)
	{
		if(eof_get_note_type(eof_song, eof_selected_track, i) == eof_note_type)
		{
			eof_selection.multi[i] = 1;
		}
	}

	return 1;
}

void eof_sanitize_note_flags(unsigned long *flags,unsigned long desttrack)
{
	if((flags == NULL) || (desttrack >= eof_song->tracks))
		return;

	if(eof_song->track[desttrack]->track_format != EOF_PRO_GUITAR_TRACK_FORMAT)
	{	//Erase all pro guitar flags from a non pro guitar note
		*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_HO);			//Erase the pro hammer on flag
		*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_PO);			//Erase the pro hammer off flag
		*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_SLIDE_UP);		//Erase the pro slide up flag
		*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_SLIDE_DOWN);	//Erase the pro slide down flag
		*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_STRING_MUTE);	//Erase the pro string mute flag
		*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_PALM_MUTE);	//Erase the pro palm mute flag
		*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_DOWN_STRUM);	//Erase the pro strum down flag
		*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_UP_STRUM);		//Erase the pro strum up flag

		if(eof_song->track[desttrack]->track_behavior != EOF_GUITAR_TRACK_BEHAVIOR)
		{	//If this isn't a 5 lane guitar track either
			*flags &= (~EOF_NOTE_FLAG_HOPO);	//Erase the temporary HOPO flag
			*flags &= (~EOF_NOTE_FLAG_F_HOPO);	//Erase the forced HOPO ON flag
			*flags &= (~EOF_NOTE_FLAG_NO_HOPO);	//Erase the forced HOPO OFF flag
		}
	}
	else
	{	//Resolve pro guitar flag conflicts
		if((*flags & EOF_PRO_GUITAR_NOTE_FLAG_HO) && (*flags & EOF_PRO_GUITAR_NOTE_FLAG_PO))
		{	//If both the hammer on AND the pull off flags are set, clear both
			*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_HO);
			*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_PO);
		}
		if(*flags & EOF_PRO_GUITAR_NOTE_FLAG_TAP)
		{	//If the tap flag is set
			if(*flags & EOF_PRO_GUITAR_NOTE_FLAG_HO)
			{	//If the hammer on flag is also set, clear both
				*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_TAP);
				*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_HO);
			}
			if(*flags & EOF_PRO_GUITAR_NOTE_FLAG_PO)
			{	//If the pull off flag is also set, clear both
				*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_TAP);
				*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_PO);
			}
		}
		if((*flags & EOF_PRO_GUITAR_NOTE_FLAG_SLIDE_UP) && (*flags & EOF_PRO_GUITAR_NOTE_FLAG_SLIDE_DOWN))
		{	//If both the slide up AND the slide down flags are set, clear both
			*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_SLIDE_UP);
			*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_SLIDE_DOWN);
		}
		if((*flags & EOF_PRO_GUITAR_NOTE_FLAG_STRING_MUTE) && (*flags & EOF_PRO_GUITAR_NOTE_FLAG_PALM_MUTE))
		{	//If both the string mute AND the palm mute flags are set, clear both
			*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_STRING_MUTE);
			*flags &= (~EOF_PRO_GUITAR_NOTE_FLAG_PALM_MUTE);
		}
	}

	if(desttrack != EOF_TRACK_DRUM)
	{	//Erase all drum flags from a non PART DRUMS note
		*flags &= (~EOF_NOTE_FLAG_Y_CYMBAL);				//Erase the yellow cymbal flag
		*flags &= (~EOF_NOTE_FLAG_B_CYMBAL);				//Erase the blue cymbal flag
		*flags &= (~EOF_NOTE_FLAG_G_CYMBAL);				//Erase the green cymbal flag
		*flags &= (~EOF_NOTE_FLAG_DBASS);					//Erase the double bass flag
	}
	else
	{	//Erase all non drum flags from a PART DRUMS note
		*flags &= (~EOF_NOTE_FLAG_CRAZY);	//Erase the "crazy" note flag
	}

	if(eof_song->track[desttrack]->track_behavior == EOF_KEYS_TRACK_BEHAVIOR)
	{	//For a note in any keys track, force the crazy flag to be set
		*flags |= EOF_NOTE_FLAG_CRAZY;
	}
}

void eof_menu_edit_paste_clear_range(unsigned long track, int note_type, unsigned long start, unsigned long end)
{
	unsigned long i, notepos, notelen;


	for(i = eof_get_track_size(eof_song, track); i > 0; i--)
	{	//For each note in the specified track
		notepos = eof_get_note_pos(eof_song, track, i - 1);
		notelen = eof_get_note_length(eof_song, track, i);

		if((notepos <= end) && (notepos + notelen >= start))
		{	//If the note begins at or before the specified end position and the note ends at or after the specified start position
			eof_track_delete_note(eof_song, track, i - 1);
		}
	}
}

void eof_menu_paste_read_clipboard_note(PACKFILE * fp, EOF_EXTENDED_NOTE *temp_note)
{
	if(!fp || !temp_note)
		return;

	/* read the note */
	eof_load_song_string_pf(temp_note->name, fp, sizeof(temp_note->name));	//Read the note's name
	temp_note->note = pack_igetl(fp);	//Read the note fret values
	temp_note->pos = pack_igetl(fp);		//Read the note's position relative to within the selection
	pack_fread(&temp_note->porpos, sizeof(float), fp);	//Read the percent representing the note's start position within a beat
	pack_fread(&temp_note->porendpos, sizeof(float), fp);	//Read the percent representing the note's end position within a beat
	temp_note->beat = pack_igetl(fp);	//Read the beat the note starts in
	temp_note->endbeat = pack_igetl(fp);	//Read the beat the note ends in
	temp_note->length = pack_igetl(fp);	//Read the note's length
	temp_note->flags = pack_igetl(fp);	//Read the note's flags
	temp_note->legacymask = pack_igetl(fp);		//Read the note's legacy bitmask
	pack_fread(temp_note->frets, sizeof(temp_note->frets), fp);	//Read the note's fret array
	temp_note->ghostmask = pack_igetl(fp);				//Read the note's ghost bitmask
}
