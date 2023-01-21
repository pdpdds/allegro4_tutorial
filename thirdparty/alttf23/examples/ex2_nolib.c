//----------------------------------------------------------------------------
//
// AATEXT - Antialiased text fonts for Allegro
//
// Douglas Eleveld (D.J.Eleveld@anest.azg.nl)
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//
// Simple loading of a TTF file in two point sizes.
//
// Example 2 modified to directly include the C files so that linking to a 
// libalttf is not necessary,
//
// Written by Doug Eleveld
//
//----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include "allegro.h"
#include "allegttf.h"

#include "../source/freetype/ttapi.c"
#include "../source/freetype/ttcalc.c"
/*#include "../source/freetype/ttdebug.c" not needed, probably more could be removed */
#include "../source/freetype/ttfile.c"
#include "../source/freetype/ttinterp.c"
#include "../source/freetype/ttmemory.c"
#include "../source/freetype/ttobjs.c"
#include "../source/freetype/ttcache.c"
#include "../source/freetype/ttcmap.c"
#include "../source/freetype/ttextend.c"
#include "../source/freetype/ttgload.c"
#include "../source/freetype/ttload.c"
#include "../source/freetype/ttmutex.c"
#include "../source/freetype/ttraster.c"
#include "../source/aaclip.c"
#include "../source/aaload2.c"
#include "../source/aamap.c"
#include "../source/aatext15.c"
#include "../source/aatext1x.c"
#include "../source/aatext32.c"
#include "../source/aatext.c"
#include "../source/aaload1.c"
#include "../source/aaload3.c"
#include "../source/aasetup.c"
#include "../source/aatext16.c"
#include "../source/aatext24.c"
#include "../source/aatext8.c"

//----------------------------------------------------------------------------
int main(void)
{
	FONT *thefont_10point;
	FONT *thefont_20point;
	PALETTE pal;
	RGB black;

	black.r = 0;
	black.g = 0;
	black.b = 0;

	// Setup Allegro and some internal stuff
	allegro_init();
	install_keyboard();

	printf("Loading a ttf file in different point sizes (no antialiasing)\n");
	printf("Press any key to exit...\n");

	// Try and set the graphic mode
	set_color_depth(8);
	if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0) {
		// Warn that the mode did not work
		set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);
		printf("Could not set graphics mode.\n");
		return 1;
	}
	// Load the small font data in
	thefont_10point = load_ttf_font("dejavusans.ttf", 10, 0);
	if (thefont_10point == NULL) {
		set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);
		printf("Could not load ttf slicker.ttf [10 point]\n");
		return 1;
	}
	// Load the large font data in
	thefont_20point = load_ttf_font("dejavusans.ttf", 20, 0);
	if (thefont_20point == NULL) {
		set_gfx_mode(GFX_TEXT, 80, 25, 0, 0);
		printf("Could not load ttf slicker.ttf [20 point]\n");
		return 1;
	}
	// Create the color maps and RGB table for the antialiased fonts
	generate_332_palette(pal);
	set_palette(pal);

	// Make sure that we have black as colour zero
	set_color(0, &black);

	// Draw background
	clear_to_color(screen, makecol(0, 0, 0));
	text_mode(0);

	textout(screen, thefont_10point, "This is 10 point DejaVuSans...", 10, 10, makecol(255, 255, 255));
	textout(screen, thefont_20point, "This is 20 point DejaVuSans...", 10, 30, makecol(255, 255, 255));

	while (!keypressed());

	// Close up shop and exit
	destroy_font(thefont_10point);
	destroy_font(thefont_20point);

	antialias_exit();
	remove_keyboard();
	allegro_exit();

	return 0;
}

END_OF_MAIN();
//----------------------------------------------------------------------------
