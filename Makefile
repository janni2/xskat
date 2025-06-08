
#   xskat - a card game for 1 to 3 players.
#   Copyright (C) 2000  Gunter Gerhardt
#
#   This program is free software; you can redistribute it freely.
#   Use it at your own risk; there is NO WARRANTY.
#
#   Redistribution of modified versions is permitted
#   provided that the following conditions are met:
#   1. All copyright & permission notices are preserved.
#   2.a) Only changes required for packaging or porting are made.
#     or
#   2.b) It is clearly stated who last changed the program.
#        The program is renamed or
#        the version number is of the form x.y.z,
#        where x.y is the version of the original program
#        and z is an arbitrary suffix.

CFLAGS	=
LDFLAGS	= -L/usr/X11R6/lib -lX11
# perhaps you need one of: -lsocket -lnsl

#DEFL    = -DDEFAULT_LANGUAGE=\"german\"
DEFL   = -DDEFAULT_LANGUAGE=\"english\"

DEFI    = -DDEFAULT_IRC_SERVER=\"irc.fu-berlin.de\"

OBJECTS	= skat.o ramsch.o null.o bitmaps.o xio.o xdial.o irc.o text.o

xskat: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	rm -f $(OBJECTS) xskat

text.o: text.c text.h
	$(CC) $(CFLAGS) $(DEFL) -c $< -o $@

irc.o: irc.c irc.h skat.h xio.h xdial.h text.h
	$(CC) $(CFLAGS) $(DEFI) -c $< -o $@

skat.o: skat.h text.h
null.o: null.h skat.h
ramsch.o: ramsch.h skat.h
xio.o: xio.h skat.h bitmaps.h irc.h text.h
xdial.o: xdial.h xio.h skat.h ramsch.h irc.h text.h
bitmaps.o: bitmaps.h symbs.xbm symbl.xbm icon.xbm cards.c
