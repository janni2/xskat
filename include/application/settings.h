/*
    XSkat Application Layer - Settings Management
    Copyright (C) 2004  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#ifndef SETTINGS_H
#define SETTINGS_H

// Player settings structure
typedef struct {
    int strategy;       // AI strategy level
    int hints;          // Show hints flag
    int blatt;          // Card design preference
    int lang;           // Language setting
    int maxrw;          // Maximum reiz value
    int sort1, sort2;   // Sorting preferences
    int alternate;      // Alternate play flag
    int splfirst;       // Who plays first
    int keyboard;       // Keyboard input mode
    int abkuerz;        // Abbreviation mode
    int briefmsg;       // Brief messages flag
    int trickl2r;       // Trick display left to right
} player_settings_t;

// Game settings structure
typedef struct {
    int numsp;          // Number of players
    int numgames;       // Number of games
    int playramsch;     // Play Ramsch variant
    int playsramsch;    // Play Schar-Ramsch variant
    int sramschstufe;   // Schar-Ramsch level
    int playkontra;     // Allow Kontra
    int kontrastufe;    // Kontra level
    int playbock;       // Play Bock games
    int bockevents;     // Bock triggering events
    int resumebock;     // Resume Bock games
    int spitzezaehlt;   // Count Spitzen
    int revolution;     // Revolution rules
    int klopfen;        // Allow Klopfen
    int schenken;       // Allow Schenken
    int oldrules;       // Use old rules
    int fastdeal;       // Fast dealing
} game_settings_t;

// File paths structure
typedef struct {
    char *list_file;
    char *game_file;
    char *prot_file;
    char *opt_file;
    char *cards_file;
} file_paths_t;

// Settings management functions
void settings_init(void);
void settings_load_from_file(const char *filename);
void settings_save_to_file(const char *filename);
void settings_apply_defaults(void);

// Player settings functions
void player_settings_init(int player_id);
void player_settings_set_strategy(int player_id, int strategy);
void player_settings_set_hints(int player_id, int hints);
void player_settings_set_language(int player_id, int lang);

// Game settings functions
void game_settings_init(void);
void game_settings_set_ramsch(int enabled);
void game_settings_set_kontra(int enabled);
void game_settings_set_bock(int enabled);

// File path management
void file_paths_init(void);
void file_paths_set_game_file(const char *path);
void file_paths_set_log_file(const char *path);

// Settings validation
int settings_validate(void);

#endif /* SETTINGS_H */