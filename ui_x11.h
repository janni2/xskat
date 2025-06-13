#ifndef UI_X11_H
#define UI_X11_H

#include "ui_abst.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h> // For cursors

struct UI_Context {
    Display* display;
    int screen;
    Window root_window;
    Window main_window;
    GC gc;
    GC gc_xor;
    GC gc_background;
    Colormap colormap;
    XFontStruct* default_font_struct;
    Visual* visual;

    unsigned long x_black_pixel;
    unsigned long x_white_pixel;

    int width;
    int height;

    Pixmap back_buffer; // For double buffering

    // Card and symbol pixmaps
    Pixmap card_pixmaps[33]; // 0 for back, 1-32 for faces (card_index 0-31)
    Pixmap symbols_pixmap;
    Pixmap large_symbols_pixmap; // If large card variant is distinct
    // Card dimensions
    int card_width_small;
    int card_height_small;
    int card_width_large;
    int card_height_large;
    Bool use_large_cards; // To select which dimensions/symbols to use

    // Color management
    XColor x_color_cache[256]; // Cache for allocated XColor structs
    int x_color_cache_count;   // Number of colors in x_color_cache
    char program_name[64];    // To store the program name like "xskat" for XGetDefault
    unsigned long x_pixel_foreground;
    unsigned long x_pixel_background;
    unsigned long x_pixel_button_face; // Example, if used
    // For closest_col's cache:
    XColor x_system_colormap_cache[256]; // Cache of system's colormap
    Bool x_system_colormap_cached;     // Flag if x_system_colormap_cache is populated
    int x_display_planes; // Store display depth/planes

    int card_style; // 0=fr2, 1=fr4, 2=de2, 3=de4 (maps to 'blatt' array logic)
    unsigned long x_pixel_card_symbol_black; // For black symbols like K, Q, J, numbers
    unsigned long x_pixel_card_symbol_red;   // For red symbols like Hearts, Diamonds

    // Dialog related fields
    OBJECT* current_active_dialog_object;
    int dialog_result_value;
    int dialog_active_button_idx; // For tracking focused button
    char input_text_buffer[256]; // For text input dialogs
    Bool is_dialog_active; // Flag to indicate a modal dialog loop is running
    char yes_no_title_buffer[128];
    char yes_no_message_buffer[256];
    int current_language_index;

    // Thinking dialog
    Window thinking_dialog_window;
    char thinking_message_buffer[256];
    GC thinking_gc;

    Cursor arrow_cursor;
    Cursor hand_cursor;
    Cursor wait_cursor;
    // Add ibeam_cursor if text input becomes a feature
};

struct UI_Texture {
    Pixmap pixmap;
    Display* display; // To free the pixmap
    int width;
    int height;
    int depth;
};

struct UI_Font {
    XFontStruct* font_struct;
    Display* display; // To free the font
};

// Helper function (declaration)
unsigned long ui_x11_get_pixel(UI_Context* ctx, UI_Color color);
// Global display pointer for font operations if context is not available (temporary)
extern Display* ui_x11_global_display_for_fonts;


#endif // UI_X11_H
