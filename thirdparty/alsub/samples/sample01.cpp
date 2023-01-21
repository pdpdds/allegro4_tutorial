#include <allegro.h>
#include "alsub.h"
#include "sample.h"


// normal timer function
volatile int timer;
void timer_func()
{
	timer++;
}
END_OF_FUNCTION(timer_func);


// main function
int main(void)
{
	ALSUB sub;
	BITMAP *buffer, *fundo;
	MIDI *midi;
	DATAFILE *dat;
	FONT *fonte;

	// allegro initialization
	allegro_init();
	install_keyboard();
	install_timer();
	install_sound(DIGI_NONE, MIDI_AUTODETECT, "");
	set_window_close_button(0);
	set_color_depth(16);
	if(set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) < 0) {
		set_color_depth(15);
		if(set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) < 0) {
			set_color_depth(8);
			if(set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) < 0) {
				allegro_message("ERROR!\n%s", allegro_error);
			}
		}
	}

	buffer = create_bitmap(SCREEN_W, SCREEN_H);
	fundo = create_bitmap_ex(8, SCREEN_W, SCREEN_H);

	// disable color conversion and load datafile
	set_color_conversion(COLORCONV_NONE);
	dat = load_datafile("sample.dat");
	set_palette((RGB *)dat[LHOP_PAL].dat);
	fonte = (FONT *)dat[FONTE001].dat;
	text_mode(-1);

	// because stretch_blit can't convert colors
	stretch_blit((BITMAP *)dat[LHOP_BMP].dat, fundo, 0, 0, ((BITMAP *)dat[LHOP_BMP].dat)->w,
		((BITMAP *)dat[LHOP_BMP].dat)->h, 0, 0, fundo->w, fundo->h);

	// load midi and sub file
	midi = (MIDI *)dat[LHOP_MIDI].dat;
	if(sub.load("sample.dat#LHOP_SUB")) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("ERROR! Couldn't load midi");
		destroy_bitmap(buffer);
		destroy_midi(midi);
		return 1;
	}

	// start playing the midi
	play_midi(midi, 0);

	LOCK_VARIABLE(timer);
	LOCK_FUNCTION(timer_func);
	// because the midi has a delay
	timer = -100;
	// every 10 miliseconds, one frame ahead
	install_int(timer_func, 10);

	while(!key[KEY_ESC] && midi_pos >= 0) {
		// update subtitle
		sub.update_frame(timer);

		// draw backbuffer
		acquire_bitmap(buffer);
		blit(fundo, buffer, 0, 0, 0, 0, fundo->w, fundo->h);

		// draw 3 versions of subtitle with black borders
		sub.display(buffer, fonte, SCREEN_W/2, 10, makecol(255, 255, 0),
			makecol(0, 0, 0), CENTER, TOP);
		sub.display(buffer, fonte, SCREEN_W/2, SCREEN_H/2, makecol(0, 255, 255),
			makecol(0, 0, 0), CENTER, MIDDLE);
		sub.display(buffer, fonte, SCREEN_W/2, SCREEN_H-10, makecol(255, 255, 255),
			makecol(0, 0, 0), CENTER, BOTTOM);

		release_bitmap(buffer);
		// wait for vsync and draw buffer to screen
		vsync();
		acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
		release_screen();
	}

	// only for test purposes, converting subtitles from 100 fps to 29.97 fps
	sub.convert(100, 29.97);
	sub.save("temp.sub");

	// releasing memory
	destroy_bitmap(buffer);
	unload_datafile(dat);

	// final message
	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	allegro_message("Sample01\n\nExample program from AlSub version %s", ALSUB_VERSION_STR);

	// bye!
	return 0;
}
END_OF_MAIN();
