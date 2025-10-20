
/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt

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
#include "application/file_manager.h"
#include "application/text.h"
#include "domain/utils.h"
#include "ui/xio.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================
 * FILE I/O AND CONFIGURATION MANAGEMENT
 * ======================================================================== */

int get_game() {
  static int opened;
  static FILE* f;
  char s[100], *p;
  int i, n, cpos[4], cmax[4], state, rep;
  long num;

  if (predef == 1) predef = 0;
  if (!game_file) return 0;
  if (!opened) {
    if (!strcmp(game_file, "-")) {
      game_file = const_cast<char*>("stdin");
      f         = stdin;
    } else {
      f = fopen(game_file, "r");
    }
    if (!f) {
      fprintf(stderr, "Can't open file %s\n", game_file);
      exitus(1);
    }
    opened = 1;
  }
  state = rep = n = 0;
  while (state != 4) {
    if (fscanf(f, " %99s", s) != 1) {
      if (!state) break;
      synerr(f, "");
      return 0;
    } else if (*s == '#') {
      do {
        fgets(s, 99, f);
      } while (s[strlen(s) - 1] != '\n' && s[0]);
    } else if (!strcmp(s, "random_seed")) {
      if (!state)
        state = 2;
      else {
        synerr(f, s);
        return 0;
      }
    } else if (!strcmp(s, "repeat")) {
      if (!state) {
        if (rep) break;
        rewind(f);
        rep = 1;
      } else {
        synerr(f, s);
        return 0;
      }
    } else {
      num = strtol(s, &p, 10);
      if (p != s + strlen(s)) {
        synerr(f, s);
        return 0;
      }
      switch (state) {
        case 0:
          cpos[0] = 30;
          cmax[0] = 2;
          cpos[1] = sager * 10;
          cmax[1] = 10;
          cpos[2] = geber * 10;
          cmax[2] = 10;
          cpos[3] = hoerer * 10;
          cmax[3] = 10;
          state   = 1;
        case 1:
          if (num < 0 || num > 3 || !cmax[num]) {
            synerr(f, s);
            return 0;
          }
          cards[cpos[num]] = n;
          cpos[num]++;
          cmax[num]--;
          n++;
          if (n == 32) {
            predef = 1;
            return 1;
          }
          break;
        case 2:
          predef = 2;
          setrnd(&seed[0], savseed = num);
          state = 3;
          break;
        case 3:
          gamenr = num;
          while (num-- > 0) {
            for (i = 0; i < 32; i++) rndval(&seed[0], 0);
          }
          if (fscanf(f, " %d", &i) == 1) {
            if (i >= 1 && i <= 3) {
              geber  = i - 1;
              hoerer = ausspl = left(geber);
              sager           = right(geber);
            }
          }
          if (fscanf(f, " %99s", s) == 1) {
            if (toupper(*s) == 'L')
              rotateby = -1;
            else if (toupper(*s) == 'R')
              rotateby = 1;
          }
          state = 4;
          break;
      }
    }
  }
  fclose(f);
  game_file = 0;
  return 0;
}

void read_opt_srpk(FILE* f) {
  int i, v, va[3];

  if (fscanf(f, "s %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (!stgset[i]) {
        if (va[i] < -4)
          va[i] = -4;
        else if (va[i] > 0)
          va[i] = 0;
        strateg[i] = va[i];
      }
    }
  }
  if (fscanf(f, "r %d\n", &v) == 1) {
    if (!ramschset) {
      if (v < 0)
        v = 0;
      else if (v > 2)
        v = 2;
      playramsch = v;
    }
  }
  if (fscanf(f, "p %d\n", &v) == 1) {
    if (!sramschset) {
      playsramsch = !!v;
    }
  }
  if (fscanf(f, "k %d\n", &v) == 1) {
    if (!kontraset) {
      if (v < 0)
        v = 0;
      else if (v > 2)
        v = 2;
      playkontra = v;
    }
  }
}

void read_opt() {
  FILE* f;
  int v, va[3], i;
  char buf[40];

  dlhintseen = 1;
  if (!opt_file) return;
  dlhintseen = 0;
  f          = fopen(opt_file, "r");
  if (!f) {
    firstgame = 1;
    return;
  }
  read_opt_srpk(f);
  if (fscanf(f, "b %d\n", &v) == 1) {
    if (!bockset) {
      if (v < 0)
        v = 0;
      else if (v > 2)
        v = 2;
      playbock = v;
    }
  }
  if (fscanf(f, "e %d\n", &v) == 1) {
    if (!bockeventsset) {
      bockevents = v;
    }
  }
  if (fscanf(f, "c %d\n", &v) == 1) {
    if (!resumebockset) {
      resumebock = !!v;
    }
  }
  if (fscanf(f, "d %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !downupset[i]) {
        sort1[i] = !!va[i];
      }
    }
  }
  if (fscanf(f, "a %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !altseqset[i]) {
        alternate[i] = !!va[i];
      }
    }
  }
  if (fscanf(f, "t %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !tdelayset[i]) {
        if (va[i] < 0)
          va[i] = 7;
        else if (va[i] > 101)
          va[i] = 101;
        nimmstich[i][0] = va[i];
      }
    }
  }
  if (fscanf(f, "l %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !alistset[i]) {
        if (va[i] < 0)
          va[i] = 0;
        else if (va[i] > 2)
          va[i] = 2;
        alist[i] = va[i];
      }
    }
  }
  if (fscanf(f, "m %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !mbuttonset[i]) {
        if (va[i] < 0 || va[i] > 5) va[i] = 0;
        mbutton[i] = va[i];
      }
    }
  }
  if (fscanf(f, "s %d\n", &v) == 1) {
    if (!spitzezaehltset) {
      spitzezaehlt = v;
    }
  }
  if (fscanf(f, "r %d\n", &v) == 1) {
    if (!revolutionset) {
      revolution = !!v;
    }
  }
  if (fscanf(f, "k %d\n", &v) == 1) {
    if (!klopfenset) {
      klopfen = !!v;
    }
  }
  if (fscanf(f, "s %d\n", &v) == 1) {
    if (!schenkenset) {
      schenken = !!v;
    }
  }
  if (fscanf(f, "f %d\n", &v) == 1) {
    if (!fastdealset) {
      fastdeal = !!v;
    }
  }
  if (fscanf(f, "h %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !hintsset[i]) {
        hints[i] = !!va[i];
      }
    }
  }
  if (fscanf(f, "b %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !blattset[i]) {
        if (va[i] < 0 || va[i] > 3) va[i] = 0;
        blatt[i] = va[i];
      }
    }
  }
  if (fscanf(f, "l %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !langset[i]) {
        if (va[i] < 0 || va[i] >= NUM_LANG) va[i] = 0;
        lang[i] = va[i];
      }
    }
  }
  if (fscanf(f, "a %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !abkuerzset[i]) {
        if (va[i] < 0 || va[i] > 2) va[i] = 1;
        abkuerz[i] = va[i];
      }
    }
  }
  if (fscanf(f, "o %d\n", &v) == 1) {
    if (!oldrulesset) {
      oldrules = !!v;
    }
  }
  if (fscanf(f, "k %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !keyboardset[i]) {
        if (va[i] < 0 || va[i] > 2) va[i] = 1;
        keyboard[i] = va[i];
      }
    }
  }
  if (fscanf(f, "b %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !briefmsgset[i]) {
        briefmsg[i] = !!va[i];
      }
    }
  }
  if (fscanf(f, "l %d %d %d\n", &va[0], &va[1], &va[2]) == 3) {
    for (i = 0; i < 3; i++) {
      if (useoptfile[i] && !trickl2rset[i]) {
        trickl2r[i] = !!va[i];
      }
    }
  }
  if (fscanf(f, "s %d\n", &v) == 1) {
    if (!rskatloserset) {
      rskatloser = !!v;
    }
  }
  if (fscanf(f, "d %d\n", &v) == 1) {
    dlhintseen = 1;
  }
  fscanf(f, "l %35s %35s %35s\n", lanip[0], lanip[1], lanip[2]);
  fscanf(f, "i %d %d\n", &laninvite[0], &laninvite[1]);
  if (fscanf(f, "h %35s\n", buf) == 1) {
    if (!irc_hostset) {
      strcpy(irc_hostname, buf);
    }
  }
  fscanf(f, "a %9s %9s\n", usrname[0], usrname[1]);
  fscanf(f, "a %9s %9s\n", conames[0][0], conames[0][1]);
  fscanf(f, "a %9s %9s\n", conames[1][0], conames[1][1]);
  fclose(f);
}

void save_opt() {
  FILE* f;

  if (!opt_file) return;
  f = fopen(opt_file, "w");
  if (!f) {
    fprintf(stderr, "Can't write file %s\n", opt_file);
    return;
  }
  fprintf(f, "s %d %d %d\n", strateg[0], strateg[1], strateg[2]);
  fprintf(f, "r %d\n", playramsch);
  fprintf(f, "p %d\n", playsramsch);
  fprintf(f, "k %d\n", playkontra);
  fprintf(f, "b %d\n", playbock);
  fprintf(f, "e %d\n", bockevents);
  fprintf(f, "c %d\n", resumebock);
  fprintf(f, "d %d %d %d\n", sort1[0], sort1[1], sort1[2]);
  fprintf(f, "a %d %d %d\n", alternate[0], alternate[1], alternate[2]);
  fprintf(f, "t %d %d %d\n", nimmstich[0][0], nimmstich[1][0], nimmstich[2][0]);
  fprintf(f, "l %d %d %d\n", alist[0], alist[1], alist[2]);
  fprintf(f, "m %d %d %d\n", mbutton[0], mbutton[1], mbutton[2]);
  fprintf(f, "s %d\n", spitzezaehlt);
  fprintf(f, "r %d\n", revolution);
  fprintf(f, "k %d\n", klopfen);
  fprintf(f, "s %d\n", schenken);
  fprintf(f, "f %d\n", fastdeal);
  fprintf(f, "h %d %d %d\n", hints[0], hints[1], hints[2]);
  fprintf(f, "b %d %d %d\n", blatt[0], blatt[1], blatt[2]);
  fprintf(f, "l %d %d %d\n", lang[0], lang[1], lang[2]);
  fprintf(f, "a %d %d %d\n", abkuerz[0], abkuerz[1], abkuerz[2]);
  fprintf(f, "o %d\n", oldrules);
  fprintf(f, "k %d %d %d\n", keyboard[0], keyboard[1], keyboard[2]);
  fprintf(f, "b %d %d %d\n", briefmsg[0], briefmsg[1], briefmsg[2]);
  fprintf(f, "l %d %d %d\n", trickl2r[0], trickl2r[1], trickl2r[2]);
  fprintf(f, "s %d\n", rskatloser);
  fprintf(f, "d 1\n");
  fprintf(f, "l %s %s %s\n", lanip[0], lanip[1], lanip[2]);
  fprintf(f, "i %d %d\n", laninvite[0], laninvite[1]);
  fprintf(f, "h %s\n", irc_hostname);
  fprintf(f, "a %s %s\n", usrname[0], usrname[1]);
  fprintf(f, "a %s %s\n", conames[0][0], conames[0][1]);
  fprintf(f, "a %s %s\n", conames[1][0], conames[1][1]);
  fclose(f);
}

void read_list() {
  FILE* f;
  int c, i, j;

  if (!list_file) return;
  f = fopen(list_file, "r");
  if (!f) return;
  splstp = 0;
  if (fscanf(f, "%d %d %d\n", &splsum[0][0], &splsum[1][0], &splsum[2][0]) !=
      3) {
    splsum[0][0] = splsum[1][0] = splsum[2][0] = 0;
    fclose(f);
    return;
  }
  if (fscanf(f, "a %d %d %d\n", &splsum[0][1], &splsum[1][1], &splsum[2][1]) !=
      3) {
    splsum[0][1] = splsum[1][1] = splsum[2][1] = 0;
  }
  if (fscanf(f, "t %d %d %d\n", &splsum[0][2], &splsum[1][2], &splsum[2][2]) !=
      3) {
    splsum[0][2] = splsum[1][2] = splsum[2][2] = 0;
  }
  read_opt_srpk(f);
  if (fscanf(f, "b %d %d %d\n", &bockspiele, &bockinc, &ramschspiele) != 3) {
    bockspiele = bockinc = ramschspiele = 0;
  }
  if (fscanf(f, "g %d %d %d\n", &sgewoverl[0][0], &sgewoverl[1][0],
             &sgewoverl[2][0]) != 3) {
    sgewoverl[0][0] = sgewoverl[1][0] = sgewoverl[2][0] = 0;
  }
  if (fscanf(f, "v %d %d %d\n", &sgewoverl[0][1], &sgewoverl[1][1],
             &sgewoverl[2][1]) != 3) {
    sgewoverl[0][1] = sgewoverl[1][1] = sgewoverl[2][1] = 0;
  }
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      sum[i][j] = splsum[i][j];
    }
    for (j = 0; j < 2; j++) {
      cgewoverl[i][j] = sgewoverl[i][j];
    }
  }
  do {
    if (fscanf(f, "%d\n", &i) == 1) {
      splist[splstp].s = i / 10000;
      splist[splstp].r = (i - splist[splstp].s * 10000) / 4000;
      splist[splstp].d =
          (i - splist[splstp].s * 10000 - splist[splstp].r * 4000) / 2000;
      splist[splstp].e = i % 2000 >> 1;
      splist[splstp].g = i & 1;
      modsum(sum, cgewoverl, splstp, (int*)0, (int*)0, (int*)0, (int*)0);
      splstp++;
    } else if (fscanf(f, "e %d %d %d %d %d\n", &splist[splstp].s,
                      &splist[splstp].r, &splist[splstp].d, &splist[splstp].e,
                      &splist[splstp].g) == 5) {
      modsum(sum, cgewoverl, splstp, (int*)0, (int*)0, (int*)0, (int*)0);
      splstp++;
    } else {
      while ((c = getc(f)) != EOF && c != '\n');
    }
  } while (!feof(f) && splstp < 360);
  fclose(f);
}

void save_list() {
  FILE* f;
  int i;

  if (!list_file) return;
  f = fopen(list_file, "w");
  if (!f) {
    fprintf(stderr, "Can't write file %s\n", list_file);
    return;
  }
  fprintf(f, "%d %d %d\n", splsum[0][0], splsum[1][0], splsum[2][0]);
  fprintf(f, "a %d %d %d\n", splsum[0][1], splsum[1][1], splsum[2][1]);
  fprintf(f, "t %d %d %d\n", splsum[0][2], splsum[1][2], splsum[2][2]);
  fprintf(f, "b %d %d %d\n", bockspiele, bockinc, ramschspiele);
  fprintf(f, "g %d %d %d\n", sgewoverl[0][0], sgewoverl[1][0], sgewoverl[2][0]);
  fprintf(f, "v %d %d %d\n", sgewoverl[0][1], sgewoverl[1][1], sgewoverl[2][1]);
  for (i = 0; i < splstp; i++) {
    fprintf(f, "e %d %d %d %d %d\n", splist[i].s, splist[i].r, splist[i].d,
            splist[i].e, splist[i].g);
  }
  fclose(f);
}

void update_list() {
  int i;

  if (splstp >= 360) {
    for (i = 0; i < 12; i++) {
      modsum(splsum, sgewoverl, i, (int*)0, (int*)0, (int*)0, (int*)0);
    }
    for (i = 12; i < splstp; i++) splist[i - 12] = splist[i];
    splstp -= 12;
  }
  splist[splstp].s = spieler;
  splist[splstp].r = trumpf == 5;
  splist[splstp].d = trumpf == 5 && stsum == 120 && spgew;
  splist[splstp].e = spwert;
  splist[splstp].g = spgew;
  memcpy((void*)prevsum, (void*)sum, sizeof(sum));
  modsum(sum, cgewoverl, splstp, (int*)0, (int*)0, (int*)0, (int*)0);
  splstp++;
}

void set_prot() {
  prot2.stichgem = stich - 1;
  prot2.spieler  = spieler;
  prot2.trumpf   = trumpf;
  prot2.gereizt  = reizp < 0 || ramschspiele ? 0 : reizw[reizp];
  prot2.gewonn   = spgew;
  prot2.augen    = stsum;
  prot2.handsp   = handsp;
  prot2.ehsso    = revolang  ? handsp ? 1 : 0
                   : ouveang ? trumpf == -1 && handsp ? 5 : 4
                   : schwang ? 3
                   : schnang ? 2
                   : handsp  ? 1
                             : 0;
  prot2.predef   = predef;
  if (trumpf != 5) prot2.sramsch = 0;
  prot2.savseed    = savseed;
  prot2.gamenr     = gamenr - 1;
  prot2.rotateby   = rotateby;
  prot2.spitze     = spitzeang;
  prot2.revolution = revolang;
  prot2.schenken   = schenkstufe;
}
