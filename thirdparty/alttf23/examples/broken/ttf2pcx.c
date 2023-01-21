//----------------------------------------------------------------------------
//
// ALLEGTTF - True type font loader for Allegro
//
// Douglas Eleveld (D.J.Eleveld@anest.azg.nl)
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//
// TTF2PCX program - Make Allegro PCX font file from TTF file
//
//----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../source/internal.h"
#include "allegttf.h"

//#include <allegro/aintern.h>

//----------------------------------------------------------------------------
// Parse an arg out of the program arguments
const char *argfind(const char *arg, const int argc, const char *argv[])
{
	int i;
	int l = strlen(arg);

	// Look at all the arguments
	for (i = 0; i < argc; i++) {
		// Look for a match
		if (strncmp(argv[i], arg, l) == 0) {
			return &(argv[i][l]);
		}
	}
	// No match found
	return NULL;
}

//----------------------------------------------------------------------------
// Indicate program usage
const char *_usage =
	"TTF2PCX 1.0 - Doug Eleveld < deleveld @ dds.nl >" "Usage:TTF2PCX < flags > <ttffont > <pcxfile >"
	"Flags can be:-p Set font point size < default = 10 >" "-ph Set font horizontal point size"
	"- pv Set font vertical point size" "- sn Use no font smoothing <"
	"default >-st Use ttf font smoothing(antialiasing + hinting)" "- sr Use real font smoothing(antialiasing)"
	"- a Use ascii character set 32 to 255 <" "default >-u Use unicode character set 0 to 224 -"
	"cs Start character(must be >= 32 with ascii) < default ="
	"32 > -ce End character(must be <= 224 with ascii) < default =" "128 >"
	"-v Draw the font file on the screen and wait for a keypress before" "exiting Times font,"
	"20 point basic ascii charater set to times.pcx TTF2PCX - p20 -"
	"a times.ttf times.pcx Times font, 20 point horizontal,"
	"25 point vertical unicode charaters 1 to 55 set to times.pcx TTF2PCX -"
	"ph20 - pv25 - cs1 - ce55 - u times.ttf times.pcx ";

void usage(void)
{
	fprintf(stdout, "%s", _usage);
	exit(0);
}

//----------------------------------------------------------------------------DJDIR%/info;%DJDIR%/gnu/emacs/info
int main(const int argc, const char *argv[])
{
	int i;

	FONT *f;
	BITMAP *dest;
	BITMAP *thechar;

	int startchar = 32;
	int endchar = 128;

	int points_w = 10;
	int points_h = 10;
	int fontsmooth = ALLEGTTF_NOSMOOTH;
	int ascii = 1;
	int visual = 0;

	const char *ttffile;
	const char *pcxfile;

	PALETTE origpal;

	const char *s;

	int w, h, bw, bh;

	// Check input arguments
	if (argc < 3)
		usage();

	// Look for a general point size
	s = argfind("-p", argc, argv);
	if (s)
		points_h = points_w = atoi(s);

	// Look for a horizontal point size
	s = argfind("-ph", argc, argv);
	if (s)
		points_w = atoi(s);

	// Look for a vertical point size
	s = argfind("-pv", argc, argv);
	if (s)
		points_h = atoi(s);

	// Make sure font size is good
	if (points_h <= 0)
		points_h = 10;
	if (points_w <= 0)
		points_w = 10;

	// Look for unicode char set
	s = argfind("-u", argc, argv);
	if (s)
		ascii = 0;

	// Look for ascii char set
	s = argfind("-a", argc, argv);
	if (s)
		ascii = 1;

	// Look for a starting and ending chars
	s = argfind("-cs", argc, argv);
	if (s)
		startchar = atoi(s);
	if (startchar < 32 && ascii)
		startchar = 32;

	s = argfind("-ce", argc, argv);
	if (s)
		endchar = atoi(s);
	if (endchar > 224 && ascii)
		endchar = 224;

	// Look for a font smoothing
	s = argfind("-st", argc, argv);
	if (s)
		fontsmooth = ALLEGTTF_TTFSMOOTH;

	s = argfind("-sr", argc, argv);
	if (s)
		fontsmooth = ALLEGTTF_REALSMOOTH;

	s = argfind("-sn", argc, argv);
	if (s)
		fontsmooth = ALLEGTTF_NOSMOOTH;

	// Look for visual info
	s = argfind("-v", argc, argv);
	if (s)
		visual = 1;

	// Get the filenames out
	ttffile = argv[argc - 2];
	pcxfile = argv[argc - 1];

	// Startup allegro
	allegro_init();
	install_keyboard();
	if (visual)
		set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);

	/* Setup a nice black-white gradient palette */
	for (i = 0; i < 256; i++) {
		desktop_palette[i].r = i / 4;
		desktop_palette[i].g = i / 4;
		desktop_palette[i].b = i / 4;
	}
	if (visual) {
		get_palette(origpal);
		set_palette(desktop_palette);
	}
	// Try and load the ttf font in
	f = load_ttf_font_ex2(ttffile, points_w, points_h, startchar, endchar, fontsmooth);
	if (f == NULL) {
		fprintf(stderr, "Could not load ttf file: %s", ttffile);
		exit(0);
	}

	/* Figure out the size of the destination bitmap */
	thechar = ((struct FONT_COLOR_DATA *) f->data)->bitmaps[0];
	w = ((thechar->w * 2) + 16) & 0xFFF0;
	h = ((thechar->h) + 16) & 0xFFF0;

	bw = 1 + w * 16;
	bh = 1 + h * ((points_h + 15) / 16) * 12;

	/* Make a bit destination bitmap */
	dest = create_bitmap_ex(8, bw, bh);
	if (dest == NULL) {
		fprintf(stderr, "Could not allocate bitmap");
		exit(0);
	}
	clear_to_color(dest, 255);

	if (visual)
		clear_to_color(screen, 255);

	text_mode(0);

	// Possibly setup the antialiasing stuff
	if (fontsmooth)
		antialias_init(desktop_palette);

	// Draw characters from 32 to 255
	for (i = startchar; i < endchar; i++) {
		int x = 1 + w * (i & 15);
		int y = 1 + h * (i / 16);

		// Put the character onto the bitmap
		thechar = ((struct FONT_COLOR_DATA *) f->data)->bitmaps[i - startchar];

		if (thechar != NULL)
			blit(thechar, dest, 0, 0, x, y, thechar->w, thechar->h);
	}

	// Possibly display the bitmap
	if (visual)
		blit(dest, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

	/* Save the PCX file out */
	save_pcx((char *) pcxfile, dest, desktop_palette);

	destroy_bitmap(dest);

	if (visual) {
		while (!keypressed());
		set_palette(origpal);
		set_gfx_mode(GFX_TEXT, 80, 20, 0, 0);
	}

	antialias_exit();
	allegro_exit();
	return 0;
}

END_OF_MAIN();
//----------------------------------------------------------------------------
