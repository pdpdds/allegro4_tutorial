#include <algif.h>

#undef main
int main()
{
    char const *name = "gifs/alex.gif";
    //if (argc == 2)
      //  name = argv[1];
    allegro_init ();
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);

    clear_to_color (screen, makecol (255, 0, 255));
    install_keyboard ();
    algif_init ();
    BITMAP *bmp = load_bitmap (name, NULL);
    if (bmp)
    {
        draw_sprite(screen, bmp, 0, 0);
        readkey ();
    }
    else
    {
        allegro_message ("Could not open %s.\n", name);
        return 1;
    }
    return 0;
}
//END_OF_MAIN ()

