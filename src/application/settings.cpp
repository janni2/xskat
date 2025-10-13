/*
    XSkat Application Layer - Settings Management Implementation
    Copyright (C) 2004  Gunter Gerhardt

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#include "application/settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External references to global settings (will be gradually refactored)
extern int numsp, numgames;
extern int strateg[3], stgset[3];
extern int hints[3], hintsset[3];
extern int blatt[3], blattset[3];
extern int lang[3], langset[3];
extern int maxrw[3], sort1[3], sort2[3], alternate[3], splfirst[3];
extern int keyboard[3], keyboardset[3];
extern int abkuerz[3], abkuerzset[3];
extern int briefmsg[3], briefmsgset[3];
extern int trickl2r[3], trickl2rset[3];
extern int playramsch, ramschset;
extern int playsramsch, sramschset, sramschstufe;
extern int playkontra, kontraset, kontrastufe;
extern int playbock, bockset, bockevents, bockeventsset;
extern int resumebock, resumebockset;
extern int spitzezaehlt, spitzezaehltset;
extern int revolution, revolutionset;
extern int klopfen, klopfenset;
extern int schenken, schenkenset;
extern int oldrules, oldrulesset;
extern int fastdeal, fastdealset;
extern char *list_file, *game_file, *prot_file, *opt_file, *cards_file;

// Static settings structures
static player_settings_t player_settings[3];
static game_settings_t game_settings;
static file_paths_t file_paths;

void settings_init(void) {
    // Initialize default values
    for (int i = 0; i < 3; i++) {
        player_settings_init(i);
    }
    game_settings_init();
    file_paths_init();
}

void player_settings_init(int player_id) {
    if (player_id < 0 || player_id >= 3) return;
    
    player_settings[player_id].strategy = 0;
    player_settings[player_id].hints = 0;
    player_settings[player_id].blatt = 0;
    player_settings[player_id].lang = 0;
    player_settings[player_id].maxrw = 0;
    player_settings[player_id].sort1 = 0;
    player_settings[player_id].sort2 = 0;
    player_settings[player_id].alternate = 0;
    player_settings[player_id].splfirst = 0;
    player_settings[player_id].keyboard = 0;
    player_settings[player_id].abkuerz = 0;
    player_settings[player_id].briefmsg = 0;
    player_settings[player_id].trickl2r = 0;
}

void game_settings_init(void) {
    game_settings.numsp = 1;
    game_settings.numgames = 1;
    game_settings.playramsch = 0;
    game_settings.playsramsch = 0;
    game_settings.sramschstufe = 1;
    game_settings.playkontra = 0;
    game_settings.kontrastufe = 1;
    game_settings.playbock = 0;
    game_settings.bockevents = 0;
    game_settings.resumebock = 0;
    game_settings.spitzezaehlt = 1;
    game_settings.revolution = 0;
    game_settings.klopfen = 0;
    game_settings.schenken = 0;
    game_settings.oldrules = 0;
    game_settings.fastdeal = 0;
}

void file_paths_init(void) {
    file_paths.list_file = NULL;
    file_paths.game_file = NULL;
    file_paths.prot_file = NULL;
    file_paths.opt_file = NULL;
    file_paths.cards_file = NULL;
}

void player_settings_set_strategy(int player_id, int strategy) {
    if (player_id < 0 || player_id >= 3) return;
    player_settings[player_id].strategy = strategy;
    strateg[player_id] = strategy;
}

void player_settings_set_hints(int player_id, int hint_setting) {
    if (player_id < 0 || player_id >= 3) return;
    player_settings[player_id].hints = hint_setting;
    hints[player_id] = hint_setting;
}

void player_settings_set_language(int player_id, int language) {
    if (player_id < 0 || player_id >= 3) return;
    player_settings[player_id].lang = language;
    lang[player_id] = language;
}

void game_settings_set_ramsch(int enabled) {
    game_settings.playramsch = enabled;
    playramsch = enabled;
}

void game_settings_set_kontra(int enabled) {
    game_settings.playkontra = enabled;
    playkontra = enabled;
}

void game_settings_set_bock(int enabled) {
    game_settings.playbock = enabled;
    playbock = enabled;
}

void file_paths_set_game_file(const char *path) {
    if (file_paths.game_file) {
        free(file_paths.game_file);
    }
    if (path) {
        file_paths.game_file = strdup(path);
        game_file = file_paths.game_file;
    } else {
        file_paths.game_file = NULL;
        game_file = NULL;
    }
}

void file_paths_set_log_file(const char *path) {
    if (file_paths.prot_file) {
        free(file_paths.prot_file);
    }
    if (path) {
        file_paths.prot_file = strdup(path);
        prot_file = file_paths.prot_file;
    } else {
        file_paths.prot_file = NULL;
        prot_file = NULL;
    }
}

void settings_load_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return;
    
    // Simple settings file format parsing would go here
    // For now, just close the file
    fclose(file);
}

void settings_save_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return;
    
    // Write settings in a simple format
    fprintf(file, "# XSkat Settings File\n");
    fprintf(file, "numsp=%d\n", game_settings.numsp);
    fprintf(file, "playramsch=%d\n", game_settings.playramsch);
    fprintf(file, "playkontra=%d\n", game_settings.playkontra);
    
    for (int i = 0; i < 3; i++) {
        fprintf(file, "player%d_strategy=%d\n", i, player_settings[i].strategy);
        fprintf(file, "player%d_hints=%d\n", i, player_settings[i].hints);
        fprintf(file, "player%d_lang=%d\n", i, player_settings[i].lang);
    }
    
    fclose(file);
}

void settings_apply_defaults(void) {
    settings_init();
}

int settings_validate(void) {
    // Basic validation
    if (game_settings.numsp < 1 || game_settings.numsp > 3) return 0;
    if (game_settings.numgames < 1) return 0;
    
    for (int i = 0; i < 3; i++) {
        if (player_settings[i].strategy < -4 || player_settings[i].strategy > 4) return 0;
        if (player_settings[i].lang < 0 || player_settings[i].lang > 1) return 0;
    }
    
    return 1;
}