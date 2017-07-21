//xcr.c
//cc -o xcr $(pkg-config --cflags --libs cairo xcb xcb-icccm) xcr.c -lcairo -lxcb -lxcb-icccm
#include <cairo-xcb.h>
#include <cairo.h>
#include <stdlib.h>
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xcb_aux.h>
#include <xcb/xcb_icccm.h>
#include <xcb/xcb_image.h>

typedef struct {
    int width, height;
    int scrno;
    xcb_screen_t* scr;
    xcb_connection_t* connection;
    xcb_drawable_t win;
    unsigned int white;
    xcb_visualtype_t* visual_type;

    cairo_surface_t* surface;
    cairo_t* cr;
} Window;
Window window;

int makewindow()
{
    xcb_screen_iterator_t iter;
    xcb_depth_iterator_t depth_iter;

    window.width = 300;
    window.height = 200;

    window.connection = xcb_connect(NULL, &window.scrno);
    iter = xcb_setup_roots_iterator(xcb_get_setup(window.connection));
    for (; iter.rem; --window.scrno, xcb_screen_next(&iter))
        if (window.scrno == 0) {
            window.scr = iter.data;
            break;
        }
    window.win = xcb_generate_id(window.connection);
    window.white = window.scr->white_pixel;
    xcb_create_window(window.connection, XCB_COPY_FROM_PARENT,
        window.win, window.scr->root,
        0, 0,
        window.width, window.height,
        5,
        XCB_WINDOW_CLASS_INPUT_OUTPUT,
        window.scr->root_visual,
        XCB_CW_BACK_PIXEL,
        &window.white);
    xcb_icccm_set_wm_name(window.connection, window.win, XCB_ATOM_STRING, 8, strlen("xcr"), "xcr");
    xcb_map_window(window.connection, window.win);
    xcb_flush(window.connection);

    depth_iter = xcb_screen_allowed_depths_iterator(window.scr);
    for (; depth_iter.rem; xcb_depth_next(&depth_iter)) {
        xcb_visualtype_iterator_t visual_iter;

        visual_iter = xcb_depth_visuals_iterator(depth_iter.data);
        for (; visual_iter.rem; xcb_visualtype_next(&visual_iter)) {
            if (window.scr->root_visual == visual_iter.data->visual_id) {
                window.visual_type = visual_iter.data;
                goto visual_found;
            }
        }
    }
visual_found:;

    {
        window.surface = cairo_xcb_surface_create(window.connection, window.win, window.visual_type, window.width, window.height);
        window.cr = cairo_create(window.surface);

        cairo_select_font_face(window.cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(window.cr, 32.0);
        cairo_set_source_rgb(window.cr, 0.0, 0.0, 1.0);
        cairo_move_to(window.cr, 10.0, 50.0);
        cairo_show_text(window.cr, "Hello, world");

        cairo_surface_flush(window.surface);
        xcb_flush(window.connection);
    }
    return 0;
}

int destroywindow()
{
    cairo_destroy(window.cr);
    cairo_surface_destroy(window.surface);
    xcb_disconnect(window.connection);
    return 0;
}

int main(int argc, char** argv)
{

    makewindow();
    sleep(100);
    destroywindow();

    return 0;
}
