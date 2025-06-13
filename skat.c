/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt
    ... (copyright notice as before) ...
*/

#define SKAT_C

#include "skat.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <unistd.h> // For nanosleep, if used

#include "irc.h"
#include "null.h"
#include "ramsch.h"
#include "text.h" // For textarr, TX_ constants
#include "xdial.h"
#include "xio.h"
#include "ui_abst.h"

UI_Context* g_ui_context = NULL;
UI_Font* g_game_font = NULL;

// --- Dummy/Stub implementations for now ---
void read_list_stub() { fprintf(stdout, "STUB: read_list() - game server list reading skipped\n"); }
void read_opt_stub() { fprintf(stdout, "STUB: read_opt() - X options reading skipped\n"); }
void set_conames_stub() { fprintf(stdout, "STUB: set_conames() - computer opponent name setting skipped\n"); }
void setcurs(int f) {
    if (g_ui_context) {
        // Example: if (f == CUR_NORMAL) ui_set_cursor(g_ui_context, UI_CURSOR_ARROW);
    }
}
void put_box(int s) { /* UI_STUB: put_box for player %d */ }
void rem_box(int s) { /* UI_STUB: rem_box for player %d */ }
void inv_box(int s, int c, int rev) { /* UI_STUB: inv_box for player %d, item %d, rev %d */ }
void clear_info() { /* UI_STUB: clear_info called. Was for xdial options state. */ }
// --- End Stubs ---

// --- Helper Functions ---
static void get_player_name_str(int player_idx, char* buffer, int buffer_size) {
    if (!g_ui_context || player_idx < 0 || player_idx > 2 || !buffer) {
        if (buffer && buffer_size > 0) buffer[0] = '\0';
        return;
    }
    if (spnames[player_idx][0][g_ui_context->current_language_index] && spnames[player_idx][0][g_ui_context->current_language_index][0] != '\0') {
        snprintf(buffer, buffer_size, "%s %s",
                 spnames[player_idx][0][g_ui_context->current_language_index],
                 spnames[player_idx][1][g_ui_context->current_language_index]);
    } else {
        snprintf(buffer, buffer_size, "Player %d", player_idx + 1);
    }
}

static int get_trumpf_text_idx(int current_card_style, int current_trumpf_val) {
    if (revolang) return TX_REVOLUTION;
    if (current_trumpf_val == -1) return TX_NULL;
    if (current_trumpf_val == 4) return TX_GRAND;
    if (current_trumpf_val >= 0 && current_trumpf_val < 4) {
        // This mapping assumes TX_KARO, TX_HERZ, TX_PIK, TX_KREUZ are contiguous
        // and TX_SCHELLEN, TX_HERZ_DE, TX_BLATT, TX_EICHEL are also contiguous.
        // This matches typical textarr structure from original.
        if (current_card_style >= 2) { // German styles (e.g. blatt[sn] == 2 or 3)
            return TX_SCHELLEN + current_trumpf_val;
        } else { // French styles (e.g. blatt[sn] == 0 or 1)
            return TX_KARO + current_trumpf_val;
        }
    }
    return TX_GRAND; // Fallback
}


int left(s)int s;{ return (s + 1) % 3; }
int right(s)int s;{ return (s + 2) % 3; }
int iscomp(s)int s;{ return s >= numsp; }
void swap(i, j) int *i, *j;{int h;h=*i;*i=*j;*j=h;}
void setrnd(s, v) long *s, v;{ *s = v << 1 ? v : -1; }
int rndval(s, m)long* s;int m;{register long h=*s;int i;for(i=0;i<7;i++)h=(h<<16)|((((h<<1)^(h<<4))>>16)&0xffff);*s=h;return h&m;}
int rnd(m)int m;{ return rndval(&seed[1], m); }
void synerr(f, s) FILE* f;char* s;{ /* ... original content ... */ }
int get_game() { /* ... original content ... */ return 0;}
int gutesblatt() { /* ... original content ... */ return 0;}
void mischen() { /* ... original content ... */ }
int lower(c1, c2, n) int c1,c2,n; { /* ... original content ... */ return 0;}
void sort(sn) int sn; { /* ... original content ... */ }
void calc_rw(s) int s; { /* ... original content ... */ }

void initscr(int sn_unused, int sor_unused) {
    if (!g_ui_context) return;
    int card_width = g_ui_context->use_large_cards ? g_ui_context->card_width_large : g_ui_context->card_width_small;
    int card_height = g_ui_context->use_large_cards ? g_ui_context->card_height_large : g_ui_context->card_height_small;
    int player_hand_y = g_ui_context->height - card_height - 30;
    int player_hand_x_start = (g_ui_context->width - (10 * (card_width / 2 + 5) - 5)) / 2;
    int opponent_left_y = 20; int opponent_left_x_start = 20;
    int opponent_right_y = 20; int opponent_right_x_start = g_ui_context->width - (10 * (card_width / 3 + 3) ) - 20;
    int skat_x = (g_ui_context->width - (2 * card_width + 10)) / 2;
    int skat_y = g_ui_context->height / 2 - card_height - 10;
    int stich_base_x = (g_ui_context->width - (3 * card_width + 2 * 5)) / 2;
    int stich_y = g_ui_context->height / 2 - card_height / 2 - 10;
    UI_Color text_color = {0,0,0,255}; UI_Color name_color = {50,50,150,255};
    for (int i = 0; i < 10; ++i) { if (cards[0*10+i]>=0){UI_Rect r={player_hand_x_start+i*(card_width/2+5),player_hand_y,card_width,card_height};ui_draw_card_face(g_ui_context,cards[0*10+i],&r);}}
    for (int i = 0; i < 10; ++i) { UI_Rect r={opponent_left_x_start+i*(card_width/3+3),opponent_left_y,card_width,card_height}; if(cards[1*10+i]>=0){if(ouveang&&spieler==0)ui_draw_card_face(g_ui_context,cards[1*10+i],&r);else ui_draw_card_back(g_ui_context,&r);}}
    for (int i = 0; i < 10; ++i) { UI_Rect r={opponent_right_x_start+i*(card_width/3+3),opponent_right_y,card_width,card_height}; if(cards[2*10+i]>=0){if(ouveang&&spieler==0)ui_draw_card_face(g_ui_context,cards[2*10+i],&r);else ui_draw_card_back(g_ui_context,&r);}}
    if (phase >= ANSAGEN) { if (skatopen && (spieler == 0 || aufgedeckt)) { UI_Rect r1={skat_x,skat_y,card_width,card_height}; ui_draw_card_face(g_ui_context,cards[30],&r1); UI_Rect r2={skat_x+card_width+10,skat_y,card_width,card_height}; ui_draw_card_face(g_ui_context,cards[31],&r2);} else {UI_Rect r1={skat_x,skat_y,card_width,card_height}; ui_draw_card_back(g_ui_context,&r1); UI_Rect r2={skat_x+card_width+10,skat_y,card_width,card_height}; ui_draw_card_back(g_ui_context,&r2);}}
    if (stichopen > 0 && stich > 0 && stich <= 10) { for(int i=0;i<stichopen;++i){ int player_of_card=(prot2.anspiel[stich-1]+i)%3; int card_x=stich_base_x+player_of_card*(card_width+5); UI_Rect r={card_x,stich_y,card_width,card_height}; ui_draw_card_face(g_ui_context,stcd[i],&r);}}
    char buffer[128]; if(g_game_font){
        get_player_name_str(0, buffer, sizeof(buffer)); ui_display_text_at(g_ui_context,buffer,g_game_font,name_color,player_hand_x_start,player_hand_y+card_height+5,0);
        get_player_name_str(1, buffer, sizeof(buffer)); ui_display_text_at(g_ui_context,buffer,g_game_font,name_color,opponent_left_x_start,opponent_left_y+card_height+5,0);
        get_player_name_str(2, buffer, sizeof(buffer)); ui_display_text_at(g_ui_context,buffer,g_game_font,name_color,opponent_right_x_start,opponent_right_y+card_height+5,0);
        if (predef) { const char* pt = textarr[TX_VORDEFINIERTES_SPIEL].t[g_ui_context->current_language_index]; int msg_w,msg_h; ui_get_text_size(g_game_font,pt,&msg_w,&msg_h); ui_display_text_at(g_ui_context,pt,g_game_font,text_color,(g_ui_context->width-msg_w)/2,10,0);}
    }
}

void do_sagen(int s, int w) {
    char bid_text_buffer[10]; sprintf(bid_text_buffer, "%d", w);
    int bid_x = g_ui_context->width / 2 - 100 + s * 100; int bid_y = g_ui_context->height / 2 - 50;
    int text_w = 0, text_h = 0; if(g_game_font) ui_get_text_size(g_game_font, bid_text_buffer, &text_w, &text_h); else {text_w=20; text_h=10;}
    UI_Rect box_rect = {bid_x - 10, bid_y - text_h, text_w + 20, text_h + 10};
    UI_Color box_bg={220,220,220,255}; UI_Color box_border={0,0,0,255}; UI_Color text_color={0,0,0,255};
    ui_fill_rect(g_ui_context, &box_rect, box_bg); ui_draw_rect(g_ui_context, &box_rect, box_border);
    if(g_game_font) ui_display_text_at(g_ui_context, bid_text_buffer, g_game_font, text_color, bid_x, bid_y, 0);
    // stdwait();
    sagte18[s] = 1;
}
void do_passen(int s) {
    const char* passe_text = textarr[TX_PASSE].t[g_ui_context->current_language_index];
    int bid_x = g_ui_context->width / 2 - 100 + s * 100; int bid_y = g_ui_context->height / 2 - 50;
    int text_w = 0, text_h = 0; if(g_game_font && ctx->default_font_struct) ui_get_text_size(g_game_font, passe_text, &text_w, &text_h); else {text_w=40; text_h=10;}
    UI_Rect box_rect = {bid_x - 10, bid_y - text_h, text_w + 20, text_h + 10};
    UI_Color box_bg={200,200,255,255}; UI_Color box_border={0,0,0,255}; UI_Color text_color={0,0,0,255};
    ui_fill_rect(g_ui_context, &box_rect, box_bg); ui_draw_rect(g_ui_context, &box_rect, box_border);
    if(g_game_font) ui_display_text_at(g_ui_context, passe_text, g_game_font, text_color, bid_x, bid_y, 0);
    // stdwait();
}
void do_akzept(int s) {
    const char* ja_text = textarr[TX_JA].t[g_ui_context->current_language_index];
    int bid_x = g_ui_context->width / 2 - 100 + s * 100; int bid_y = g_ui_context->height / 2 - 50;
    int text_w=0,text_h=0; if(g_game_font && ctx->default_font_struct) ui_get_text_size(g_game_font,ja_text,&text_w,&text_h); else {text_w=30;text_h=10;}
    UI_Rect box_rect = {bid_x - 10, bid_y - text_h, text_w + 20, text_h + 10};
    UI_Color box_bg={220,255,220,255}; UI_Color box_border={0,0,0,255}; UI_Color text_color={0,0,0,255};
    ui_fill_rect(g_ui_context, &box_rect, box_bg); ui_draw_rect(g_ui_context, &box_rect, box_border);
    if(g_game_font) ui_display_text_at(g_ui_context, ja_text, g_game_font, text_color, bid_x, bid_y, 0);
    // stdwait();
    sagte18[s] = 1;
}
void do_geben() { /* ... original content, but clear_info() is now a stub ... */
    int sn, i; static int f_static_var; // Renamed f to avoid conflict with other f in scope if any
    sort2[0]=sort2[1]=sort2[2]=0; prot2.verdopp[0]=prot2.verdopp[1]=prot2.verdopp[2]=0;
    schnang=schwang=ouveang=spitzeang=revolang=0; ndichtw=0; hintcard[0]=-1; hintcard[1]=-1;
    for(sn=0;sn<numsp;sn++)calc_desk(sn); if(!wieder){if(ramschspiele){if(trumpf==4)geber=right(geber);else ramschspiele--;}else if(bockspiele){bockspiele--;if(bockspiele%3==0&&playbock==2){ramschspiele=3;}} bockspiele+=3*bockinc; geber=left(geber);}else if(!vorhandwn){geber=left(geber+wieder);} bockinc=0; trumpf=-1; hoerer=ausspl=left(geber); sager=right(geber); mischen(); setcurs(0);
    givecard(hoerer,0);givecard(sager,0);givecard(geber,0);givecard(-1,0);givecard(hoerer,1);givecard(sager,1);givecard(geber,1);givecard(hoerer,2);givecard(sager,2);givecard(geber,2);
    for(sn=0;sn<numsp;sn++)initscr(sn,1);
    for(i=0;i<3;i++){lastmsaho[i]=0;sagte18[i]=0;} kontrastufe=0;schenkstufe=0;saho=1;reizp=0;
    clear_info();
    if(!dlhintseen){di_copyr(0);}else if(firstgame){di_options(-1);}else if(!f_static_var&&(sum[0][0]||sum[0][1]||sum[0][2]||sum[1][0]||sum[1][1]||sum[1][2]||sum[2][0]||sum[2][1]||sum[2][2])){di_delliste();} f_static_var=1;
    if(ramschspiele){phase=ANSAGEN;di_grandhand(hoerer);}else if(playramsch>1){init_ramsch();}else{putmark(hoerer);put_box(sager);put_box(hoerer);for(sn=numsp;sn<3;sn++)calc_rw(sn);phase=REIZEN;}
}
void do_handspiel() {
    int i, sn;
    prot2.anspiel[0]=ausspl; prot2.gemacht[0]=-1;
    if (phase == HANDSPIEL && g_ui_context && g_game_font && reizp >= 0 && reizp < (sizeof(reizw)/sizeof(reizw[0]))) {
        char reiz_msg[128]; UI_Color text_color = {0,0,0,255};
        sprintf(reiz_msg, textarr[TX_GEREIZT_BIS_L].t[g_ui_context->current_language_index], reizw[reizp]);
        int msg_w, msg_h; ui_get_text_size(g_game_font, reiz_msg, &msg_w, &msg_h);
        ui_display_text_at(g_ui_context, reiz_msg, g_game_font, text_color, (g_ui_context->width - msg_w) / 2, 40, 0);
    }
    if(reizp<0&&!ramschspiele){ if(playramsch>0){init_ramsch();return;} stich=1;fill_st();trumpf=4;set_prot();save_skat(1);prot1=prot2;spwert=0;update_list();save_list();if(logging)di_proto(0,1,1);splres=1;nextgame();phase=WEITER;for(sn=0;sn<numsp;sn++){draw_skat(sn);}if(numsp==1)di_wiederweiter(0);else di_weiter(1);return;}
    drkcd=0; if(!ramschspiele)handsp=0; stsum=0;vmh=0;gedr=0;
    for(i=0;i<10;i++)spcards[i]=cards[spieler*10+i]; save_skat(0); spcards[10]=cards[30];spcards[11]=cards[31];
    rem_box(sager);rem_box(hoerer);
    if (!iscomp(spieler) && !ramschspiele) {
        phase = HANDSPIEL;
        UI_HandAction hand_action = ui_prompt_hand_action(g_ui_context, (reizp >= 0 && reizp < 20 ? reizw[reizp] : 0));
        if (hand_action == UI_HAND_ACTION_TAKE_SKAT) { handsp = 0; do_handok(); }
        else if (hand_action == UI_HAND_ACTION_PLAY_HAND) { handsp = 1; do_handok(); }
        else { fprintf(stderr, "Hand action cancelled or unknown.\n"); /* TODO: Define game behavior */ }
    } else { do_handok(); }
}
void do_ansagen() {
    phase = ANSAGEN;
    UI_AnnouncedGame announced_game_data; int game_announced_successfully = 0;
    if (!iscomp(spieler) && !ramschspiele) {
        game_announced_successfully = ui_prompt_announce_game(g_ui_context, &announced_game_data);
    } else {
        remmark(1);
        announced_game_data.game_type = trumpf; announced_game_data.hand_options = 0;
        if(handsp) announced_game_data.hand_options |= 1; if(schnang) announced_game_data.hand_options |= 2;
        if(schwang) announced_game_data.hand_options |= 4; if(ouveang) announced_game_data.hand_options |= 8;
        game_announced_successfully = 1;
    }
    if (game_announced_successfully) {
        trumpf = announced_game_data.game_type; handsp = (announced_game_data.hand_options & 1)?1:0;
        schnang = (announced_game_data.hand_options & 2)?1:0; schwang = (announced_game_data.hand_options & 4)?1:0;
        ouveang = (announced_game_data.hand_options & 8)?1:0;
        if (g_ui_context && g_game_font) {
            char spiel_msg[128]; UI_Color text_color = {0,0,0,255};
            int game_text_idx = get_trumpf_text_idx(g_ui_context->card_style, trumpf);
            sprintf(spiel_msg, "%s %s", textarr[TX_GESPIELT_WIRD].t[g_ui_context->current_language_index], textarr[game_text_idx].t[g_ui_context->current_language_index]);
            int msg_w, msg_h; ui_get_text_size(g_game_font, spiel_msg, &msg_w, &msg_h);
            ui_display_text_at(g_ui_context, spiel_msg, g_game_font, text_color, (g_ui_context->width - msg_w) / 2, 60, 0);
        }
        if (game_announced_successfully && trumpf >= 0 && trumpf <= 4 && playkontra > 0) {
            int spieler_asked_re = 0;
            for (int opponent_idx = 0; opponent_idx < 3; ++opponent_idx) {
                if (opponent_idx == spieler) continue;
                if (!iscomp(opponent_idx) && (playkontra == 2 || (playkontra == 1 /* && sagte18[opponent_idx] */ ))) {
                    char opponent_name_buffer[UI_MAX_STRING_LEN]; get_player_name_str(opponent_idx, opponent_name_buffer, UI_MAX_STRING_LEN);
                    if (g_ui_context) { ui_set_cursor(g_ui_context, UI_CURSOR_ARROW); ui_present_screen(g_ui_context); }
                    UI_DialogResult kontra_res = ui_prompt_kontra(g_ui_context, opponent_name_buffer);
                    if (kontra_res == UI_DIALOG_RESULT_OK) {
                        kontrastufe = 1; prot2.verdopp[opponent_idx] = 2;
                        if (!iscomp(spieler) && !spieler_asked_re) {
                            char spieler_name_buffer[UI_MAX_STRING_LEN]; get_player_name_str(spieler, spieler_name_buffer, UI_MAX_STRING_LEN);
                            if (g_ui_context) ui_present_screen(g_ui_context);
                            UI_DialogResult re_res = ui_prompt_re(g_ui_context, spieler_name_buffer);
                            if (re_res == UI_DIALOG_RESULT_OK) { kontrastufe = 2; prot2.verdopp[spieler] = 2; }
                            spieler_asked_re = 1;
                        } else if (iscomp(spieler) && !spieler_asked_re) { spieler_asked_re = 1; }
                        break;
                    }
                }
            }
        }
        do_angesagt();
    } else { fprintf(stderr, "Game announcement cancelled by player.\n"); /* TODO: Handle this robustly */ }
}
void next_stich() {
    int nd; if (maxnimm() < 101) { /* stdwait(); */ }
    // info_stich calls removed, card drawing is part of initscr
    nimm_stich(); vmh=0; stich++; nd=0;
    if(stich==11||(trumpf==-1&& (nullv||(!ndichtw&&stich<10&&(nd=null_dicht(spieler,handsp,&prot1.skat[1][0],(int*)0,(int*)0,(int*)0)))))){ // Used prot1.skat[1] for consistency
        if(nd)di_dicht();else finishgame();
    }
}
void finishgame() {
    int i; // s removed as unused after info_stich removal
    if (stich < 11) { /* ... original content ... */ }
    calc_result(); set_prot(); prot1 = prot2; update_list();
    if (playbock) bockinc = check_bockevents();
    save_list(); if (logging) di_proto(0, 1, 1); splres = 1;

    UI_GameResultData result_data; memset(&result_data, 0, sizeof(UI_GameResultData));
    result_data.spieler_idx = spieler; result_data.gewonnen = spgew; result_data.bockinc = bockinc;
    result_data.trumpf_played = trumpf; result_data.displayed_game_value = spwert;
    if (spgew) { result_data.game_value_spieler = spwert; }
    else { result_data.game_value_spieler = (handsp || trumpf == -1 || oldrules) ? (-2 * spwert) : (-spwert);
        if (reizp >=0 && reizp < 20 && spwert < reizw[reizp] && trumpf >=0 && trumpf < (sizeof(rwert)/sizeof(rwert[0]))) {
            int rounded_reizw = ((reizw[reizp]-1)/rwert[trumpf]+1)*rwert[trumpf];
            result_data.game_value_spieler = (handsp||trumpf==-1||oldrules)?(-2*rounded_reizw):(-rounded_reizw);
        }
    }
    if (gedr == 2 || handsp) { result_data.skat_card1 = prot1.skat[1][0]; result_data.skat_card2 = prot1.skat[1][1];}
    else { result_data.skat_card1 = prot1.skat[0][0]; result_data.skat_card2 = prot1.skat[0][1];}
    for(i=0;i<3;++i){get_player_name_str(i,result_data.player_names[i],UI_MAX_STRING_LEN); result_data.total_scores[i]=sum[i][alist[i]]; /* Simplified final_scores */ if(i==spieler)result_data.final_scores[i]=result_data.game_value_spieler; else if(trumpf!=5)result_data.final_scores[i]=spgew?-(result_data.game_value_spieler/2):(-result_data.game_value_spieler/2);}
    result_data.message1[0]='\0'; result_data.message2[0]='\0';
    if(handsp&&trumpf!=5)strncat(result_data.message1,textarr[TX_HAND].t[g_ui_context->current_language_index],UI_MAX_STRING_LEN-1-strlen(result_data.message1));
    // Simplified message appends
    if(schnang&&!schwang){strncat(result_data.message1," Schneider",UI_MAX_STRING_LEN-1-strlen(result_data.message1));}
    if(schwang){strncat(result_data.message1," Schwarz",UI_MAX_STRING_LEN-1-strlen(result_data.message1));}
    if(ouveang&&trumpf!=5)strncat(result_data.message2,textarr[TX_OUVE].t[g_ui_context->current_language_index],UI_MAX_STRING_LEN-1-strlen(result_data.message2));
    if(kontrastufe>0&&trumpf!=5){strncat(result_data.message2,kontrastufe==1?" Kontra":" Kontra Re",UI_MAX_STRING_LEN-1-strlen(result_data.message2));}

    phase = RESULT;
    if (g_ui_context) ui_show_game_result_dialog(g_ui_context, &result_data);
    nextgame();
}

// ... (rest of skat.c: main, play, exitus, other game logic functions from previous full file listing) ...
// (Ensure all previous functions are here, only showing modified ones above for brevity)
void do_msagen(sn, w) int sn, w; { /* ... original content, calls do_msaho ... */ }
void do_mhoeren(sn) int sn; { /* ... original content, calls do_msaho ... */ }
void do_entsch() { /* ... original content ... */ }
void do_reizen() { /* ... original content ... */ }
void drueck(f, n, p) int f, n, *p; { /* ... original content ... */ }
void truempfe() { /* ... original content ... */ }
int tr_voll(sn, f) int sn, f; { /* ... original content ... */ return 0;}
int sage_kontra(sn) int sn; { /* ... original content ... */ return 0;}
int sage_re(sn) int sn; { /* ... original content ... */ return 0;}
int testgrand(bb,b,vh) int bb, b[4], vh; { /* ... original content ... */ return 0;}
void calc_inhand(sn) int sn; { /* ... original content ... */ }
int testhand() { /* ... original content ... */ return 0;}
void calc_drueck() { /* ... original content ... */ }
void nextgame() { /* ... original content ... */ }
void save_skat(i) int i; { /* ... original content ... */ }
int check_bockevents() { /* ... original content ... */ return 0;}
void update_list() { /* ... original content ... */ }
void do_grandhand(sn) int sn; { /* ... original content ... */ }
void set_prot() { /* ... original content ... */ }
void do_druecken() { /* ... original content ... */ }
void do_handok() { /* ... original content ... */ }
void karobube() { /* ... original content ... */ }
int karobubespielen() { /* ... original content ... */ return 0;}
void do_angesagt() { /* ... original content ... */ }
void spielphase() { /* ... original content ... */ }
int higher(c1, c2) int c1, c2; { /* ... original content ... */ return 0;}
void calc_result() { /* ... original content ... */ }
void get_next() { /* ... original content ... */ }
void save_list() { /* ... original content ... */ }
void setsum(clr) int clr; { /* ... original content ... */ }
void modsum(sm,gv,p,as,ae,ar,ad) int sm[3][3],gv[3][2],p,*as,*ae,*ar,*ad; { /* ... original content ... */ }
void read_opt_srpk(f) FILE* f; { /* ... original content ... */ }
void fill_st() { /* ... original content ... */ }
int maxnimm() { /* ... original content ... */ return 0;}
void do_next() { /* ... original content ... */ }
void calc_poss(s) int s; { /* ... original content ... */ }
void c_high(f,h) int f; int* h; { /* ... original content ... */ }
void calc_high(f,s) int f, s; { /* ... original content ... */ }
int zweihoechste(ci) int ci; { /* ... original content ... */ return 0;}
int ignorieren() { /* ... original content ... */ return 0;}
int genugdrin() { /* ... original content ... */ return 0;}
int gewinnstich(f) int f; { /* ... original content ... */ return 0;}
int uebernehmen(p,h,n) int p, h, n; { /* ... original content ... */ return 0;}
void schmieren() { /* ... original content ... */ }
int einstechen() { /* ... original content ... */ return 0;}
int niedrighoch(f) int f; { /* ... original content ... */ return 0;}
int ueberdoerfer() { /* ... original content ... */ return 0;}
int bubeausspielen() { /* ... original content ... */ return 0;}
int trumpfausspielen() { /* ... original content ... */ return 0;}
int hochausspielen() { /* ... original content ... */ return 0;}
void schenke() { /* ... original content ... */ }
int zehnblank(ci) int ci; { /* ... original content ... */ return 0;}
int fabwerfen() { /* ... original content ... */ return 0;}
void abwerfen() { /* ... original content ... */ }
int buttern() { /* ... original content ... */ return 0;}
int hatas() { /* ... original content ... */ return 0;}
int schnippeln(f) int f; { /* ... original content ... */ return 0;}
void nichtspitze() { /* ... original content ... */ }
int spitzefangen() { /* ... original content ... */ return 0;}
int restbeimir() { /* ... original content ... */ return 0;}
void m_bvsp() { /* ... original content ... */ } void m_bmsp() { /* ... original content ... */ }
void m_bhsp() { /* ... original content ... */ } void m_bvns() { /* ... original content ... */ }
void m_bmns() { /* ... original content ... */ } void m_bhns() { /* ... original content ... */ }
void m_bsp() { /* ... original content ... */ } void m_bns() { /* ... original content ... */ }
void make_best(s) int s; { /* ... original content ... */ }
void adjfb(s,v) int s, v; { /* ... original content ... */ }
void do_spielen() { /* ... original content ... */ }
void computer() { /* ... original content ... */ }

void play() {
  if (!resumebock || !playbock) { bockspiele = bockinc = ramschspiele = 0; }
  else if (playbock != 2) { ramschspiele = 0; }
  phase = GEBEN; UI_Event event;
  if (g_ui_context) { ui_clear_screen(g_ui_context, (UI_Color){230,230,230,255}); initscr(0,1); ui_present_screen(g_ui_context); }
  if (!no_serv) connect_serv();
  while (!quit) {
      if (ui_poll_event(g_ui_context, &event)) {
          if (event.type == UI_EVENT_QUIT) { quit = 1; break; }
          if (event.type == UI_EVENT_WINDOW_EXPOSED) { fprintf(stdout, "UI_EVENT_WINDOW_EXPOSED: Full redraw initiated.\n"); if (g_ui_context) { ui_clear_screen(g_ui_context, (UI_Color){230,230,230,255}); initscr(0,1); ui_present_screen(g_ui_context);}}
          if (event.type == UI_EVENT_KEY_DOWN) { fprintf(stdout, "UI_EVENT_KEY_DOWN: sym=%d, text='%s'\n", event.data.key.sym, event.data.key.text); }
          if (event.type == UI_EVENT_MOUSE_BUTTON_DOWN) { fprintf(stdout, "UI_EVENT_MOUSE_BUTTON_DOWN: x=%d y=%d button=%d\n", event.data.mouse_button.x, event.data.mouse_button.y, event.data.mouse_button.button); }
      }
      if (g_ui_context && !g_ui_context->is_dialog_active) { computer(); }
  }
}

int main(int argc, char* argv[]) {
  long t; theargc = argc; theargv = argv;
  g_ui_context = ui_initialize("XSkat (Abstracted UI)", 1024, 768);
  if (!g_ui_context) { fprintf(stderr, "Failed to initialize UI. Exiting.\n"); return 1; }
  if (g_ui_context->default_font_struct) {
      g_game_font = (UI_Font*)malloc(sizeof(UI_Font));
      if (g_game_font) { g_game_font->font_struct = g_ui_context->default_font_struct; g_game_font->display = g_ui_context->display; }
      else { fprintf(stderr, "Failed to allocate g_game_font wrapper.\n"); }
  }
  if (!g_game_font) {
      g_game_font = ui_load_font(g_ui_context, "fixed", 14);
      if (!g_game_font) { fprintf(stderr, "Failed to load game font 'fixed'. Text display will be affected.\n"); }
  }
  init_text(); read_list_stub(); read_opt_stub(); set_conames_stub();
  srand((unsigned int)time(&t)); ramsch = 1; force = 0; numsp = 1;
  for (int k=1; k<argc; k++) { if (!strcmp(argv[k],"-n")) numsp=0; else if (!strcmp(argv[k],"-1")) numsp=1; else if (!strcmp(argv[k],"-2")) numsp=2; else if (!strcmp(argv[k],"-3")) numsp=3; }
  play(); exitus(0); return 0;
}

void exitus(n) int n; {
  if (prot_on) fclose(prot); if (list_on) fclose(list);
  if (g_game_font && g_ui_context) {
      if (g_ui_context->default_font_struct && g_game_font->font_struct != g_ui_context->default_font_struct) { ui_free_font(g_ui_context, g_game_font); }
      else if (g_game_font->font_struct == g_ui_context->default_font_struct) { free(g_game_font); /* Was just a wrapper for the context's default font */ }
      else { ui_free_font(g_ui_context, g_game_font); /* Fallback: was a separately loaded font */ }
      g_game_font = NULL;
  }
  if (g_ui_context) { ui_cleanup(g_ui_context); g_ui_context = NULL; }
  exit(n);
}

void panic(s,a,b,c,d,e,f) char *s; int a,b,c,d,e,f; { fprintf(stderr,s,a,b,c,d,e,f); fprintf(stderr,"\n"); exitus(1); }
