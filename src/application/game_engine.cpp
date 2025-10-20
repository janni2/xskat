/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt

    Application Layer - Game Engine
    Core game coordination and flow management

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.

    Redistribution of modified versions is permitted
    provided that the following conditions are met:
    1. All copyright & permission notices are preserved.
    2.a) Only changes required for packaging or porting are made.
      or
    2.b) It is clearly stated who last changed the program.
         The program is renamed or
         the version number is of the form x.y.z,
         where x.y is the version of the original program
         and z is an arbitrary suffix.
*/

#include "skat.h"
#include "game_interfaces.h"
#include "application/game_engine.h"
#include "application/file_manager.h"
#include "application/ai_engine.h"
#include "domain/skat_constants.h"

/* ========================================================================
 * GAME PHASE HANDLERS
 * ======================================================================== */

void do_geben() {
  int sn, i;
  static int f;

  sort2[0] = sort2[1] = sort2[2] = 0;
  prot2.verdopp[0] = prot2.verdopp[1] = prot2.verdopp[2] = 0;
  schnang = schwang = ouveang = spitzeang = revolang = 0;
  ndichtw                                            = 0;
  hintcard[0]                                        = -1;
  hintcard[1]                                        = -1;
  for (sn = 0; sn < numsp; sn++) calc_desk(sn);
  if (!wieder) {
    if (ramschspiele) {
      if (trumpf == GRAND_GAME)
        geber = right(geber);
      else
        ramschspiele--;
    } else if (bockspiele) {
      bockspiele--;
      if (bockspiele % NUM_PLAYERS == 0 && playbock == 2) {
        ramschspiele = NUM_PLAYERS;
      }
    }
    bockspiele += NUM_PLAYERS * bockinc;
    geber = left(geber);
  } else if (!vorhandwn) {
    geber = left(geber + wieder);
  }
  bockinc = 0;
  trumpf  = -1;
  hoerer = ausspl = left(geber);
  sager           = right(geber);
  mischen();
  setcurs(0);
  givecard(hoerer, 0);
  givecard(sager, 0);
  givecard(geber, 0);
  givecard(-1, 0);
  givecard(hoerer, 1);
  givecard(sager, 1);
  givecard(geber, 1);
  givecard(hoerer, 2);
  givecard(sager, 2);
  givecard(geber, 2);
  for (sn = 0; sn < numsp; sn++) initscr(sn, 1);
  for (i = 0; i < NUM_PLAYERS; i++) {
    lastmsaho[i] = 0;
    sagte18[i]   = 0;
  }
  kontrastufe = 0;
  schenkstufe = 0;
  saho        = 1;
  reizp       = 0;
  clear_info();
  if (!dlhintseen) {
    di_copyr(0);
  } else if (firstgame) {
    di_options(-1);
  } else if (!f &&
             (sum[0][0] || sum[0][1] || sum[0][2] || sum[1][0] || sum[1][1] ||
              sum[1][2] || sum[2][0] || sum[2][1] || sum[2][2])) {
    di_delliste();
  }
  f = 1;
  if (ramschspiele) {
    phase = ANSAGEN;
    di_grandhand(hoerer);
  } else if (playramsch > 1) {
    init_ramsch();
  } else {
    putmark(hoerer);
    put_box(sager);
    put_box(hoerer);
    for (sn = numsp; sn < NUM_PLAYERS; sn++) calc_rw(sn);
    phase = REIZEN;
  }
}

void do_sagen(int s, int w) {
  char str[4];
  tx_typ tt;
  int ln;

  for (ln = 0; ln < NUM_LANG; ln++) {
    tt.t[ln] = str;
  }
  sprintf(str, "%d", w);
  b_text(s, &tt);
  inv_box(s, 0, 1);
  stdwait();
  inv_box(s, 0, 0);
  sagte18[s] = 1;
}

void do_passen(int s) {
  b_text(s, &textarr[TX_PASSE]);
  inv_box(s, 1, 1);
  stdwait();
  inv_box(s, 1, 0);
  rem_box(s);
}

void do_akzept(int s) {
  tx_typ tt;
  int ln;

  for (ln = 0; ln < NUM_LANG; ln++) {
    tt.t[ln] = " ";
  }
  b_text(s, &textarr[TX_JA]);
  inv_box(s, 0, 1);
  stdwait();
  inv_box(s, 0, 0);
  b_text(s, &tt);
  sagte18[s] = 1;
}

void do_msagen(int sn, int w) {
  char str[4];

  if (lastmsaho[sn] == w) return;
  lastmsaho[sn] = w;
  sprintf(str, "%d", w);
  do_msaho(sn, str);
}

void do_mhoeren(int sn) {
  if (lastmsaho[sn] == 1) return;
  lastmsaho[sn] = 1;
  do_msaho(sn, textarr[TX_JA].t[lang[sn]]);
}

void do_entsch() {
  int rw;

  rw = reizw[reizp];
  if (saho) {
    if (maxrw[sager] >= rw || (maxrw[sager] == 17 && rw == 18)) {
      do_sagen(sager, rw);
      saho = 0;
      if (sager == hoerer) {
        spieler = sager;
        do_handspiel();
      }
    } else {
      do_passen(sager);
      if (sager == geber || sager == hoerer) {
        if (sager == hoerer) {
          reizp--;
          do_handspiel();
        } else {
          if (reizp) {
            spieler = hoerer;
            reizp--;
            do_handspiel();
          } else {
            rem_box(sager);
            sager = hoerer;
          }
        }
      } else {
        rem_box(sager);
        sager = geber;
        put_box(sager);
      }
    }
  } else {
    if (maxrw[hoerer] >= rw) {
      do_akzept(hoerer);
      reizp++;
      saho = 1;
    } else {
      do_passen(hoerer);
      if (sager == geber) {
        spieler = sager;
        do_handspiel();
      } else {
        rem_box(hoerer);
        rem_box(sager);
        hoerer = sager;
        sager  = geber;
        reizp++;
        saho = 1;
        put_box(hoerer);
        put_box(sager);
      }
    }
  }
}

void do_reizen() {
  while (phase == REIZEN &&
         ((iscomp(sager) && saho) || (iscomp(hoerer) && !saho))) {
    do_entsch();
  }
  if (phase == REIZEN) {
    if (saho)
      do_msagen(sager, reizw[reizp]);
    else
      do_mhoeren(hoerer);
  }
}

void do_grandhand(int sn) {
  handsp  = 1;
  trumpf  = GRAND_GAME;
  reizp   = 0;
  spieler = sn;
  do_handspiel();
}

void do_handspiel() {
  int i, sn;

  prot2.anspiel[0] = ausspl;
  prot2.gemacht[0] = -1;
  if (reizp < 0 && !ramschspiele) {
    if (playramsch > 0) {
      init_ramsch();
      return;
    }
    stich = 1;
    fill_st();
    trumpf = GRAND_GAME;
    set_prot();
    save_skat(1);
    prot1  = prot2;
    spwert = 0;
    update_list();
    save_list();
    if (logging) di_proto(0, 1, 1);
    splres = 1;
    nextgame();
    phase = WEITER;
    for (sn = 0; sn < numsp; sn++) {
      draw_skat(sn);
    }
    if (numsp == 1)
      di_wiederweiter(0);
    else
      di_weiter(1);
    return;
  }
  info_reiz();
  drkcd = 0;
  if (!ramschspiele) handsp = 0;
  stsum = 0;
  vmh   = 0;
  gedr  = 0;
  for (i = 0; i < CARDS_PER_PLAYER; i++) spcards[i] = cards[spieler * CARDS_PER_PLAYER + i];
  save_skat(0);
  spcards[CARDS_PER_PLAYER] = cards[SKAT_OFFSET];
  spcards[CARDS_PER_PLAYER + 1] = cards[SKAT_OFFSET + 1];
  rem_box(sager);
  rem_box(hoerer);
  if (!iscomp(spieler) && !ramschspiele) {
    phase = HANDSPIEL;
    di_hand();
  } else
    do_handok();
}

void do_druecken() {
  draw_skat(spieler);
  if (hintcard[0] == -1) {
    gedr = 0;
    calc_drueck();
    trumpf = -1;
  }
  if (hints[spieler]) {
    show_hint(spieler, 0, 1);
    show_hint(spieler, 1, 1);
  }
  put_fbox(spieler, TX_DRUECKEN);
  drbut             = spieler + 1;
  phase             = DRUECKEN;
  stsum             = 0;
  gespcd[cards[SKAT_OFFSET]] = 0;
  gespcd[cards[SKAT_OFFSET + 1]] = 0;
  gedr = handsp = 0;
}

void do_handok() {
  if (iscomp(spieler) || handsp) {
    home_skat();
    if (iscomp(spieler) && !handsp) calc_drueck();
    stsum = cardw[cards[SKAT_OFFSET] & CARD_RANK_MASK] + cardw[cards[SKAT_OFFSET + 1] & CARD_RANK_MASK];
    save_skat(1);
  }
  if (!iscomp(spieler) && !handsp)
    do_druecken();
  else
    do_ansagen();
}

void do_ansagen() {
  int i, c, bb;

  phase = ANSAGEN;
  bb = kannspitze = 0;
  for (i = 0; i < (handsp ? CARDS_PER_PLAYER : CARDS_IN_INITIAL_DEAL); i++) {
    c = i >= CARDS_PER_PLAYER ? prot2.skat[1][i - CARDS_PER_PLAYER] : cards[spieler * CARDS_PER_PLAYER + i];
    if ((c & CARD_RANK_MASK) == BUBE) bb++;
    if (i < CARDS_PER_PLAYER) {
      if ((c & CARD_RANK_MASK) == SIEBEN) {
        kannspitze = 1;
        break;
      }
      if (c == BUBE) {
        kannspitze = 2;
      }
    }
  }
  if (kannspitze == 2) {
    kannspitze = bb != NUM_SUITS;
  }
  if (!iscomp(spieler) && !ramschspiele) {
    di_spiel();
  } else {
    remmark(1);
    di_ansage();
  }
}

void do_angesagt() {
  if (!iscomp(spieler)) {
    remmark(1);
  }
  stich    = 1;
  schwz    = 1;
  nullv    = 0;
  spitzeok = 0;
  info_spiel();
  sort2[0] = sort2[1] = sort2[2] = trumpf == -1;
  if (revolang) revolutiondist();
  if (revolang && numsp && (numsp > 1 || iscomp(spieler)))
    revolutionscr();
  else
    spielphase();
}

void spielphase() {
  int sn, c, i;

  phase      = SPIELEN;
  sptruempfe = 0;
  for (i = 0; i < CARDS_PER_PLAYER; i++) {
    c = cards[spieler * CARDS_PER_PLAYER + i];
    if ((c & CARD_RANK_MASK) == BUBE || c >> CARD_SUIT_SHIFT == trumpf) sptruempfe++;
  }
  karobube();
  if (ouveang) {
    for (sn = 0; sn < numsp; sn++) {
      di_info(sn, -2);
      calc_desk(sn);
    }
  }
  for (sn = numsp; sn < NUM_PLAYERS; sn++) {
    sort1[sn]     = sort1[0];
    sort2[sn]     = trumpf == -1;
    alternate[sn] = alternate[0];
    sort(sn);
  }
  for (sn = 0; sn < numsp; sn++) initscr(sn, 1);
}

void get_next() {
  int s;

  prot2.anspiel[stich - 1]               = ausspl;
  prot2.stiche[stich - 1][ausspl]        = stcd[0];
  prot2.stiche[stich - 1][left(ausspl)]  = stcd[1];
  prot2.stiche[stich - 1][right(ausspl)] = stcd[2];
  if (trumpf == -1) null_stich();
  if (higher(stcd[0], stcd[1])) {
    if (higher(stcd[0], stcd[2]))
      s = 0;
    else
      s = 2;
  } else {
    if (higher(stcd[1], stcd[2]))
      s = 1;
    else
      s = 2;
  }
  ausspl                   = (ausspl + s) % NUM_PLAYERS;
  prot2.gemacht[stich - 1] = ausspl;
  if (spitzeang && stich == CARDS_PER_PLAYER && ausspl == spieler &&
      stcd[s] == (trumpf == GRAND_GAME ? BUBE : SIEBEN | trumpf << CARD_SUIT_SHIFT)) {
    spitzeok = 1;
  }
  if (trumpf == RAMSCH_GAME) {
    ramsch_stich();
    return;
  }
  if (stich == 1 && !handsp) {
    astsum += stsum;
  }
  if (spieler == ausspl) {
    if (butternok == 1) butternok = 2;
    stsum += cardw[stcd[0] & CARD_RANK_MASK] + cardw[stcd[1] & CARD_RANK_MASK] + cardw[stcd[2] & CARD_RANK_MASK];
    astsum += cardw[stcd[0] & CARD_RANK_MASK] + cardw[stcd[1] & CARD_RANK_MASK] + cardw[stcd[2] & CARD_RANK_MASK];
    nullv = 1;
  } else {
    if (butternok != 2) butternok = 0;
    gstsum += cardw[stcd[0] & CARD_RANK_MASK] + cardw[stcd[1] & CARD_RANK_MASK] + cardw[stcd[2] & CARD_RANK_MASK];
    schwz = 0;
  }
}

void fill_st() {
  int i, j, s, c, sc;

  for (s = 0; s < NUM_PLAYERS; s++) {
    if (vmh >= 1 && s == ausspl) {
      sc = stcd[0];
    } else if (vmh == 2 && s == left(ausspl)) {
      sc = stcd[1];
    } else {
      sc = -1;
    }
    i = stich - 1;
    for (j = 0; j < CARDS_PER_PLAYER; j++) {
      c = cards[CARDS_PER_PLAYER * s + j];
      if (c < 0 && sc >= 0) {
        c  = sc;
        sc = -1;
      }
      if (c >= 0) prot2.stiche[i++][s] = c;
    }
  }
}

int maxnimm() {
  int i, m;

  m = nimmstich[0][0];
  for (i = 1; i < numsp; i++) {
    if (nimmstich[i][0] > m) m = nimmstich[i][0];
  }
  return m;
}

void next_stich() {
  int nd;

  if (maxnimm() < 101) {
    waitt(maxnimm() * 100, 2);
  }
  info_stich(0, stcd[0]);
  info_stich(1, stcd[1]);
  info_stich(2, stcd[2]);
  nimm_stich();
  vmh = 0;
  stich++;
  nd = 0;
  if (stich == TOTAL_TRICKS ||
      (trumpf == -1 &&
       (nullv || (!ndichtw && stich < CARDS_PER_PLAYER &&
                  (nd = null_dicht(spieler, handsp, &prot2.skat[1][0], (int*)0,
                                   (int*)0, (int*)0)))))) {
    if (nd)
      di_dicht();
    else
      finishgame();
  }
}

void finishgame() {
  int i, s;

  if (stich < TOTAL_TRICKS) {
    if (trumpf < 0 || trumpf > GRAND_GAME || (schenkstufe && stich == 1))
      fill_st();
    else {
      while (stich != TOTAL_TRICKS) {
        s = (ausspl + vmh) % NUM_PLAYERS;
        calc_poss(s);
        make_best(s);
        i         = possi[playcd];
        stcd[vmh] = cards[i];
        cards[i]  = -1;
        if (vmh == 2) {
          get_next();
          vmh = 0;
          stich++;
        } else
          vmh++;
      }
    }
  }
  calc_result();
  set_prot();
  prot1 = prot2;
  update_list();
  if (playbock) bockinc = check_bockevents();
  save_list();
  if (logging) di_proto(0, 1, 1);
  splres = 1;
  clr_desk(0);
  phase = RESULT;
  di_result(bockinc);
  nextgame();
}

void do_next() {
  int sn;

  if (vmh == 2) {
    get_next();
    for (sn = 0; sn < numsp; sn++) {
      if (nimmstich[sn][0] >= 101) {
        nimmstich[sn][1] = 1;
        phase            = NIMMSTICH;
      }
    }
    if (phase == NIMMSTICH) return;
    next_stich();
  } else
    vmh++;
}

void nextgame() {
  if (numgames) {
    phase = GEBEN;
    numgames--;
    if (!numgames) {
      printf("%d ", sum[0][alist[0]]);
      printf("%d ", sum[1][alist[0]]);
      printf("%d\n", sum[2][alist[0]]);
      quit = 1;
    }
  }
}

void save_skat(int i) {
  if (lower(cards[SKAT_OFFSET + 1], cards[SKAT_OFFSET], 0)) {
    swap(&cards[SKAT_OFFSET + 1], &cards[SKAT_OFFSET]);
  }
  prot2.skat[i][0] = cards[SKAT_OFFSET];
  prot2.skat[i][1] = cards[SKAT_OFFSET + 1];
}

int check_bockevents() {
  int e, m, i, ns, s;

  e = 0;
  if (bockevents & BOCK_BEI_60) {
    if (!spgew && stsum == GAME_WIN_POINTS && trumpf >= 0 && trumpf <= GRAND_GAME) e++;
  }
  if (bockevents & BOCK_BEI_GRANDHAND) {
    if (spgew && trumpf == GRAND_GAME && handsp) e++;
  }
  m = 0;
  if (bockevents & BOCK_BEI_KONTRA) {
    if (!spgew && kontrastufe) e++, m = 1;
  }
  if (!m && bockevents & BOCK_BEI_RE) {
    if (kontrastufe == 2) e++;
  }
  for (i = 0; i < NUM_PLAYERS; i++) {
    ns = sum[i][alist[0]];
    s  = ns < 0 ? -ns : ns;
    if (ns != prevsum[i][alist[0]] &&
        ((bockevents & BOCK_BEI_NNN && s % 10 == s / 10 % 10 &&
          s % 10 == s / 100 % 10) ||
         (bockevents & BOCK_BEI_N00 && s % 100 == 0)))
      e++;
  }
  m = 0;
  if (bockevents & BOCK_BEI_72) {
    if (nspwert >= 72) e++, m = 1;
  }
  if (!m && bockevents & BOCK_BEI_96) {
    if (nspwert >= 96) e++;
  }
  return e;
}

void setsum(int clr) {
  int i, j;

  splstp = 0;
  for (i = 0; i < NUM_PLAYERS; i++) {
    splfirst[i] = 0;
    for (j = 0; j < NUM_PLAYERS; j++) {
      if (clr) {
        sum[i][j] = 0;
        if (j < 2) {
          cgewoverl[i][j] = 0;
        }
      }
      splsum[i][j] = sum[i][j];
      if (j < 2) {
        sgewoverl[i][j] = cgewoverl[i][j];
      }
    }
  }
}

void modsum(int sm[3][3], int gv[3][2], int p, int *as, int *ae, int *ar, int *ad) {
  int s, e, r, d;

  s = splist[p].s;
  r = splist[p].r;
  d = splist[p].d;
  e = splist[p].e;
  if (!splist[p].g) e = -e;
  if (e <= 0 || !r || d) {
    sm[s][0] += e;
    sm[s][2] += e;
    if (e) gv[s][e < 0]++;
  }
  if (e < 0) {
    sm[s][1] -= e;
    if (!r) {
      sm[s][2] -= 50;
      sm[left(s)][2] += 40;
      sm[right(s)][2] += 40;
    }
  } else {
    if (r && !d) {
      sm[left(s)][0] -= e;
      sm[right(s)][0] -= e;
      sm[left(s)][2] -= e;
      sm[right(s)][2] -= e;
      if (e) {
        gv[left(s)][1]++;
        gv[right(s)][1]++;
      }
    }
    sm[left(s)][1] += e;
    sm[right(s)][1] += e;
    if (!r && e) {
      sm[s][2] += 50;
    }
  }
  if (as) *as = s;
  if (ae) *ae = e;
  if (ar) *ar = r;
  if (ad) *ad = d;
}

/* End of Application Layer - Game Engine */
