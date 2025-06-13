#ifndef UI_ABST_H
#define UI_ABST_H

// Forward declaration for opaque UI context/renderer handle
typedef struct UI_Context UI_Context;
typedef struct UI_Texture UI_Texture; // For images/cards
typedef struct UI_Font UI_Font;       // For text rendering

// --- Common Data Structures ---
typedef struct {
    int x, y, w, h;
} UI_Rect;

typedef struct {
    unsigned char r, g, b, a;
} UI_Color;

// --- Initialization and Cleanup ---
// Initializes the UI system (e.g., SDL_Init, create window & renderer)
// Returns a UI_Context pointer on success, NULL on failure.
UI_Context* ui_initialize(const char* title, int width, int height);

// Cleans up UI resources and shuts down the UI system
void ui_cleanup(UI_Context* ctx);

// --- Rendering ---
// Clears the screen
void ui_clear_screen(UI_Context* ctx, UI_Color color);

// Presents the rendered content to the screen
void ui_present_screen(UI_Context* ctx);

// Loads an image from a file path into a texture
UI_Texture* ui_load_texture(UI_Context* ctx, const char* file_path);

// Creates a texture from raw pixel data (e.g., for embedded card images if not replaced)
// UI_PixelFormat will need to be defined (e.g., UI_PIXELFORMAT_RGB24, UI_PIXELFORMAT_RGBA32)
// typedef enum { UI_PIXELFORMAT_UNKNOWN, UI_PIXELFORMAT_RGB24, UI_PIXELFORMAT_RGBA32 } UI_PixelFormat;
// UI_Texture* ui_create_texture_from_data(UI_Context* ctx, unsigned char* pixel_data, int width, int height, UI_PixelFormat format);

// Frees a texture
void ui_free_texture(UI_Texture* texture);

// Draws a texture (or part of it) to the screen at (x, y)
// src_rect can be NULL to draw the whole texture
// dest_rect specifies the position and size on screen
void ui_draw_texture(UI_Context* ctx, UI_Texture* texture, const UI_Rect* src_rect, const UI_Rect* dest_rect);

// Loads a font
UI_Font* ui_load_font(UI_Context* ctx, const char* font_path, int point_size);

// Frees a font
void ui_free_font(UI_Context* ctx, UI_Font* font);

// Renders text to a texture (which can then be drawn with ui_draw_texture)
UI_Texture* ui_render_text_to_texture(UI_Context* ctx, UI_Font* font, const char* text, UI_Color color);

// Gets the dimensions of a rendered text (useful for layout)
void ui_get_text_size(UI_Font* font, const char* text, int* width, int* height);

// Draws a filled rectangle
void ui_fill_rect(UI_Context* ctx, const UI_Rect* rect, UI_Color color);

// Draws a rectangle outline
void ui_draw_rect(UI_Context* ctx, const UI_Rect* rect, UI_Color color);

// Draws a line
void ui_draw_line(UI_Context* ctx, int x1, int y1, int x2, int y2, UI_Color color);


// --- Event Handling ---
typedef enum {
    UI_EVENT_NONE,
    UI_EVENT_QUIT,
    UI_EVENT_KEY_DOWN,
    UI_EVENT_KEY_UP,
    UI_EVENT_MOUSE_BUTTON_DOWN,
    UI_EVENT_MOUSE_BUTTON_UP,
    UI_EVENT_MOUSE_MOTION,
    UI_EVENT_WINDOW_EXPOSED, // For redraws
    UI_EVENT_WINDOW_RESIZED // If dynamic resizing is supported
    // ... other events as needed
} UI_EventType;

// Key symbol definitions (can be mapped from SDL_Keycode or X11 Keysyms)
// This is a simplified example; a more comprehensive mapping would be needed.
typedef enum {
    UI_KEY_UNKNOWN,
    UI_KEY_RETURN,
    UI_KEY_ESCAPE,
    UI_KEY_BACKSPACE,
    UI_KEY_TAB,
    UI_KEY_SPACE,
    UI_KEY_LEFT,
    UI_KEY_RIGHT,
    UI_KEY_UP,
    UI_KEY_DOWN,
    UI_KEY_F1,
    UI_KEY_0, UI_KEY_1, UI_KEY_2, UI_KEY_3, UI_KEY_4,
    UI_KEY_5, UI_KEY_6, UI_KEY_7, UI_KEY_8, UI_KEY_9,
    UI_KEY_A, /* ... through Z */ UI_KEY_Z,
    // ... other keys
} UI_KeySymbol;

typedef struct {
    UI_EventType type;
    union {
        struct { UI_KeySymbol sym; unsigned int mod; /* for shift, ctrl, alt */ char text[32]; /* for text input */ } key;
        struct { int x, y; unsigned char button; unsigned char clicks; } mouse_button; // button: 1=left, 2=middle, 3=right
        struct { int x, y; int xrel; int yrel; unsigned int state; /* button mask */ } mouse_motion;
        struct { int w, h; } window_resize;
    } data;
} UI_Event;

// Polls for the next event. Returns 1 if an event was retrieved, 0 otherwise.
int ui_poll_event(UI_Context* ctx, UI_Event* event);

// Waits for an event indefinitely (or with a timeout)
// int ui_wait_event(UI_Context* ctx, UI_Event* event, int timeout_ms); // timeout_ms <= 0 means wait indefinitely

// --- Window Management ---
void ui_set_window_title(UI_Context* ctx, const char* title);
void ui_get_window_size(UI_Context* ctx, int* width, int* height);
// void ui_set_window_icon(UI_Context* ctx, UI_Texture* icon_texture); // If needed

// --- Cursor Management ---
typedef enum { UI_CURSOR_ARROW, UI_CURSOR_HAND, UI_CURSOR_IBEAM, UI_CURSOR_WAIT } UI_CursorType;
void ui_set_cursor(UI_Context* ctx, UI_CursorType cursor_type);
// void ui_show_cursor(UI_Context* ctx, int show);


// --- Dialog and Game-Specific UI Elements ---
// This section will require significant design based on xdial.c and skat.c UI needs.
// For now, these are conceptual.

#define UI_MAX_STRING_LEN 64 // Example length

// Generic structure for a UI element/widget (very basic)
typedef struct UI_Widget UI_Widget; // Opaque

typedef enum {
    UI_WIDGET_BUTTON,
    UI_WIDGET_LABEL,
    UI_WIDGET_TEXT_INPUT
    // ...
} UI_WidgetType;

// UI_Widget* ui_create_widget(UI_Context* ctx, UI_WidgetType type, const UI_Rect* rect, const char* text_or_id);
// void ui_draw_widget(UI_Context* ctx, UI_Widget* widget);
// void ui_handle_widget_event(UI_Widget* widget, const UI_Event* event); // Widget-specific event handling
// void ui_destroy_widget(UI_Widget* widget);

// Specific game elements
void ui_draw_card_back(UI_Context* ctx, const UI_Rect* dest_rect);
void ui_draw_card_face(UI_Context* ctx, int card_index, const UI_Rect* dest_rect); // card_index maps to specific card face

// Displaying player names, scores, game messages
void ui_display_text_at(UI_Context* ctx, const char* text, UI_Font* font, UI_Color color, int x, int y, int centered);

// For dialog boxes that were previously in xdial.c

// --- Dialog Management ---
typedef enum {
    UI_DIALOG_RESULT_CANCEL = 0, // Or No
    UI_DIALOG_RESULT_OK = 1,     // Or Yes
    UI_DIALOG_RESULT_OTHER = 2
} UI_DialogResult;

typedef struct {
    int sort_order_inverted;    // Example: maps to sort1[sn]
    int alternate_symbol_set; // Example: maps to alternate[sn]
    int show_hints;
    char player_name1[UI_MAX_STRING_LEN]; // Example
    char player_name2[UI_MAX_STRING_LEN]; // Example
    int card_style; // 0=fr2, 1=fr4, 2=de2, 3=de4
    int current_language; // 0=lang1, 1=lang2 (or use string)
    // Add other relevant options from xdial.c's various option dialogs
} UI_GameOptions;

int ui_show_options_dialog(UI_Context* ctx, UI_GameOptions* options);
UI_DialogResult ui_show_yes_no_dialog(UI_Context* ctx, const char* title, const char* message);
char* ui_show_input_text_dialog(UI_Context* ctx, const char* title, const char* prompt, const char* initial_value);

typedef struct {
    char player_names[3][UI_MAX_STRING_LEN];
    int final_scores[3]; // Points for this game for each player
    int total_scores[3]; // Overall total scores after this game
    int game_value_spieler; // Actual value for the 'spieler' (can be negative if lost)
    int displayed_game_value; // Absolute game value (e.g., 24 for Grand)
    int trumpf_played; // -1 Null, 0-3 Suit, 4 Grand, 5 Ramsch
    int skat_card1, skat_card2; // Actual card indices
    int spieler_idx;
    int gewonnen; // 1 if spieler won, 0 if lost
    char message1[UI_MAX_STRING_LEN]; // e.g., "Schneider", "Schwarz", "Hand"
    char message2[UI_MAX_STRING_LEN]; // e.g., "Ouvert", "Kontra", "Re"
    int bockinc; // How many bock rounds were triggered
} UI_GameResultData;
void ui_show_game_result_dialog(UI_Context* ctx, const UI_GameResultData* result_data);

void ui_show_thinking_dialog(UI_Context* ctx, const char* message); // Could be non-blocking
void ui_hide_thinking_dialog(UI_Context* ctx);

// --- Game Specific Actions Requiring UI ---
typedef enum { UI_HAND_ACTION_UNKNOWN = 0, UI_HAND_ACTION_TAKE_SKAT, UI_HAND_ACTION_PLAY_HAND } UI_HandAction;
UI_HandAction ui_prompt_hand_action(UI_Context* ctx, int current_reiz_value);

typedef struct {
    int game_type; // -1 Null, 0-3 Suit, 4 Grand. Consider enum.
    int hand_options; // Bitmask: 1=Hand, 2=Schneider, 4=Schwarz, 8=Ouvert
} UI_AnnouncedGame;
int ui_prompt_announce_game(UI_Context* ctx, UI_AnnouncedGame* announced_game); // Returns 1 if announced, 0 if cancelled

UI_DialogResult ui_prompt_kontra(UI_Context* ctx, const char* opponent_name);
UI_DialogResult ui_prompt_re(UI_Context* ctx, const char* opponent_name);


#endif // UI_ABST_H
