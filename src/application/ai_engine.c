/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2004  Gunter Gerhardt

    Application Layer - AI Engine

    Computer player logic and decision making

    This program is free software; you can redistribute it freely.
    Use it at your own risk; there is NO WARRANTY.
*/

#include "skat.h"
#include "application/ai_engine.h"
#include "game_interfaces.h"
#include "core_utils.h"

/* ========================================================================
 * COMPUTER AI AND STRATEGY FUNCTIONS
 * ======================================================================== */

int ignorieren() {
  int mi, fb, i, ih, k[8];

  mi = right(ausspl);
  fb = stcd[0] >> 3;
  if ((stcd[0] & 7) == BUBE || fb == trumpf || cardw[stcd[0] & 7] ||
      hatnfb[mi][fb] == 1)
    return 0;
  ih = 0;
  for (i = 0; i < 8; i++) k[i] = 0;
  for (i = 0; i < possc; i++) {
    if (cards[possi[i]] >> 3 == fb) {
      ih++;
      k[cards[possi[i]] & 7] = 1;
    }
  }
  k[BUBE] = k[NEUN];
  k[NEUN] = k[ACHT];
  k[ACHT] = k[SIEBEN];
  if (ih >= 2) {
    for (i = AS; i <= NEUN && !k[i]; i++) {
      if (gespcd[fb << 3 | i] != 2) return 0;
    }
    for (i++; i <= ACHT && !k[i]; i++) {
      if (gespcd[fb << 3 | i] != 2) break;
    }
    if (k[i]) return 0;
  }
  if (stich > 7) {
    for (i = 0; i < possc; i++) {
      if (cards[possi[i]] >> 3 == fb && (cards[possi[i]] & 7) != BUBE) {
        if (!higher(stcd[0], cards[possi[i]])) return 0;
      }
    }
  }
  return ih < 3;
}

int genugdrin() {
  return (stcd[0] >> 3 == cards[possi[0]] >> 3 &&
          (cards[possi[0]] & 7) != BUBE) ||
         (trumpf != 4 && cardw[stcd[0] & 7] + cardw[stcd[1] & 7] > 0) ||
         cardw[stcd[0] & 7] + cardw[stcd[1] & 7] > 3 + rnd(1);
}

int gewinnstich(f)
int f;
{
  int i, p, s, g, ci, sf, su;

  s  = f ? astsum : gstsum;
  sf = 0;
  if (f) {
    if (schnang || spitzeang || stich < 6 || s > 60) return 0;
  } else {
    if (s > 59) return 0;
    if (s < 30) {
      su = cardw[prot2.skat[0][0] & 7] + cardw[prot2.skat[0][1] & 7] +
           cardw[stcd[0] & 7] + cardw[stcd[1] & 7];
      for (i = 0; i < 30; i++) {
        if (cards[i] >= 0) su += cardw[cards[i] & 7];
      }
      if (su + s < 60) sf = 1;
    }
  }
  p = !higher(stcd[0], stcd[1]);
  g = !f && (spieler == ausspl) ^ !p;
  for (i = 0; i < possc; i++) {
    ci = cards[possi[i]];
    if (!higher(stcd[p], ci) || g) {
      if (s + cardw[ci & 7] + cardw[stcd[0] & 7] + cardw[stcd[1] & 7] >
          59 + f) {
        playcd = i;
        return 1;
      }
      if (sf &&
          s + cardw[ci & 7] + cardw[stcd[0] & 7] + cardw[stcd[1] & 7] > 30) {
        playcd = i;
        return 1;
      }
    }
  }
  return 0;
}

int uebernehmen(p, h, n)
int p, h, n;
{
  int i, j, ci, cj, wi, wj, fb, is;

  is = (ausspl + vmh) % 3 == spieler;
  if (is && vmh == 1 && !hatnfb[left(spieler)][trumpf] &&
      (stcd[0] >> 3 == trumpf || (stcd[0] & 7) == BUBE ||
       hatnfb[left(spieler)][stcd[0] >> 3]))
    h = 0;
  j = 0;
  calc_inhand((ausspl + vmh) % 3);
  for (i = 0; i < possc; i++) {
    ci = cards[possi[i]];
    if (!higher(stcd[p], ci)) {
      if (j) {
        cj = cards[possi[j - 1]];
        wi = cardw[ci & 7];
        wj = cardw[cj & 7];
        if (is) {
          if (h) {
            calc_high(1, 1);
            fb = wj == 2 ? trumpf : cj >> 3;
            if (cj == high[fb] && shigh[fb] >= 0 &&
                !inhand[shigh[fb] >> 3][shigh[fb] & 7]) {
              j = i + 1;
              continue;
            }
            fb = wi == 2 ? trumpf : ci >> 3;
            if (ci == high[fb] && shigh[fb] >= 0 &&
                !inhand[shigh[fb] >> 3][shigh[fb] & 7])
              continue;
          }
        }
        if (wi == 10) wi = 12 - h * 2;
        if (wj == 10) wj = 12 - h * 2;
        if (wi == 2 && wj == 2) {
          if (trumpf == 4 && is) {
            wi = ci >> 3;
            wj = cj >> 3;
          } else {
            wi = cj >> 3;
            wj = ci >> 3;
          }
        } else {
          if (wi == 2) wi = 5 - h * 6;
          if (wj == 2) wj = 5 - h * 6;
        }
        if (is) {
          if (!h && zweihoechste(ci))
            j = i + 1;
          else {
            if (n) {
              if ((wi == 4 && ci >> 3 != trumpf) || wi == 10) wi = -1;
              if ((wj == 4 && cj >> 3 != trumpf) || wj == 10) wj = -1;
            }
            if ((h || !zweihoechste(cj)) && ((wi < wj) ^ h)) j = i + 1;
          }
        } else {
          if ((wi < wj) ^ h) j = i + 1;
        }
      } else
        j = i + 1;
    }
  }
  if (j) {
    cj = cards[possi[j - 1]];
    wj = cardw[cj & 7];
    if (is && vmh == 1 && wj > 4 && !hatnfb[left(spieler)][trumpf] &&
        (stcd[0] >> 3 == trumpf ||
         (wj == 10 && !gespcd[(cj & 0x18) | AS] && !inhand[cj >> 3][AS]) ||
         (stcd[0] & 7) == BUBE || hatnfb[left(spieler)][stcd[0] >> 3]))
      j = 0;
    else if (!h && wj == 10 && gespcd[(cj & 0x18) | AS] < !is + 1)
      j = 0;
    else
      playcd = j - 1;
  }
  return j != 0;
}

void schmieren() {
  int i, j, wi, wj, ci, cj, aw[4];

  j     = 0;
  aw[0] = aw[1] = aw[2] = aw[3] = 11;
  calc_high(2, 0);
  if (vmh != 2) {
    for (i = 0; i < 4; i++) {
      if (!(i == trumpf && high[i] != (i << 3 | AS) && possc < 3) &&
          !hatnfb[spieler][i])
        aw[i] = 2;
    }
  }
  for (i = 1; i < possc; i++) {
    wi = cardw[(ci = cards[possi[i]]) & 7];
    wj = cardw[(cj = cards[possi[j]]) & 7];
    if (wi == 2)
      wi = -2;
    else if (ci >> 3 == trumpf && cj >> 3 != trumpf)
      wi = 1;
    else if (wi == 11)
      wi = aw[ci >> 3];
    if (wj == 2)
      wj = -2;
    else if (cj >> 3 == trumpf && ci >> 3 != trumpf)
      wj = 1;
    else if (wj == 11)
      wj = aw[cj >> 3];
    if (wi > wj || (vmh == 2 && wi == wj && !wi && (ci & 7) > (cj & 7))) j = i;
  }
  playcd = j;
}

int einstechen() {
  int ci;

  if (!cardw[stcd[0] & 7] || !uebernehmen(0, 0, 0)) return 0;
  ci = cards[possi[playcd]];
  if ((ci & 7) <= ZEHN || (ci & 7) == BUBE) return 0;
  if (ci >> 3 == trumpf) return 1;
  return 0;
}

int niedrighoch(f)
int f;
{
  int i, j, ok, gespsav[32];

  for (i = 0; i < 32; i++) gespsav[i] = gespcd[i];
  ok = j = 0;
  do {
    calc_high(1, 0);
    if (ok) ok = 2;
    for (i = 0; i < possc; i++) {
      if (cards[possi[i]] == high[f]) {
        j++;
        if (f != trumpf || j < 3) {
          ok                      = 1;
          playcd                  = i;
          gespcd[cards[possi[i]]] = 2;
        }
      }
    }
  } while (ok == 1);
  for (i = 0; i < 32; i++) gespcd[i] = gespsav[i];
  return ok;
}

int ueberdoerfer() {
  int i, j;

  if ((trumpf == 4 &&
       (!hatnfb[left(spieler)][trumpf] || !hatnfb[right(spieler)][trumpf])) ||
      sptruempfe > 4)
    return 0;
  calc_high(1, 0);
  for (i = 0; i < possc; i++) {
    for (j = 0; j < 4; j++) {
      if (j != trumpf && cards[possi[i]] == high[j]) {
        playcd = i;
        return 1;
      }
    }
  }
  return 0;
}

int bubeausspielen() {
  int i, c;

  c = -1;
  calc_inhand(spieler);
  if (inhand[3][BUBE] && inhand[2][BUBE] && inhand[1][BUBE]) {
    c = rnd(1) ? 1 : rnd(1) ? 2 : 3;
  } else if (inhand[3][BUBE] && inhand[2][BUBE]) {
    c = rnd(1) ? 3 : 2;
  } else if (inhand[3][BUBE] && inhand[1][BUBE]) {
    c = rnd(7) ? 3 : 1;
  } else if (inhand[2][BUBE] && inhand[1][BUBE]) {
    c = rnd(1) ? 2 : 1;
  }
  if (c >= 0) {
    c = c << 3 | BUBE;
    for (i = 0; i < possc; i++) {
      if (cards[possi[i]] == c) {
        playcd = i;
        return 1;
      }
    }
  }
  return 0;
}

int trumpfausspielen() {
  int i, j, k, g1, g2, tr, trdr, wi, wj;

  g1 = left(spieler);
  g2 = right(spieler);
  if (!hatnfb[g1][trumpf] || !hatnfb[g2][trumpf]) {
    if (trumpf != 4 && bubeausspielen()) return 1;
    if (niedrighoch(trumpf)) return 1;
  }
  if (trumpf == 4 && hatnfb[g1][trumpf] && hatnfb[g2][trumpf]) {
    return 0;
  }
  calc_high(1, 0);
  tr = wj = 0;
  j       = -1;
  for (i = 0; i < possc; i++) {
    if (cards[possi[i]] >> 3 == trumpf || (cards[possi[i]] & 7) == BUBE) {
      tr++;
    }
  }
  trdr = 7 - gespfb[trumpf];
  for (i = 0; i < 4; i++)
    if (!gespcd[i << 3 | BUBE]) trdr++;
  for (i = 0; i < possc; i++) {
    if (cards[possi[i]] >> 3 == trumpf || (cards[possi[i]] & 7) == BUBE) {
      wi = cardw[cards[possi[i]] & 7];
      if (wi == 2 && trdr - tr != 1) wi = -1;
      if (j < 0 || wi < wj) {
        j  = i;
        wj = wi;
      }
    }
  }
  k = possc;
  if (trumpf < 4) {
    trdr = 7 - gespfb[trumpf];
    if (wj != -1 && (hatnfb[g1][trumpf] || hatnfb[g2][trumpf])) {
      calc_inhand(spieler);
      for (i = SIEBEN; i >= DAME; i--) {
        if (i == BUBE) continue;
        if (!gespcd[trumpf << 3 | i] && !inhand[trumpf][i]) {
          for (; i >= KOENIG; i--) {
            if (i == BUBE) continue;
            if (inhand[trumpf][i]) {
              for (k = 0; k < possc; k++) {
                if (cards[possi[k]] == (trumpf << 3 | i)) {
                  break;
                }
              }
              break;
            }
          }
          break;
        }
      }
    }
  } else
    trdr = 0;
  for (i = 0; i < 4; i++)
    if (!gespcd[i << 3 | BUBE]) trdr++;
  if ((tr > 2 && (trumpf != 4 || trdr - tr)) ||
      (tr > 1 && trdr - tr && trdr - tr <= 2)) {
    playcd =
        k != possc && (trdr - tr == 2 || !cardw[cards[possi[k]] & 7]) ? k : j;
    return 1;
  }
  for (i = 0; i < possc; i++) {
    for (j = 0; j < 4; j++) {
      if (j != trumpf && cards[possi[i]] == high[j]) {
        if ((cards[possi[i]] & 7) == AS)
          playcd = i;
        else
          niedrighoch(j);
        return 1;
      }
    }
  }
  return 0;
}

int hochausspielen() {
  int i, j, k;

  calc_high(2, 0);
  for (k = 0; k < 5; k++) {
    j = k ? k - 1 : trumpf;
    for (i = 0; i < possc; i++) {
      if (cards[possi[i]] == high[j] && (j != trumpf || stich > 6) &&
          (!hatnfb[spieler][j] || stich > 7)) {
        playcd = i;
        return 1;
      }
    }
  }
  return 0;
}

void schenke() {
  int i, j, ci, cj, wi, wj, iw, jw, ih[4], ze[4], ko[4], da[4], ne[4];

  if (!vmh && trumpf == 4) {
    for (i = 0; i < 4; i++) {
      ih[i] = ze[i] = ko[i] = da[i] = ne[i] = 0;
    }
    for (i = 0; i < possc; i++) {
      ci = cards[possi[i]];
      if ((ci & 7) != BUBE) ih[ci >> 3]++;
      if ((ci & 7) == ZEHN)
        ze[ci >> 3] = 1;
      else if ((ci & 7) == KOENIG)
        ko[ci >> 3] = 1;
      else if ((ci & 7) == DAME)
        da[ci >> 3] = 1;
      else if ((ci & 7) == NEUN)
        ne[ci >> 3] = 1;
    }
  }
  j = 0;
  for (i = 1; i < possc; i++) {
    ci = cards[possi[i]];
    cj = cards[possi[j]];
    wi = cardw[iw = (ci & 7)];
    wj = cardw[jw = (cj & 7)];
    if (wi == 2) wi = 5;
    if (wj == 2) wj = 5;
    if (wi == 5 && wj == 5) {
      wi = ci >> 3;
      wj = cj >> 3;
    } else {
      if (!wi && !gespcd[(ci & ~7) | AS] && zehnblank(ci) && stich <= 6)
        wi += 4;
      if (!wj && !gespcd[(cj & ~7) | AS] && zehnblank(cj) && stich <= 6)
        wj += 4;
    }
    if ((ci & 7) == BUBE || ci >> 3 == trumpf) wi += 5;
    if ((cj & 7) == BUBE || cj >> 3 == trumpf) wj += 5;
    if (wi < wj ||
        (wi == wj &&
         (((vmh || trumpf != 4) && iw >= NEUN && jw >= NEUN && iw > jw) ||
          (!vmh && trumpf == 4 && ih[ci >> 3] > ih[cj >> 3]))))
      j = i;
  }
  if (!vmh && trumpf == 4) {
    for (i = 1; i < possc; i++) {
      ci = cards[possi[i]];
      cj = cards[possi[j]];
      wi = cardw[iw = (ci & 7)];
      wj = cardw[jw = (cj & 7)];
      if (ci >> 3 == cj >> 3 && ze[ci >> 3] && ko[ci >> 3] && ih[ci >> 3] > 2) {
        if (((wi == 4 && !da[ci >> 3] && !ne[ci >> 3]) ||
             (wi == 3 && !ne[ci >> 3]) || iw == NEUN) &&
            !wj)
          j = i;
      }
    }
  }
  playcd = j;
}

int zehnblank(ci)
int ci;
{
  int i, f, n, z, a, cj;

  f = ci >> 3;
  n = z = a = 0;
  for (i = 0; i < possc; i++) {
    cj = cards[possi[i]];
    if ((cj & 7) != BUBE && cj >> 3 == f) {
      n++;
      if ((cj & 7) == ZEHN)
        z = 1;
      else if ((cj & 7) == AS)
        a = 1;
    }
  }
  return z && !a && n == 2 && !hatnfb[spieler][f];
}

int fabwerfen() {
  int i, fb, ci, n[4];

  fb = stcd[0] >> 3;
  if (!hatnfb[spieler][fb] ||
      (vmh == 2 && cardw[stcd[0] & 7] + cardw[stcd[1] & 7] > 4) ||
      (vmh == 1 && cardw[stcd[0] & 7] > 0))
    return 0;
  n[0] = n[1] = n[2] = n[3] = 0;
  for (i = 0; i < possc; i++) {
    ci = cards[possi[i]];
    if ((ci & 7) != BUBE && ci >> 3 != trumpf) {
      n[ci >> 3]++;
    }
  }
  calc_high(1, 0);
  for (i = 0; i < possc; i++) {
    ci = cards[possi[i]];
    fb = ci >> 3;
    if ((ci & 7) != BUBE && fb != trumpf && cardw[ci & 7] <= 4 && n[fb] == 1 &&
        ci != high[fb]) {
      playcd = i;
      return 1;
    }
  }
  return 0;
}

void abwerfen() {
  int i, j, ci, cj, wi, wj, mi, wio, wjo, h;
  int gsp[4], ze[4], as[4], ih[4];

  for (i = 0; i < 4; i++) gsp[i] = ze[i] = as[i] = ih[i] = 0;
  for (i = 0; i < 32; i++) {
    if ((i & 7) != BUBE && gespcd[i] == 2) gsp[i >> 3]++;
  }
  for (i = 0; i < possc; i++) {
    ci = cards[possi[i]];
    if ((ci & 7) != BUBE) ih[ci >> 3]++;
    if ((ci & 7) == ZEHN)
      ze[ci >> 3] = 1;
    else if ((ci & 7) == AS)
      as[ci >> 3] = 1;
  }
  j = 0;
  for (i = 1; i < possc; i++) {
    ci  = cards[possi[i]];
    cj  = cards[possi[j]];
    wi  = cardw[ci & 7];
    wj  = cardw[cj & 7];
    wio = wi;
    wjo = wj;
    if (wi == 2) wi = 5;
    if (wj == 2) wj = 5;
    if (wi == 5 && wj == 5) {
      wi = ci >> 3;
      wj = cj >> 3;
    } else {
      if (stich > 7) {
        wi *= 2;
        wj *= 2;
        if (wi == 10 || ci >> 3 == trumpf) wi += 12;
        if (wj == 10 || cj >> 3 == trumpf) wj += 12;
        if (hatnfb[spieler][ci >> 3]) wi -= 7;
        if (hatnfb[spieler][cj >> 3]) wj -= 7;
      } else {
        if (wi == 5 || ci >> 3 == trumpf) wi += 5;
        if (wj == 5 || cj >> 3 == trumpf) wj += 5;
        if (wi < 4 && zehnblank(ci) && stich <= 7) wi += wi ? 2 : 6;
        if (wj < 4 && zehnblank(cj) && stich <= 7) wj += wj ? 2 : 6;
        if (!vmh) {
          if (trumpf == 4) {
            if ((ci & 7) != BUBE && hatnfb[spieler][ci >> 3]) wi -= 30;
            if ((cj & 7) != BUBE && hatnfb[spieler][cj >> 3]) wj -= 30;
          } else {
            mi  = spieler == left(ausspl) ? 2 : 1;
            wio = wi;
            wjo = wj;
            if (!hatnfb[spieler][ci >> 3])
              wi += 8;
            else if (hatnfb[spieler][ci >> 3] &&
                     hatnfb[(ausspl + mi) % 3][ci >> 3] != 1 &&
                     ih[ci >> 3] + gsp[ci >> 3] > 4 && !as[ci >> 3] &&
                     gespcd[(ci & ~7) | AS] != 2) {
              wi += 35;
            } else if (wi > 4)
              wi += 8;
            if (!hatnfb[spieler][cj >> 3])
              wj += 8;
            else if (hatnfb[spieler][cj >> 3] &&
                     hatnfb[(ausspl + mi) % 3][cj >> 3] != 1 &&
                     ih[cj >> 3] + gsp[cj >> 3] > 4 && !as[cj >> 3] &&
                     gespcd[(cj & ~7) | AS] != 2) {
              wj += 35;
            } else if (wj > 4)
              wj += 8;
            if (mi == 2 && hatnfb[(ausspl + mi) % 3][trumpf] != 1) {
              h = 0;
              if (hatnfb[(ausspl + mi) % 3][ci >> 3] == 1 && wio <= 4)
                wi -= 30, h++;
              if (hatnfb[(ausspl + mi) % 3][cj >> 3] == 1 && wjo <= 4)
                wj -= 30, h++;
              if (h == 2) swap(&wi, &wj);
            }
          }
          if (wi == wj && stich <= 3 && ci >> 3 != cj >> 3) {
            if (ih[ci >> 3] < ih[cj >> 3])
              wi--;
            else if (ih[ci >> 3] > ih[cj >> 3])
              wj--;
            else if (ih[ci >> 3] == 2) {
              if (as[ci >> 3]) wi -= spieler == left(ausspl) ? 1 : -1;
              if (as[cj >> 3]) wj -= spieler == left(ausspl) ? 1 : -1;
            }
            if (spieler == left(ausspl) || trumpf == 4) swap(&wi, &wj);
          }
        } else {
          if (possc == 2 && ((stcd[0] & 7) == BUBE || stcd[0] >> 3 == trumpf) &&
              (wio == 2 || wjo == 2) && (wio >= 10 || wjo >= 10)) {
            if (wio >= 10)
              wi = 1, wj = 2;
            else
              wi = 2, wj = 1;
            if (((gespcd[BUBE] == 2 &&
                  (gespcd[trumpf << 3 | AS] == 2 || wio == 11 || wjo == 11)) ||
                 ci == BUBE || cj == BUBE || gespcd[2 << 3 | BUBE] != 2 ||
                 gespcd[3 << 3 | BUBE] != 2) &&
                !(gespcd[2 << 3 | BUBE] == 2 && gespcd[3 << 3 | BUBE] != 2 &&
                  vmh == 1)) {
              swap(&wi, &wj);
            }
          } else {
            if ((ci & 7) == BUBE)
              wi += 5;
            else if (!hatnfb[spieler][ci >> 3] && wi >= 4)
              wi += 3;
            if ((cj & 7) == BUBE)
              wj += 5;
            else if (!hatnfb[spieler][cj >> 3] && wj >= 4)
              wj += 3;
            if (vmh == 1 && spieler != ausspl) {
              if (wi > 1 && wi < 5 && !wj && !cardw[stcd[0] & 7] &&
                  hatnfb[spieler][stcd[0] >> 3]) {
                wi = 1;
                wj = 2;
              } else if (wj > 1 && wj < 5 && !wi && !cardw[stcd[0] & 7] &&
                         hatnfb[spieler][stcd[0] >> 3]) {
                wi = 2;
                wj = 1;
              }
            }
          }
        }
      }
    }
    if (wi < wj ||
        (wi == wj && !cardw[ci & 7] && !cardw[cj & 7] && (ci & 7) > (cj & 7)))
      j = i;
  }
  playcd = j;
}

int buttern() {
  int fb, mi, se;

  se = left(ausspl);
  mi = spieler == ausspl ? right(ausspl) : ausspl;
  fb = stcd[0] >> 3;
  if ((stcd[0] & 7) == BUBE) fb = trumpf;
  if (stich == 9 && spitzeang) return 1;
  if (!hatnfb[se][fb]) return 0;
  calc_high(2, 0);
  if (spieler == ausspl) {
    if ((fb == trumpf && gespcd[trumpf << 3 | AS] == 2 &&
         gespcd[0 << 3 | BUBE] == 2 && gespcd[1 << 3 | BUBE] == 2 &&
         gespcd[2 << 3 | BUBE] == 2 && gespcd[3 << 3 | BUBE] == 2 && rnd(1)) ||
        ((stcd[0] & 7) == BUBE && gespcd[2 << 3 | BUBE] == 2 &&
         gespcd[3 << 3 | BUBE] != 2) ||
        higher(stcd[0], high[fb]) ||
        (hatnfb[mi][fb] == 1 && hatnfb[mi][trumpf] == 1) ||
        (trumpf == 4 && (stcd[0] & 7) != BUBE &&
         (gespcd[0 << 3 | BUBE] == 2 || gespcd[1 << 3 | BUBE] == 2 ||
          gespcd[2 << 3 | BUBE] == 2 || gespcd[3 << 3 | BUBE] == 2)) ||
        (cardw[stcd[0] & 7] > 4 && rnd(1)))
      return 0;
    if (butternok) return rnd(1);
    butternok = rnd(1);
    return 1;
  }
  if (higher(stcd[0], high[trumpf]) && higher(stcd[0], high[fb])) return 1;
  if (higher(stcd[0], high[fb]) && !hatnfb[spieler][fb]) {
    return 1;
  }
  return 0;
}

int hatas() {
  int f, i, as;

  f  = stcd[0] >> 3;
  as = 0;
  for (i = 0; i < possc; i++) {
    if (cards[possi[i]] == (f << 3 | AS)) as = i + 1;
  }
  if (!as || (stcd[0] & 7) == BUBE || f == trumpf || cardw[stcd[0] & 7] > 4 ||
      hatnfb[spieler][f])
    return 0;
  playcd = as - 1;
  return 1;
}

int schnippeln(f)
int f;
{
  int fb, i, j, k, as, hi;

  if (gstsum >= 44 && gstsum < 60) return 0;
  if (stich > 8 && gstsum <= 30) return 0;
  fb = stcd[0] >> 3;
  if ((stcd[0] & 7) == BUBE || (stcd[f] & 7) == BUBE || fb == trumpf ||
      stcd[f] >> 3 == trumpf || (f && fb != stcd[1] >> 3) ||
      gespcd[fb << 3 | ZEHN] == 2 || gespfb[fb] > 3) {
    return 0;
  }
  as = 0;
  for (i = 0; i < possc; i++) {
    if (cards[possi[i]] == (fb << 3 | AS)) as = i + 1;
    if (cards[possi[i]] == (fb << 3 | ZEHN)) return 0;
  }
  if (!as) return 0;
  possi[as - 1] = possi[--possc];
  j = k = 0;
  for (i = 1; i < possc; i++) {
    if (cards[possi[i]] < cards[possi[j]]) j = i;
    if (cards[possi[i]] > cards[possi[k]]) k = i;
  }
  hi     = f ? higher(stcd[0], stcd[1]) ^ (spieler == ausspl)
             : cards[possi[j]] < stcd[0];
  playcd = hi ? j : k;
  return 1;
}

void nichtspitze() {
  int sp, i;

  if (spitzeang) {
    sp = trumpf == 4 ? BUBE : SIEBEN | trumpf << 3;
    for (i = 0; i < possc; i++) {
      if (cards[possi[i]] == sp) {
        possc--;
        for (; i < possc; i++) {
          possi[i] = possi[i + 1];
        }
        return;
      }
    }
  }
}

int spitzefangen() {
  int i, c, t;

  if (!spitzeang || stich != 9) return 0;
  t = -1;
  for (i = 0; i < possc; i++) {
    if (((c = cards[possi[i]]) & 7) == BUBE || c >> 3 == trumpf) {
      if (t != -1) return 0;
      t = i;
    }
  }
  if (t == -1) return 0;
  playcd = t ? 0 : 1;
  return 1;
}

int restbeimir() {
  int c, h, i, j, k, s[2];

  if (stich == 10 || vmh || ausspl != spieler || trumpf < 0 || trumpf > 4)
    return 0;
  s[0] = left(spieler);
  s[1] = right(spieler);
  if (!hatnfb[s[0]][trumpf] || !hatnfb[s[1]][trumpf]) {
    if (trumpf == 4) return 0;
    h = -1;
    for (k = 0; k < 10; k++) {
      if ((c = cards[spieler * 10 + k]) >= 0) {
        if (c >> 3 != trumpf && (c & 7) != BUBE) return 0;
        if (h < 0 || !higher(c, cards[spieler * 10 + h])) h = k;
      }
    }
    for (j = 0; j < 2; j++) {
      for (k = handsp ? -1 : 0; k < 10; k++) {
        if ((c = k < 0 ? prot2.skat[0][j] : cards[s[j] * 10 + k]) >= 0 &&
            higher(c, cards[spieler * 10 + h]))
          return 0;
      }
    }
    return 1;
  }
  for (i = 0; i < 4; i++) {
    if (i == trumpf || (hatnfb[s[0]][i] && hatnfb[s[1]][i])) continue;
    h = SIEBEN + 1;
    for (j = 0; j < 2; j++) {
      for (k = handsp ? -1 : 0; k < 10; k++) {
        if ((c = k < 0 ? prot2.skat[0][j] : cards[s[j] * 10 + k]) >= 0 &&
            c >> 3 == i && (c & 7) != BUBE && (c & 7) < h)
          h = c & 7;
      }
    }
    for (k = 0; k < 10; k++) {
      if ((c = cards[spieler * 10 + k]) >= 0 && c >> 3 == i &&
          (c & 7) != BUBE && (c & 7) > h)
        return 0;
    }
  }
  return 1;
}

void m_bvsp() {
  if (ueberdoerfer()) return;
  if (!trumpfausspielen()) schenke();
}

void m_bmsp() {
  if (fabwerfen()) return;
  if (!uebernehmen(0, 1, 1)) schenke();
}

void m_bhsp() {
  if (gewinnstich(1)) return;
  if (fabwerfen()) return;
  if (!uebernehmen(!higher(stcd[0], stcd[1]), 1, 0)) schenke();
}

void m_bvns() {
  if (spitzefangen()) return;
  if (spieler == left(ausspl) && karobubespielen()) return;
  if (!hochausspielen()) abwerfen();
}

void m_bmns() {
  if (spitzefangen()) return;
  if (karobubespielen()) return;
  if (spieler == ausspl) {
    if ((rnd(3) && schnippeln(0)) || (!ignorieren() && uebernehmen(0, 1, 0)))
      return;
  } else {
    if (einstechen() || hatas()) return;
  }
  if (buttern())
    schmieren();
  else
    abwerfen();
}

void m_bhns() {
  if (gewinnstich(0)) return;
  if (spitzefangen()) return;
  if (rnd(1) && karobubespielen()) return;
  if (rnd(3) && schnippeln(1)) return;
  if (higher(stcd[0], stcd[1]) ^ (spieler != ausspl)) {
    if (!genugdrin() || !uebernehmen(spieler != ausspl, 1, 0)) abwerfen();
  } else {
    schmieren();
  }
}

void m_bsp() {
  playcd = 0;
  nichtspitze();
  if (!vmh)
    m_bvsp();
  else if (vmh == 1)
    m_bmsp();
  else
    m_bhsp();
}

void m_bns() {
  playcd = 0;
  if (!vmh)
    m_bvns();
  else if (vmh == 1)
    m_bmns();
  else
    m_bhns();
}

void make_best(s) int s;
{
  if (possc == 1)
    playcd = 0;
  else if (trumpf > 4) {
    m_bramsch();
  } else if (trumpf >= 0) {
    if (s == spieler)
      m_bsp();
    else
      m_bns();
  } else {
    if (s == spieler)
      m_nsp();
    else
      m_nns(s);
  }
}

void adjfb(s, v) int s, v;
{
  int i, c, n;
  int fb[5];

  fb[0] = fb[1] = fb[2] = fb[3] = fb[4] = 0;
  n                                     = handsp && s != spieler ? 12 : 10;
  for (i = 0; i < n; i++) {
    if ((c = i < 10 ? cards[10 * s + i] : prot2.skat[0][i - 10]) >= 0) {
      if (trumpf != -1 && (c & 7) == BUBE)
        fb[trumpf] = 1;
      else
        fb[c >> 3] = 1;
    }
  }
  for (i = 0; i < 5; i++) {
    if (!fb[i]) {
      if (hatnfb[s][i] != 1) hatnfb[s][i] = v;
    }
  }
}

#define DRUECKEN(T, N, C)                      \
  {                                            \
    for (i = 0; x && i < 4; i++) {             \
      if (i != trumpf && t[i] == (T) && (C)) { \
        drueck(i, N, &p[i]);                   \
        t[i] -= (N);                           \
        x = 0;                                 \
        break;                                 \
      }                                        \
    }                                          \
  }

#define LUSCHE() (inhand[i][SIEBEN] || inhand[i][ACHT] || inhand[i][NEUN])

void calc_drueck() {
  int i, j, c, f, bb, n, sp, tr, x;
  int b[4], t[4], p[4], o[4];
  int savecards[32];

  if (iscomp(spieler)) {
    if (maxrw[spieler] == nullw[0] || maxrw[spieler] == nullw[1] ||
        maxrw[spieler] == nullw[2] || maxrw[spieler] == nullw[3] ||
        maxrw[spieler] == nullw[4]) {
      trumpf = -1;
      if (maxrw[spieler] != nullw[0] && maxrw[spieler] != nullw[2]) handsp = 1;
      if (maxrw[spieler] >= nullw[3]) ouveang = 1;
      if (maxrw[spieler] == nullw[4]) revolang = 1;
      gedr = 2;
      return;
    }
    if (testhand()) {
      gedr   = 2;
      handsp = 1;
      return;
    }
  } else {
    for (i = 0; i < 32; i++) savecards[i] = cards[i];
  }
  for (i = 0; i < 4; i++) {
    b[i] = t[i] = p[i] = 0;
  }
  bb = 0;
  for (i = 0; i < 4; i++) {
    for (c = 0; c < 8; c++) inhand[i][c] = 0;
  }
  for (i = 0; i < 12; i++) {
    c = spcards[i];
    if ((c & 7) == BUBE) {
      b[c >> 3] = 1;
      bb++;
    } else {
      p[c >> 3] += cardw[c & 7];
      t[c >> 3]++;
      inhand[c >> 3][c & 7] = 1;
    }
  }
  f = 2;
  while (f < 5 && b[4 - f] == b[3]) f++;
  trumpf = 0;
  if (iscomp(spieler)) {
    while (f * rwert[trumpf] < reizw[reizp]) trumpf++;
  }
  for (i = trumpf + 1; i < 4; i++) {
    if (t[i] > t[trumpf] || (t[i] == t[trumpf] && p[i] <= p[trumpf]))
      trumpf = i;
  }
  tr = t[trumpf];
  truempfe();
  do {
    x = 1;
    if (!gedr) {
      DRUECKEN(1, 1, inhand[i][ZEHN]);
      DRUECKEN(2, 1, inhand[i][ZEHN] && (inhand[i][DAME] || LUSCHE()));
      DRUECKEN(1, 1, inhand[i][KOENIG]);
      DRUECKEN(2, 2, inhand[i][KOENIG] && inhand[i][DAME]);
      DRUECKEN(1, 1, inhand[i][DAME]);
      DRUECKEN(2, 2, inhand[i][KOENIG] && LUSCHE());
      DRUECKEN(2, 2, inhand[i][DAME] && LUSCHE());
      DRUECKEN(2, 2, inhand[i][ZEHN] && inhand[i][KOENIG]);
      DRUECKEN(1, 1, !p[i]);
      DRUECKEN(2, 2, !p[i]);
      DRUECKEN(2, 1, inhand[i][AS] && inhand[i][KOENIG]);
      DRUECKEN(2, 1, inhand[i][AS] && inhand[i][DAME]);
      DRUECKEN(2, 1, inhand[i][AS] && LUSCHE());
    } else {
      DRUECKEN(1, 1, inhand[i][ZEHN]);
      DRUECKEN(2, 1, inhand[i][ZEHN] && (inhand[i][DAME] || LUSCHE()));
      DRUECKEN(1, 1, inhand[i][KOENIG]);
      DRUECKEN(1, 1, inhand[i][DAME]);
      DRUECKEN(1, 1, !p[i]);
      DRUECKEN(2, 1, inhand[i][KOENIG] && LUSCHE());
      DRUECKEN(2, 1, inhand[i][DAME] && LUSCHE());
      DRUECKEN(2, 1, inhand[i][KOENIG] && inhand[i][DAME]);
      DRUECKEN(2, 1, !p[i]);
      DRUECKEN(2, 1, inhand[i][AS] && inhand[i][KOENIG]);
      DRUECKEN(2, 1, inhand[i][AS] && inhand[i][DAME]);
      DRUECKEN(2, 1, inhand[i][AS] && LUSCHE());
      DRUECKEN(2, 1, inhand[i][ZEHN] && inhand[i][KOENIG]);
    }
  } while (gedr < 2 && !x);
  for (i = 0; i < 4; i++) {
    o[i] = i;
  }
  for (i = 0; i < 4; i++) {
    for (j = i + 1; j < 4; j++) {
      if (p[o[i]] > p[o[j]]) {
        x    = o[i];
        o[i] = o[j];
        o[j] = x;
      }
    }
  }
  for (n = 3; n < 8 && gedr < 2; n++) {
    for (j = 0; j < 4 && gedr < 2; j++) {
      i = o[j];
      if (t[i] == n && i != trumpf) {
        if (inhand[i][AS]) {
          if (!inhand[i][ZEHN]) drueck(i, 2, &p[i]);
        } else
          drueck(i, 2, &p[i]);
      }
    }
  }
  if (testgrand(bb, b, spieler == ausspl)) {
    trumpf = 4;
  }
  if (spitzezaehlt &&
      ((trumpf < 4 && inhand[trumpf][SIEBEN] &&
        ((tr + bb >= 7 && (bb > 1 || !b[0])) || (tr + bb == 6 && bb >= 4))) ||
       (trumpf == 4 && b[0] && b[3] && bb == 3 && spieler == ausspl))) {
    sp = trumpf == 4 ? BUBE : SIEBEN | trumpf << 3;
    if (cards[30] != sp && cards[31] != sp) {
      spitzeang = 1;
    }
  }
  if (iscomp(spieler)) {
    gespcd[cards[30]] = 1;
    gespcd[cards[31]] = 1;
  } else {
    for (j = 0; j < 2; j++) {
      for (i = 0; i < 12; i++) {
        if (cards[30 + j] == spcards[i]) {
          hintcard[j] = i < 10 ? 10 * spieler + i : 20 + i;
          break;
        }
      }
    }
    for (i = 0; i < 32; i++) cards[i] = savecards[i];
  }
}

void do_spielen() {
  int s, i;
  static int sp, lvmh;

  if (phase != SPIELEN) {
    sp = 0;
    return;
  }
  if (trumpf == -1 && stich == 1) init_null();
  while (phase == SPIELEN) {
    s = (ausspl + vmh) % 3;
    if (iscomp(s))
      sp = 0;
    else {
      if (sp == s + 1 && lvmh == vmh) return;
      sp = s + 1;
    }
    lvmh = vmh;
    if (s == spieler && trumpf != 5) {
      adjfb(left(spieler), 2);
      adjfb(right(spieler), 2);
      for (i = 0; i < 5; i++) {
        if (!hatnfb[left(spieler)][i] || !hatnfb[right(spieler)][i]) {
          if (hatnfb[left(spieler)][i] == 2) hatnfb[left(spieler)][i] = 0;
          if (hatnfb[right(spieler)][i] == 2) hatnfb[right(spieler)][i] = 0;
        }
      }
    }
    if (ouveang) {
      adjfb(spieler, 1);
    }
    calc_poss(s);
    if (trumpf == -1 && stich == 1 && sp) testnull(s);
    make_best(s);
    hintcard[0] = possi[playcd];
    if (sp && hints[s]) {
      show_hint(s, 0, 1);
    }
    if (!ndichtw && restbeimir()) {
      di_dicht();
      return;
    }
    if (sp) return;
    drop_card(possi[playcd], s);
    do_next();
  }
}

void computer() {
  if (quit) return;
  if (phase == GEBEN) do_geben();
  if (phase == REIZEN) do_reizen();
  do_spielen();
}

/* End of AI Engine */
