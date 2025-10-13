
/*
    xskat - a card game for 1 to 3 players.
    Copyright (C) 2000  Gunter Gerhardt

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

#ifndef IRC_H
#define IRC_H

#include <sys/types.h>

#undef EXTERN
#ifdef IRC_C
#define EXTERN
#else
#define EXTERN extern
#endif

#define IRC_NICK_LEN 30

enum { IRC_OFFLINE, IRC_TALK, IRC_SERVER, IRC_PLAYING };

EXTERN pid_t irc_telnetpid;
EXTERN int irc_i, irc_o;
EXTERN int irc_state, irc_clients;
EXTERN int irc_play;
EXTERN int irc_2player, irc_pos;
EXTERN int irc_port;
EXTERN int irc_bell;
EXTERN int irc_logappend;
EXTERN int irc_histidx[3], irc_histcnt[3];
EXTERN int irc_inplen;
EXTERN long irc_tick;
EXTERN char *irc_telnet, *irc_host, *irc_channel;
EXTERN char *irc_nick, *irc_user, *irc_realname;
EXTERN char* irc_logfile;
EXTERN char* irc_history[3][100];
EXTERN char irc_substr[100];
EXTERN char irc_inpbuf[1024];
EXTERN struct {
  char nick[IRC_NICK_LEN + 1];
  int sort1, alternate, large;
  int nimmstich, pos, abkuerz;
  char spnames[2][10];
} irc_conf[3];
EXTERN char irc_defaulthost[]
#ifdef IRC_C
    = DEFAULT_IRC_SERVER
#endif
    ;

extern void irc_log();
extern void irc_out();
extern void irc_print();
extern void irc_printnl();
extern char* irc_getline();
extern int irc_xinput(char* s, int l);
extern int irc_match();
extern void irc_sendnick();
extern void irc_pr_ss();
extern void irc_pr_bs();
extern void irc_pr_sd();
extern void irc_pr_ramsch();
extern void irc_pr_sramsch();
extern void irc_pr_rskatloser();
extern void irc_pr_kontra();
extern void irc_pr_bock();
extern void irc_pr_resumebock();
extern void irc_pr_spitze();
extern void irc_pr_revolution();
extern void irc_pr_klopfen();
extern void irc_pr_schenken();
extern void irc_pr_oldrules();
extern void irc_pr_bockevents();
extern void irc_pr_alist();
extern void irc_pr_start();
extern void irc_pr_s1();
extern void irc_sendrules();
extern void irc_incidx();
extern void irc_sync();
extern void irc_sendsync();
extern void irc_checksync();
extern void irc_alarm();
extern void irc_talk(char* msg);
extern char* irc_copyname();
extern int irc_senderok();
extern void irc_histsave();
extern void irc_sendbtev(int sn, int bt);
extern void irc_sendxyev(int sn, int x, int y, int opt);
extern void irc_sendsort(int sn);
extern void irc_sendschenken(int sn);
extern void irc_sendloeschen(int sn);
extern void irc_addcmd();
extern int irc_getcmd();
extern void irc_checkhist();
extern void irc_getrules();
extern void irc_getserverconf();
extern void irc_putserverconf();
extern void irc_putclientconf();
extern void irc_setpos();
extern void irc_getclientconf();
extern void irc_changenick(int send);
extern void irc_checknick();
extern void irc_nickchanged();
extern void irc_msg();
extern void irc_parse(char* s);
extern void irc_connect();
extern void irc_init();

#endif /* IRC_H */
