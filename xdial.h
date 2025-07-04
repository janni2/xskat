
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

#ifndef XDIAL_H
#define XDIAL_H

#include <X11/X.h>

#include "text.h"

#undef EXTERN
#ifdef XDIAL_C
#define EXTERN
#else
#define EXTERN extern
#endif

#define OB_NONE 0
#define OB_BUTTON (1 << 0)
#define OB_EXIT (1 << 1)
#define OB_SELECTED (1 << 2)
#define OB_CENTERED (1 << 3)
#define OB_HIDDEN (1 << 4)
#define OB_BOLD (1 << 5)
#define OB_UNDERLINED (1 << 6)
#define OB_RIGHT (1 << 7)
#define OB_DISABLED (1 << 8)

#define TOB(t) ((tx_typ*)((t) + OB_NONE + 1))

typedef struct {
  int spec;
  int x, y, w, h;
  tx_typ* str;
  int next;
  Window win;
} OBJECT;

EXTERN OBJECT* actdial[3];
EXTERN OBJECT* resdial[3];
EXTERN int inputdi[3], inputlen[3];
EXTERN char* inputbuf[3];
EXTERN int ktrsag, ktrnext, schenknext;
EXTERN tx_typ stichstr[2][3][3], spielstr[2][3];

EXTERN OBJECT dihand[]
#ifdef XDIAL_C
    =
        {
            {5,                           0,  0, 23, 7, OB_NONE,        OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 21, 1, TOB(TX_HAND_F), OB_NONE},
            {OB_EXIT,                     2,  3, 8,  1, TOB(TX_JA),     OB_NONE},
            {OB_EXIT,                     13, 3, 8,  1, TOB(TX_NEIN),   OB_NONE},
            {OB_CENTERED,                 1,  5, 21, 1, OB_NONE,        OB_NONE}
}
#endif
;

EXTERN OBJECT digrandhand[]
#ifdef XDIAL_C
    =
        {
            {4,                           0,  0, 19, 6, OB_NONE,            OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 17, 1, TOB(TX_GRAND_HAND),
             OB_NONE                                                               },
            {OB_EXIT,                     2,  4, 6,  1, TOB(TX_NEIN),       OB_NONE},
            {OB_EXIT,                     11, 4, 6,  1, TOB(TX_JA),         OB_NONE}
}
#endif
;

EXTERN OBJECT dischieben[]
#ifdef XDIAL_C
    =
        {
            {4,                           0,  0, 23, 6, OB_NONE,                OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 21, 1, TOB(TX_SKAT_AUFNEHMEN),
             OB_NONE                                                                   },
            {OB_EXIT,                     4,  4, 6,  1, TOB(TX_JA),             OB_NONE},
            {OB_EXIT,                     13, 4, 6,  1, TOB(TX_NEIN),           OB_NONE}
}
#endif
;

EXTERN OBJECT diverdoppelt[]
#ifdef XDIAL_C
    =
        {
            {5,                           0,  0, 33, 8, OB_NONE,            OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 31, 1, TOB(TX_VERDOPPELT),
             OB_NONE                                                               },
            {OB_CENTERED,                 1,  3, 31, 1, OB_NONE,            OB_NONE},
            {OB_CENTERED,                 1,  4, 31, 1, TOB(TX_SCHIEBT),    OB_NONE},
            {OB_EXIT,                     12, 6, 9,  1, TOB(TX_AHA),        OB_NONE}
}
#endif
;

EXTERN OBJECT dibuben[]
#ifdef XDIAL_C
    =
        {
            {4,                           0,  0, 43, 7, OB_NONE,             OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 41, 1, TOB(TX_HINWEIS),
             OB_NONE                                                                },
            {OB_CENTERED,                 1,  3, 41, 1, TOB(TX_BUBEN_NICHT), OB_NONE},
            {OB_EXIT,                     17, 5, 9,  1, TOB(TX_AHA),         OB_NONE}
}
#endif
;

EXTERN OBJECT diklopfen[]
#ifdef XDIAL_C
    =
        {
            {5,                           0,  0, 27, 7, OB_NONE,                      OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 25, 1, TOB(TX_KLOPFEN_T),
             OB_NONE                                                                         },
            {OB_CENTERED,                 1,  3, 25, 1, TOB(TX_SPIELWERT_VERDOPPELN), OB_NONE},
            {OB_EXIT,                     6,  5, 6,  1, TOB(TX_NEIN),                 OB_NONE},
            {OB_EXIT,                     15, 5, 6,  1, TOB(TX_JA),                   OB_NONE}
}
#endif
;

EXTERN OBJECT dischenken[]
#ifdef XDIAL_C
    =
        {
            {5,                           0,  0, 27, 7, OB_NONE,                      OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 25, 1, TOB(TX_SCHENKEN_T),
             OB_NONE                                                                         },
            {OB_CENTERED,                 1,  3, 25, 1, TOB(TX_SPIEL_VERLOREN_GEBEN), OB_NONE},
            {OB_EXIT,                     6,  5, 6,  1, TOB(TX_NEIN),                 OB_NONE},
            {OB_EXIT,                     15, 5, 6,  1, TOB(TX_JA),                   OB_NONE}
}
#endif
;

EXTERN OBJECT digeschenkt[]
#ifdef XDIAL_C
    =
        {
            {5,                           0,  0, 27, 7, OB_NONE,                   OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 25, 1, TOB(TX_SCHENKEN_T),
             OB_NONE                                                                      },
            {OB_CENTERED,                 1,  3, 25, 1, TOB(TX_GESCHENK_ANNEHMEN), OB_NONE},
            {OB_EXIT,                     2,  5, 11, 1, TOB(TX_JA),                OB_NONE},
            {OB_EXIT,                     14, 5, 11, 1, TOB(TX_SCHNEIDER),         OB_NONE}
}
#endif
;

EXTERN OBJECT diendeschenken[]
#ifdef XDIAL_C
    =
        {
            {4,                           0,  0, 27, 7, OB_NONE,                  OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 25, 1, TOB(TX_SCHENKEN_T),
             OB_NONE                                                                     },
            {OB_CENTERED,                 1,  3, 25, 1, TOB(TX_GEGNER_GEBEN_AUF), OB_NONE},
            {OB_EXIT,                     10, 5, 7,  1, TOB(TX_AHA),              OB_NONE}
}
#endif
;

EXTERN OBJECT diwiederschenken[]
#ifdef XDIAL_C
    =
        {
            {6,                           0,  0, 27, 9, OB_NONE,                      OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 25, 1, TOB(TX_SCHENKEN_T),
             OB_NONE                                                                         },
            {OB_CENTERED,                 1,  3, 25, 1, TOB(TX_SCHN_ANGE),            OB_NONE},
            {OB_CENTERED,                 1,  5, 25, 1, TOB(TX_SPIEL_VERLOREN_GEBEN), OB_NONE},
            {OB_EXIT,                     6,  7, 6,  1, TOB(TX_NEIN),                 OB_NONE},
            {OB_EXIT,                     15, 7, 6,  1, TOB(TX_JA),                   OB_NONE}
}
#endif
;

EXTERN OBJECT dinichtschenken[]
#ifdef XDIAL_C
    =
        {
            {4,                           0, 0, 27, 7, OB_NONE,                     OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1, 1, 25, 1, TOB(TX_SCHENKEN_T),
             OB_NONE                                                                       },
            {OB_CENTERED,                 1, 3, 25, 1, TOB(TX_MITSPIELER_LEHNT_AB), OB_NONE},
            {OB_EXIT,                     8, 5, 11, 1, TOB(TX_AHA),                 OB_NONE}
}
#endif
;

EXTERN OBJECT diende[3][4]
#ifdef XDIAL_C
    =
        {
            {{4, 0, 0, 19, 6, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 17, 1, TOB(TX_SPIEL_BEENDEN),
              OB_NONE},
             {OB_EXIT, 2, 4, 6, 1, TOB(TX_JA), OB_NONE},
             {OB_EXIT, 11, 4, 6, 1, TOB(TX_NEIN), OB_NONE}}
}
#endif
;

EXTERN OBJECT diterm[3][5]
#ifdef XDIAL_C
    =
        {
            {{5, 0, 0, 23, 8, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 21, 1, TOB(TX_SPIELENDE),
              OB_NONE},
             {OB_CENTERED, 2, 3, 19, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 2, 4, 19, 1, TOB(TX_BEENDET_DAS_SPIEL), OB_NONE},
             {OB_EXIT, 8, 6, 7, 1, TOB(TX_AHA), OB_NONE}}
}
#endif
;

EXTERN OBJECT diloesch[]
#ifdef XDIAL_C
    =
        {
            {4,                           0,  0, 19, 6, OB_NONE,            OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 17, 1, TOB(TX_LOESCHEN_F),
             OB_NONE                                                               },
            {OB_EXIT,                     2,  4, 6,  1, TOB(TX_JA),         OB_NONE},
            {OB_EXIT,                     11, 4, 6,  1, TOB(TX_NEIN),       OB_NONE}
}
#endif
;

EXTERN OBJECT dispiel[]
#ifdef XDIAL_C
    =
        {
            {16,                          0,  0,  43, 13, OB_NONE,            OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1,  41, 1,  TOB(TX_SPIEL),      OB_NONE},
            {OB_BUTTON,                   2,  3,  9,  1,  TOB(TX_KARO),       1      },
            {OB_BUTTON,                   12, 3,  9,  1,  TOB(TX_HERZ),       1      },
            {OB_BUTTON,                   22, 3,  9,  1,  TOB(TX_PIK),        1      },
            {OB_BUTTON,                   32, 3,  9,  1,  TOB(TX_KREUZ),      1      },
            {OB_BUTTON,                   2,  5,  19, 1,  TOB(TX_NULL),       1      },
            {OB_BUTTON,                   22, 5,  19, 1,  TOB(TX_GRAND),      -5     },
            {OB_BUTTON,                   2,  7,  12, 1,  TOB(TX_SCHNEIDER),  OB_NONE},
            {OB_BUTTON,                   15, 7,  13, 1,  TOB(TX_SCHWARZ),    OB_NONE},
            {OB_BUTTON,                   29, 7,  12, 1,  TOB(TX_OUVERT),     OB_NONE},
            {OB_BUTTON,                   2,  9,  12, 1,  TOB(TX_SPITZE),     OB_NONE},
            {OB_EXIT,                     15, 9,  13, 1,  TOB(TX_ANSAGEN),    OB_NONE},
            {OB_BUTTON,                   29, 9,  12, 1,  TOB(TX_REVOLUTION), -11    },
            {OB_EXIT,                     2,  11, 5,  1,  OB_NONE,            OB_NONE},
            {OB_CENTERED,                 8,  11, 27, 1,  OB_NONE,            OB_NONE}
}
#endif
;

EXTERN OBJECT difehler[]
#ifdef XDIAL_C
    =
        {
            {7,                           0,  0, 43, 11, OB_NONE,         OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 41, 1,  TOB(TX_HINWEIS),
             OB_NONE                                                             },
            {OB_CENTERED,                 1,  3, 41, 1,  TOB(TX_F1),      OB_NONE},
            {OB_CENTERED,                 1,  4, 41, 1,  TOB(TX_F2),      OB_NONE},
            {OB_CENTERED,                 1,  6, 41, 1,  TOB(TX_F3),      OB_NONE},
            {OB_CENTERED,                 1,  7, 41, 1,  TOB(TX_F4),      OB_NONE},
            {OB_EXIT,                     17, 9, 9,  1,  TOB(TX_AHA),     OB_NONE}
}
#endif
;

EXTERN OBJECT diueberr[]
#ifdef XDIAL_C
    =
        {
            {8,                           0,  0,  43, 12, OB_NONE,         OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1,  41, 1,  TOB(TX_HINWEIS),
             OB_NONE                                                              },
            {OB_CENTERED,                 1,  3,  41, 1,  TOB(TX_U1),      OB_NONE},
            {OB_CENTERED,                 1,  4,  41, 1,  TOB(TX_U2),      OB_NONE},
            {OB_CENTERED,                 1,  6,  41, 1,  TOB(TX_U3),      OB_NONE},
            {OB_CENTERED,                 1,  7,  41, 1,  TOB(TX_U4),      OB_NONE},
            {OB_CENTERED,                 1,  8,  41, 1,  TOB(TX_U5),      OB_NONE},
            {OB_EXIT,                     17, 10, 9,  1,  TOB(TX_AHA),     OB_NONE}
}
#endif
;

EXTERN OBJECT dispitze[]
#ifdef XDIAL_C
    =
        {
            {5,                           0,  0, 43, 8, OB_NONE,           OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 41, 1, TOB(TX_HINWEIS),
             OB_NONE                                                              },
            {OB_CENTERED,                 1,  3, 41, 1, TOB(TX_SPITZE_F1), OB_NONE},
            {OB_CENTERED,                 1,  4, 41, 1, TOB(TX_SPITZE_F2), OB_NONE},
            {OB_EXIT,                     17, 6, 9,  1, TOB(TX_AHA),       OB_NONE}
}
#endif
;

EXTERN OBJECT diansage[]
#ifdef XDIAL_C
    =
        {
            {3,                           0, 0, 19, 5, OB_NONE,              OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1, 1, 17, 1, TOB(TX_ANGESAGT_IST),
             OB_NONE                                                                },
            {OB_EXIT,                     1, 3, 17, 1, OB_NONE,              OB_NONE}
}
#endif
;

EXTERN OBJECT dikontra[3][5]
#ifdef XDIAL_C
    =
        {
            {{5, 0, 0, 24, 7, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 22, 1, TOB(TX_ANGESAGT_IST),
              OB_NONE},
             {OB_CENTERED, 1, 3, 22, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 2, 5, 9, 1, TOB(TX_KONTRA), OB_NONE},
             {OB_EXIT, 13, 5, 9, 1, TOB(TX_AHA), OB_NONE}}
}
#endif
;

EXTERN OBJECT direkontra[]
#ifdef XDIAL_C
    =
        {
            {5,                           0,  0, 28, 7, OB_NONE,          OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 26, 1, TOB(TX_KONTRA_T),
             OB_NONE                                                             },
            {OB_CENTERED,                 1,  3, 26, 1, OB_NONE,          OB_NONE},
            {OB_EXIT,                     4,  5, 9,  1, TOB(TX_RE),       OB_NONE},
            {OB_EXIT,                     15, 5, 9,  1, TOB(TX_AHA),      OB_NONE}
}
#endif
;

EXTERN OBJECT dikonre[3][5]
#ifdef XDIAL_C
    =
        {
            {{5, 0, 0, 24, 8, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 22, 1, TOB(TX_ANGESAGT_IST),
              OB_NONE},
             {OB_CENTERED, 1, 3, 22, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 1, 4, 22, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 7, 6, 10, 1, TOB(TX_AHA), OB_NONE}}
}
#endif
;

EXTERN OBJECT didicht[]
#ifdef XDIAL_C
    =
        {
            {7,                           0,  0, 24, 9, OB_NONE,                  OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 22, 1, TOB(TX_NULL_DICHT),
             OB_NONE                                                                     },
            {OB_CENTERED,                 1,  3, 22, 1, TOB(TX_KARTEN_AUFDECKEN), OB_NONE},
            {OB_EXIT,                     4,  5, 7,  1, TOB(TX_JA),               OB_NONE},
            {OB_EXIT,                     13, 5, 7,  1, TOB(TX_NEIN),             OB_NONE},
            {OB_EXIT,                     4,  7, 7,  1, TOB(TX_IMMER),            OB_NONE},
            {OB_EXIT,                     13, 7, 7,  1, TOB(TX_NIE),              OB_NONE}
}
#endif
;

EXTERN OBJECT diweiter[3][2]
#ifdef XDIAL_C
    =
        {
            {{2, 0, 0, 14, 3, OB_NONE, OB_NONE},
             {OB_EXIT, 2, 1, 10, 1, TOB(TX_WEITER), OB_NONE}}
}
#endif
;

EXTERN OBJECT diwiederweiter[]
#ifdef XDIAL_C
    =
        {
            {3,       0,  0, 34, 3, OB_NONE,        OB_NONE},
            {OB_EXIT, 2,  1, 14, 1, TOB(TX_WIEDER), OB_NONE},
            {OB_EXIT, 18, 1, 14, 1, TOB(TX_WEITER), OB_NONE}
}
#endif
;

EXTERN OBJECT diwieder[]
#ifdef XDIAL_C
    =
        {
            {13,                          0,  0,  37, 12, OB_NONE,                  OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1,  35, 1,  TOB(TX_SPIEL_WIEDER),
             OB_NONE                                                                       },
            {OB_CENTERED,                 1,  3,  35, 1,  TOB(TX_MIT_DEN_KARTEN),   OB_NONE},
            {OB_CENTERED,                 2,  5,  9,  1,  TOB(TX_COMPUTER),         OB_NONE},
            {OB_CENTERED,                 26, 5,  9,  1,  TOB(TX_COMPUTER),         OB_NONE},
            {OB_BUTTON,                   2,  6,  9,  1,  TOB(TX_LINKS),            1      },
            {OB_BUTTON,                   14, 6,  9,  1,  TOB(TX_MIR),              1      },
            {OB_BUTTON,                   26, 6,  9,  1,  TOB(TX_RECHTS),           -2     },
            {OB_NONE,                     2,  8,  18, 1,  TOB(TX_VORHAND_WECHSELT), OB_NONE},
            {OB_BUTTON,                   23, 8,  6,  1,  TOB(TX_JA),               1      },
            {OB_BUTTON,                   29, 8,  6,  1,  TOB(TX_NEIN),             -1     },
            {OB_EXIT,                     2,  10, 12, 1,  TOB(TX_ZURUECK),          OB_NONE},
            {OB_EXIT,                     23, 10, 12, 1,  TOB(TX_START),            OB_NONE},
}
#endif
;

EXTERN OBJECT diresult[]
#ifdef XDIAL_C
    =
        {
            {24,                          0,  0,  37, 17, OB_NONE,                          OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1,  35, 1,  TOB(TX_RESULTAT),
             OB_NONE                                                                               },
            {OB_CENTERED | OB_BOLD,       1,  2,  35, 1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 1,  3,  35, 1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 1,  4,  35, 1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 1,  5,  35, 1,  TOB(TX_DER_SPIELWERT_IST),        OB_NONE},
            {OB_CENTERED,                 3,  7,  9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 14, 7,  9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 25, 7,  9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 3,  8,  9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 14, 8,  9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 25, 8,  9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 3,  9,  9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 14, 9,  9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 25, 9,  9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 1,  10, 35, 1,  TOB(TX_SPIELE_GEWONNEN_VERLOREN),
             OB_NONE                                                                               },
            {OB_CENTERED,                 3,  11, 9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 14, 11, 9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED,                 25, 11, 9,  1,  OB_NONE,                          OB_NONE},
            {OB_CENTERED | OB_BOLD,       1,  12, 35, 1,  OB_NONE,                          OB_NONE},
            {OB_EXIT,                     3,  13, 14, 1,  TOB(TX_ENDE),                     OB_NONE},
            {OB_EXIT,                     20, 13, 14, 1,  TOB(TX_WIEDER),                   OB_NONE},
            {OB_EXIT,                     3,  15, 14, 1,  TOB(TX_PROTOKOLL),                OB_NONE},
            {OB_EXIT,                     20, 15, 14, 1,  TOB(TX_WEITER),                   OB_NONE}
}
#endif
;

EXTERN OBJECT dismlres[3][18]
#ifdef XDIAL_C
    =
        {
            {{18, 0, 0, 33, 9, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_BOLD, 1, 0, 31, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 1, 1, 31, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 1, 2, 31, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 1, 3, 31, 1, TOB(TX_DER_SPIELWERT_IST), OB_NONE},
             {OB_CENTERED, 2, 4, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 12, 4, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 22, 4, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 2, 5, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 12, 5, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 22, 5, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 2, 6, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 12, 6, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 22, 6, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 2, 7, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 12, 7, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 22, 7, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_BOLD, 1, 8, 31, 1, OB_NONE, OB_NONE}}
}
#endif
;

EXTERN OBJECT diproto[3][50]
#ifdef XDIAL_C
    =
        {
            {{50, 0, 0, 41, 23, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 39, 1, TOB(TX_PROTOKOLL_T),
              OB_NONE},
             {OB_CENTERED, 2, 3, 12, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 14, 3, 12, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 26, 3, 12, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 2, 4, 12, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 14, 4, 12, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 26, 4, 12, 1, OB_NONE, OB_NONE},
             {OB_NONE, 4, 5, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 5, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 28, 5, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 4, 6, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 6, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 28, 6, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 4, 7, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 7, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 28, 7, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 4, 8, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 8, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 28, 8, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 4, 9, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 9, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 28, 9, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 4, 10, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 10, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 28, 10, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 4, 11, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 11, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 28, 11, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 4, 12, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 12, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 28, 12, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 4, 13, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 13, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 28, 13, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 4, 14, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 14, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 28, 14, 11, 1, OB_NONE, OB_NONE},
             {OB_NONE, 2, 15, 13, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 15, 22, 1, OB_NONE, OB_NONE},
             {OB_NONE, 2, 16, 38, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 16, 22, 1, OB_NONE, OB_NONE},
             {OB_NONE, 2, 17, 13, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 17, 22, 1, OB_NONE, OB_NONE},
             {OB_NONE, 2, 18, 38, 1, OB_NONE, OB_NONE},
             {OB_NONE, 2, 19, 13, 1, OB_NONE, OB_NONE},
             {OB_NONE, 16, 19, 23, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 2, 21, 12, 1, TOB(TX_SPIELLISTE), OB_NONE},
             {OB_EXIT, 17, 21, 12, 1, TOB(TX_WEITER), OB_NONE},
             {OB_EXIT, 32, 21, 7, 1, OB_NONE, OB_NONE}}
}
#endif
;

EXTERN OBJECT diliste[3][66]
#ifdef XDIAL_C
    =
        {
            {{66, 0, 0, 38, 21, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 36, 1, TOB(TX_SPIELLISTE_T),
              OB_NONE},
             {OB_CENTERED, 2, 3, 10, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 12, 3, 10, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 22, 3, 10, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 2, 4, 10, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 12, 4, 10, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 22, 4, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 5, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 5, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 5, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 6, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 6, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 6, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 6, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 7, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 7, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 7, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 7, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 8, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 8, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 8, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 8, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 9, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 9, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 9, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 9, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 10, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 10, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 10, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 10, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 11, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 11, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 11, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 11, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 12, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 12, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 12, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 12, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 13, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 13, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 13, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 13, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 14, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 14, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 14, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 14, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 15, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 15, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 15, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 15, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 16, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 16, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 16, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 16, 7, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 1, 17, 8, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 9, 17, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 19, 17, 10, 1, OB_NONE, OB_NONE},
             {OB_RIGHT, 29, 17, 7, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 3, 18, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 13, 18, 9, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 23, 18, 9, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 2, 19, 8, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 11, 19, 5, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 17, 19, 10, 1, TOB(TX_WEITER), OB_NONE},
             {OB_EXIT, 28, 19, 8, 1, OB_NONE, OB_NONE}}
}
#endif
;

EXTERN OBJECT dioptions[3][25]
#ifdef XDIAL_C
    =
        {
            {{25, 0, 0, 38, 21, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 36, 1, TOB(TX_XSKAT), OB_NONE},
             {OB_EXIT, 2, 3, 34, 1, TOB(TX_COPYRIGHT), OB_NONE},
             {OB_NONE, 2, 5, 35, 1, TOB(TX_SORTIEREN), OB_NONE},
             {OB_BUTTON, 5, 6, 13, 1, TOB(TX_AUFWAERTS), 1},
             {OB_BUTTON, 20, 6, 13, 1, TOB(TX_ABWAERTS), -1},
             {OB_BUTTON, 5, 7, 13, 1, TOB(TX_ALTERNIEREND), 1},
             {OB_BUTTON, 20, 7, 13, 1, TOB(TX_SEQUENTIELL), -1},
             {OB_BUTTON, 5, 8, 13, 1, TOB(TX_NULL), 1},
             {OB_BUTTON, 20, 8, 13, 1, TOB(TX_NORMAL), -1},
             {OB_NONE, 2, 9, 35, 1, OB_NONE, OB_NONE},
             {OB_NONE, 2, 10, 35, 1, TOB(TX_GEREIZT_BIS_L), OB_NONE},
             {OB_NONE, 2, 11, 35, 1, TOB(TX_GESPIELT_WIRD), OB_NONE},
             {OB_NONE, 2, 12, 35, 1, TOB(TX_LETZTER_STICH), OB_NONE},
             {OB_NONE, 5, 13, 32, 1, OB_NONE, OB_NONE},
             {OB_NONE, 5, 14, 32, 1, OB_NONE, OB_NONE},
             {OB_NONE, 5, 15, 32, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 13, 15, 12, 1, TOB(TX_SCHENKEN), OB_NONE},
             {OB_EXIT, 8, 15, 22, 1, TOB(TX_MEHRSPIELER), OB_NONE},
             {OB_EXIT, 5, 17, 13, 1, TOB(TX_SPIELLISTE), OB_NONE},
             {OB_EXIT, 20, 17, 13, 1, TOB(TX_OPTIONEN), OB_NONE},
             {OB_EXIT, 5, 19, 13, 1, TOB(TX_ENDE), OB_NONE},
             {OB_EXIT, 20, 19, 13, 1, TOB(TX_WEITER), OB_NONE},
             {OB_HIDDEN, 1, 14, 36, 1, TOB(TX_INTRO1), OB_NONE},
             {OB_HIDDEN, 1, 15, 36, 1, TOB(TX_INTRO2), OB_NONE}}
}
#endif
;

EXTERN OBJECT dicopyr[3][11]
#ifdef XDIAL_C
    =
        {
            {{11, 0, 0, 40, 16, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 38, 1, TOB(TX_XSKAT), OB_NONE},
             {OB_CENTERED, 1, 3, 38, 1, TOB(TX_COPYRIGHT), OB_NONE},
             {OB_CENTERED, 1, 4, 38, 1, TOB(TX_URL), OB_NONE},
             {OB_CENTERED, 1, 6, 38, 1, TOB(TX_FR1), OB_NONE},
             {OB_CENTERED, 1, 7, 38, 1, TOB(TX_FR2), OB_NONE},
             {OB_CENTERED, 1, 8, 38, 1, TOB(TX_FR3), OB_NONE},
             {OB_CENTERED, 1, 9, 38, 1, TOB(TX_FR4), OB_NONE},
             {OB_CENTERED, 1, 11, 38, 1, TOB(TX_DOWNLOAD1), OB_NONE},
             {OB_CENTERED, 1, 12, 38, 1, TOB(TX_DOWNLOAD2), OB_NONE},
             {OB_EXIT, 13, 14, 14, 1, TOB(TX_WEITER), OB_NONE}}
}
#endif
;

EXTERN OBJECT dicopyralt[3][11]
#ifdef XDIAL_C
    =
        {
            {{11, 0, 0, 40, 16, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 38, 1, TOB(TX_XSKAT), OB_NONE},
             {OB_CENTERED, 1, 3, 38, 1, TOB(TX_COPYRIGHT), OB_NONE},
             {OB_CENTERED, 1, 4, 38, 1, TOB(TX_URL), OB_NONE},
             {OB_CENTERED, 1, 6, 38, 1, TOB(TX_FR3), OB_NONE},
             {OB_CENTERED, 1, 7, 38, 1, TOB(TX_FR4), OB_NONE},
             {OB_CENTERED, 1, 9, 38, 1, TOB(TX_ALT1), OB_NONE},
             {OB_CENTERED, 1, 10, 38, 1, TOB(TX_ALT2), OB_NONE},
             {OB_CENTERED, 1, 11, 38, 1, TOB(TX_ALT3), OB_NONE},
             {OB_CENTERED, 1, 12, 38, 1, TOB(TX_ALT4), OB_NONE},
             {OB_EXIT, 13, 14, 14, 1, TOB(TX_WEITER), OB_NONE}}
}
#endif
;

EXTERN OBJECT digrafik[3][14]
#ifdef XDIAL_C
    =
        {
            {{14, 0, 0, 40, 13, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 38, 1,
              TOB(TX_GRAFIK_UND_TEXT_T), OB_NONE},
             {OB_NONE, 2, 3, 10, 1, TOB(TX_BLATT), OB_NONE},
             {OB_EXIT, 2, 4, 23, 1, TOB(TX_FRANZOESISCH), 1},
             {OB_EXIT, 2, 5, 23, 1, TOB(TX_FRANZOESISCH_4_FARBEN), 1},
             {OB_EXIT, 2, 6, 23, 1, TOB(TX_DEUTSCH), 1},
             {OB_EXIT, 2, 7, 23, 1, TOB(TX_DEUTSCH_4_FARBEN), -3},
             {OB_NONE, 28, 3, 10, 1, TOB(TX_SPRACHE), OB_NONE},
             {OB_EXIT, 28, 4, 10, 1, TOB(TX_GERMAN), 1},
             {OB_EXIT, 28, 5, 10, 1, TOB(TX_ENGLISH), -1},
             {OB_NONE, 2, 9, 10, 1, TOB(TX_NAME), OB_NONE},
             {OB_EXIT, 10, 9, 11, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 22, 9, 11, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 13, 11, 14, 1, TOB(TX_WEITER), OB_NONE}}
}
#endif
;

EXTERN OBJECT distrateg[3][24]
#ifdef XDIAL_C
    =
        {
            {{24, 0, 0, 40, 14, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 38, 1, TOB(TX_COMPUTER_T),
              OB_NONE},
             {OB_NONE, 1, 3, 20, 1, TOB(TX_SPIELSTAERKE), OB_NONE},
             {OB_NONE, 2, 4, 9, 1, TOB(TX_LINKS), OB_NONE},
             {OB_BUTTON, 12, 4, 5, 1, TOB(TX_MM), 1},
             {OB_BUTTON, 17, 4, 5, 1, TOB(TX_M), 1},
             {OB_BUTTON, 22, 4, 5, 1, TOB(TX_0), 1},
             {OB_BUTTON, 27, 4, 5, 1, TOB(TX_P), 1},
             {OB_BUTTON, 32, 4, 5, 1, TOB(TX_PP), -4},
             {OB_NONE, 2, 5, 9, 1, TOB(TX_RECHTS), OB_NONE},
             {OB_BUTTON, 12, 5, 5, 1, TOB(TX_MM), 1},
             {OB_BUTTON, 17, 5, 5, 1, TOB(TX_M), 1},
             {OB_BUTTON, 22, 5, 5, 1, TOB(TX_0), 1},
             {OB_BUTTON, 27, 5, 5, 1, TOB(TX_P), 1},
             {OB_BUTTON, 32, 5, 5, 1, TOB(TX_PP), -4},
             {OB_NONE, 1, 7, 10, 1, TOB(TX_VORSCHLAEGE), OB_NONE},
             {OB_BUTTON, 12, 7, 8, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 20, 7, 8, 1, TOB(TX_JA), -1},
             {OB_NONE, 1, 9, 10, 1, TOB(TX_NAME), OB_NONE},
             {OB_EXIT, 12, 9, 11, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 26, 9, 11, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 12, 10, 11, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 26, 10, 11, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 13, 12, 14, 1, TOB(TX_WEITER), OB_NONE}}
}
#endif
;

EXTERN OBJECT divarianten[3][31]
#ifdef XDIAL_C
    =
        {
            {{31, 0, 0, 42, 14, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 40, 1, TOB(TX_VARIANTEN),
              OB_NONE},
             {OB_NONE, 1, 3, 20, 1, TOB(TX_RAMSCH_SPIELEN), OB_NONE},
             {OB_BUTTON, 17, 3, 7, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 24, 3, 7, 1, TOB(TX_JA), 1},
             {OB_BUTTON, 31, 3, 10, 1, TOB(TX_IMMER), -2},
             {OB_NONE, 1, 4, 20, 1, TOB(TX_KONTRA_SAGEN), OB_NONE},
             {OB_BUTTON, 17, 4, 7, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 24, 4, 7, 1, TOB(TX_JA), 1},
             {OB_BUTTON, 31, 4, 10, 1, TOB(TX_AB18), -2},
             {OB_NONE, 1, 5, 20, 1, TOB(TX_BOCK_RUNDEN), OB_NONE},
             {OB_BUTTON, 17, 5, 7, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 24, 5, 7, 1, TOB(TX_JA), 1},
             {OB_BUTTON, 31, 5, 10, 1, TOB(TX_UND_RAMSCH), -2},
             {OB_NONE, 1, 6, 18, 1, TOB(TX_SPITZE), OB_NONE},
             {OB_BUTTON, 17, 6, 7, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 24, 6, 7, 1, TOB(TX_JA), 1},
             {OB_BUTTON, 31, 6, 10, 1, TOB(TX_PLUS2), -2},
             {OB_NONE, 1, 7, 18, 1, TOB(TX_REVOLUTION), OB_NONE},
             {OB_BUTTON, 17, 7, 7, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 24, 7, 7, 1, TOB(TX_JA), -1},
             {OB_NONE, 1, 8, 18, 1, TOB(TX_KLOPFEN), OB_NONE},
             {OB_BUTTON, 17, 8, 7, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 24, 8, 7, 1, TOB(TX_JA), -1},
             {OB_NONE, 1, 9, 18, 1, TOB(TX_SCHENKEN), OB_NONE},
             {OB_BUTTON, 17, 9, 7, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 24, 9, 7, 1, TOB(TX_JA), -1},
             {OB_NONE, 1, 10, 18, 1, TOB(TX_ALTE_REGELN), OB_NONE},
             {OB_BUTTON, 17, 10, 7, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 24, 10, 7, 1, TOB(TX_JA), -1},
             {OB_EXIT, 14, 12, 14, 1, TOB(TX_WEITER), OB_NONE}}
}
#endif
;

EXTERN OBJECT diramschopts[3][9]
#ifdef XDIAL_C
    =
        {
            {{9, 0, 0, 42, 9, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 40, 1,
              TOB(TX_RAMSCH_VARIANTEN_T), OB_NONE},
             {OB_NONE, 1, 3, 20, 1, TOB(TX_SCHIEBERAMSCH), OB_NONE},
             {OB_BUTTON, 15, 3, 7, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 22, 3, 7, 1, TOB(TX_JA), -1},
             {OB_NONE, 1, 5, 20, 1, TOB(TX_SKAT_GEHT_AN), OB_NONE},
             {OB_BUTTON, 15, 5, 15, 1, TOB(TX_LETZTEN_STICH), 1},
             {OB_BUTTON, 30, 5, 11, 1, TOB(TX_VERLIERER), -1},
             {OB_EXIT, 14, 7, 14, 1, TOB(TX_WEITER), OB_NONE}}
}
#endif
;

EXTERN OBJECT dibockevents[3][14]
#ifdef XDIAL_C
    =
        {
            {{14, 0, 0, 42, 16, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 40, 1,
              TOB(TX_BOCK_EREIGNISSE_T), OB_NONE},
             {OB_BUTTON, 2, 3, 38, 1, TOB(TX_VERLOREN_MIT_60), OB_NONE},
             {OB_BUTTON, 2, 4, 38, 1, TOB(TX_GRAND_HAND_GEWONNEN), OB_NONE},
             {OB_BUTTON, 2, 5, 38, 1, TOB(TX_ERFOLGREICHER_KONTRA), OB_NONE},
             {OB_BUTTON, 2, 6, 38, 1, TOB(TX_KONTRA_RE_ANGESAGT), OB_NONE},
             {OB_BUTTON, 2, 7, 38, 1, TOB(TX_NNN_IN_SPIELLISTE), OB_NONE},
             {OB_BUTTON, 2, 8, 38, 1, TOB(TX_N00_IN_SPIELLISTE), OB_NONE},
             {OB_BUTTON, 2, 9, 38, 1, TOB(TX_SPIELWERT_72), OB_NONE},
             {OB_BUTTON, 2, 10, 38, 1, TOB(TX_SPIELWERT_96), OB_NONE},
             {OB_NONE, 3, 12, 22, 1, TOB(TX_FORTSETZEN), OB_NONE},
             {OB_BUTTON, 26, 12, 7, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 33, 12, 7, 1, TOB(TX_JA), -1},
             {OB_EXIT, 14, 14, 14, 1, TOB(TX_WEITER), OB_NONE}}
}
#endif
;

EXTERN OBJECT digeschwindigkeit[3][18]
#ifdef XDIAL_C
    =
        {
            {{18, 0, 0, 33, 15, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 31, 1, TOB(TX_GESCHWINDIGKEIT),
              OB_NONE},
             {OB_CENTERED, 1, 3, 31, 1, TOB(TX_NIMM_STICH_NACH), OB_NONE},
             {OB_CENTERED, 1, 4, 31, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 2, 5, 4, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 7, 5, 4, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 12, 5, 4, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 17, 5, 4, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 22, 5, 4, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 27, 5, 4, 1, OB_NONE, OB_NONE},
             {OB_CENTERED, 1, 7, 31, 1, TOB(TX_GEBEN), OB_NONE},
             {OB_BUTTON, 2, 8, 14, 1, TOB(TX_SCHNELL), 1},
             {OB_BUTTON, 17, 8, 14, 1, TOB(TX_LANGSAM), -1},
             {OB_CENTERED, 1, 10, 31, 1, TOB(TX_ABKUERZUNG), OB_NONE},
             {OB_BUTTON, 2, 11, 9, 1, TOB(TX_NIE), 1},
             {OB_BUTTON, 12, 11, 9, 1, TOB(TX_FRAGEN), 1},
             {OB_BUTTON, 22, 11, 9, 1, TOB(TX_IMMER), -2},
             {OB_EXIT, 10, 13, 13, 1, TOB(TX_WEITER), OB_NONE}}
}
#endif
;

EXTERN OBJECT dimehrspieler[]
#ifdef XDIAL_C
    =
        {
            {6,                           0,  0, 38, 11, OB_NONE,             OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 36, 1,  TOB(TX_MEHRSPIELER),
             OB_NONE                                                                 },
            {OB_EXIT,                     2,  3, 34, 1,  TOB(TX_LAN_T),       OB_NONE},
            {OB_EXIT,                     2,  5, 34, 1,  TOB(TX_IRC_T),       OB_NONE},
            {OB_EXIT,                     9,  7, 20, 1,  TOB(TX_MAN_XSKAT),   OB_NONE},
            {OB_EXIT,                     12, 9, 14, 1,  TOB(TX_WEITER),      OB_NONE}
}
#endif
;

EXTERN OBJECT dilanspiel[]
#ifdef XDIAL_C
    =
        {
            {5,                           0,  0, 38, 9, OB_NONE,               OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 36, 1, TOB(TX_LAN_T),         OB_NONE},
            {OB_EXIT,                     2,  3, 34, 1, TOB(TX_EIGENER_TISCH), OB_NONE},
            {OB_EXIT,                     2,  5, 34, 1, TOB(TX_ANDERER_TISCH), OB_NONE},
            {OB_EXIT,                     12, 7, 14, 1, TOB(TX_ZURUECK),       OB_NONE}
}
#endif
;

EXTERN OBJECT dieigenertisch[]
#ifdef XDIAL_C
    =
        {
            {14,                          0,  0,  40, 15, OB_NONE,               OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1,  38, 1,  TOB(TX_LAN_T),         OB_NONE},
            {OB_NONE,                     2,  3,  22, 1,  TOB(TX_SPIELER_2),     OB_NONE},
            {OB_BUTTON,                   28, 3,  5,  1,  TOB(TX_JA),            1      },
            {OB_BUTTON,                   33, 3,  5,  1,  TOB(TX_NEIN),          -1     },
            {OB_NONE,                     2,  4,  36, 1,  TOB(TX_RECHNER_IP),    OB_NONE},
            {OB_EXIT,                     2,  5,  36, 1,  OB_NONE,               OB_NONE},
            {OB_NONE,                     2,  7,  22, 1,  TOB(TX_SPIELER_3),     OB_NONE},
            {OB_BUTTON,                   28, 7,  5,  1,  TOB(TX_JA),            1      },
            {OB_BUTTON,                   33, 7,  5,  1,  TOB(TX_NEIN),          -1     },
            {OB_NONE,                     2,  8,  36, 1,  TOB(TX_RECHNER_IP),    OB_NONE},
            {OB_EXIT,                     2,  9,  36, 1,  OB_NONE,               OB_NONE},
            {OB_EXIT,                     7,  11, 26, 1,  TOB(TX_TISCH_OEFFNEN), OB_NONE},
            {OB_EXIT,                     13, 13, 14, 1,  TOB(TX_ZURUECK),       OB_NONE}
}
#endif
;

EXTERN OBJECT dianderertisch[]
#ifdef XDIAL_C
    =
        {
            {11,                          0,  0,  40, 16, OB_NONE,                   OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1,  38, 1,  TOB(TX_LAN_T),             OB_NONE},
            {OB_NONE,                     2,  3,  22, 1,  TOB(TX_TISCH),             OB_NONE},
            {OB_NONE,                     2,  4,  36, 1,  TOB(TX_RECHNER_IP),        OB_NONE},
            {OB_EXIT,                     2,  5,  36, 1,  OB_NONE,                   OB_NONE},
            {OB_CENTERED,                 2,  7,  36, 1,  TOB(TX_ZUGRIFF_1),         OB_NONE},
            {OB_CENTERED,                 2,  8,  36, 1,  TOB(TX_ZUGRIFF_2),         OB_NONE},
            {OB_EXIT,                     10, 9,  20, 1,  TOB(TX_MAN_XHOST),         OB_NONE},
            {OB_CENTERED,                 2,  12, 36, 1,  TOB(TX_SCHLIESST_FENSTER), OB_NONE},
            {OB_EXIT,                     7,  11, 26, 1,  TOB(TX_PLATZ_NEHMEN),      OB_NONE},
            {OB_EXIT,                     13, 14, 14, 1,  TOB(TX_ZURUECK),           OB_NONE}
}
#endif
;

EXTERN OBJECT diwarteauf[]
#ifdef XDIAL_C
    =
        {
            {5,                           0,  0, 38, 8, OB_NONE,         OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1, 36, 1, TOB(TX_LAN_T),   OB_NONE},
            {OB_CENTERED,                 2,  3, 34, 1, OB_NONE,         OB_NONE},
            {OB_CENTERED,                 2,  4, 34, 1, OB_NONE,         OB_NONE},
            {OB_EXIT,                     12, 6, 14, 1, TOB(TX_ZURUECK), OB_NONE}
}
#endif
;

EXTERN OBJECT diirc[]
#ifdef XDIAL_C
    =
        {
            {8,                           0,  0,  40, 13, OB_NONE,                           OB_NONE},
            {OB_CENTERED | OB_UNDERLINED, 1,  1,  38, 1,  TOB(TX_IRC_T),                     OB_NONE},
            {OB_CENTERED,                 1,  3,  38, 1,  TOB(TX_IRC_VERBINDUNG_HERSTELLEN),
             OB_NONE                                                                                },
            {OB_EXIT,                     2,  4,  36, 1,  OB_NONE,                           OB_NONE},
            {OB_EXIT,                     13, 6,  14, 1,  TOB(TX_START),                     OB_NONE},
            {OB_CENTERED,                 1,  8,  38, 1,  TOB(TX_IRC_KONFIGURATION_SIEHE),
             OB_NONE                                                                                },
            {OB_EXIT,                     13, 9,  14, 1,  TOB(TX_MAN_XSKAT),                 OB_NONE},
            {OB_EXIT,                     13, 11, 14, 1,  TOB(TX_ZURUECK),                   OB_NONE}
}
#endif
;

EXTERN OBJECT digui[3][20]
#ifdef XDIAL_C
    =
        {
            {{20, 0, 0, 42, 17, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 40, 1,
              TOB(TX_BENUTZEROBERFLAECHE), OB_NONE},
             {OB_CENTERED, 1, 3, 40, 1, TOB(TX_MENU_BUTTON), OB_NONE},
             {OB_BUTTON, 3, 4, 7, 1, TOB(TX_JEDER), 1},
             {OB_BUTTON, 11, 4, 4, 1, OB_NONE, 1},
             {OB_BUTTON, 16, 4, 4, 1, OB_NONE, 1},
             {OB_BUTTON, 21, 4, 4, 1, OB_NONE, 1},
             {OB_BUTTON, 26, 4, 4, 1, OB_NONE, 1},
             {OB_BUTTON, 31, 4, 4, 1, OB_NONE, -5},
             {OB_CENTERED, 1, 6, 40, 1, TOB(TX_TASTATUR), OB_NONE},
             {OB_BUTTON, 3, 7, 10, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 14, 7, 10, 1, TOB(TX_JA), 1},
             {OB_BUTTON, 25, 7, 10, 1, TOB(TX_IMMER), -2},
             {OB_CENTERED, 1, 9, 40, 1, TOB(TX_WENIG_HINWEISE), OB_NONE},
             {OB_BUTTON, 3, 10, 10, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 14, 10, 10, 1, TOB(TX_JA), -1},
             {OB_CENTERED, 1, 12, 40, 1,
              TOB(TX_STICH_KARTEN_VON_LINKS_NACH_RECHTS), OB_NONE},
             {OB_BUTTON, 3, 13, 10, 1, TOB(TX_NEIN), 1},
             {OB_BUTTON, 14, 13, 10, 1, TOB(TX_JA), -1},
             {OB_EXIT, 14, 15, 14, 1, TOB(TX_WEITER), OB_NONE}}
}
#endif
;

EXTERN OBJECT diinput[3][5]
#ifdef XDIAL_C
    =
        {
            {{5, 0, 0, 40, 7, OB_NONE, OB_NONE},
             {OB_CENTERED | OB_UNDERLINED, 1, 1, 38, 1, OB_NONE, OB_NONE},
             {OB_NONE, 2, 3, 36, 1, OB_NONE, OB_NONE},
             {OB_EXIT, 2, 5, 10, 1, TOB(TX_LOESCHEN), OB_NONE},
             {OB_EXIT, 28, 5, 10, 1, TOB(TX_FERTIG), OB_NONE}}
}
#endif
;

extern int ismemb();
extern void init_di();
extern void init_dials();
extern void prverz();
extern int ob_disabled();
extern void cleanip();
extern void cleanirchost();
extern void cleanname();
extern void hndl_btevent();
extern void button_press();
extern void draw_wedge();
extern void draw_actbtn();
extern void draw_selpos();
extern void new_selpos();
extern void new_actbtn();
extern void set_selpos();
extern void del_selpos();
extern void manpage();
extern void polldisps();
extern void hndl_events();
extern void getob_xywhbd();
extern void create_dial();
extern void findlastex();
extern void create_di();
extern void create_diopt();
extern void remove_dial();
extern void remove_di();
extern void draw_3d();
extern void draw_dial();
extern void draw_di();
extern void refresh();
extern void prspnam();
extern void di_info();
extern void di_hand();
extern void next_grandhand();
extern void di_grandhand();
extern void di_term();
extern void di_ende();
extern void di_loesch();
extern void di_ansage();
extern void di_kontra();
extern void di_rekontra();
extern void di_konre();
extern void di_ktrnext();
extern void di_dicht();
extern void di_weiter();
extern void di_wiederweiter();
extern void di_klopfen();
extern void di_schenken();
extern void di_geschenkt();
extern void di_wiederschenken();
extern void di_nichtschenken();
extern void di_schieben();
extern int di_verdoppelt();
extern void di_buben();
extern void di_spiel();
extern void list_fun();
extern void di_delliste();
extern void di_liste();
extern int ger_toupper();
extern void pformat();
extern void prot_fun();
extern void im_skat();
extern void di_proto();
extern void di_resultdi();
extern void di_result();
extern void di_delres();
extern void di_options();
extern void di_copyr();
extern void di_grafik();
extern void di_strateg();
extern void di_varianten();
extern void di_ramschopts();
extern void di_bockevents();
extern void di_geschwindigkeit();
extern void di_mehrspieler();
extern void di_lanspiel();
extern void di_eigenertisch();
extern void di_anderertisch();
extern void di_warteauf();
extern void di_irc();
extern void di_eingabe();
extern void di_wieder();
extern void di_input();

#endif /* XDIAL_H */
