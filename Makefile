# Change this to the path where your pidgin source tree is:
PIDGIN_SRCDIR=~/pidgin-2.14.1/pidgin

# Comment this out and uncomment the next if you are not building on Windows.
# Note that on windows, you need to build pidgin fully using 'make -f
# Makefile.mingw'. On unix you can get away with just running ./configure.
#PLATFORM = win32
#PLATFORM = unix

# If this doesn't work, you'll have to set it manually to the path where
# pidgin installs.  To find where that is, type "which pidgin", and remove the
# "bin/pidgin" at the end of the output.
PIDGIN_INSTALLPREFIX=`grep ^prefix $(PIDGIN_SRCDIR)/Makefile | sed -e 's,[^/]*,,'`

# You shouldn't need to change this.
#PIDGIN_LIBDIR=$(PIDGIN_INSTALLPREFIX)/lib/pidgin
PIDGIN_LIBDIR=~/.purple/plugins
PIDGIN_PLUGINDIR=$(PIDGIN_SRCDIR)/plugins

VERSION = 2.6.5-1

ifeq ($(PLATFORM), win32)
MAKEARGS = -f Makefile.mingw
PLUGIN = discordhelper.dll
else
MAKEARGS =
PLUGIN = discordhelper.so
endif

DISTFILES=\
COPYING \
INSTALL \
Makefile \
discordhelper.c \
win32

all: $(PLUGIN)

$(PLUGIN): discordhelper.c
	cp discordhelper.c $(PIDGIN_PLUGINDIR)/
	make -C $(PIDGIN_PLUGINDIR) $(MAKEARGS) $(PLUGIN)
	cp -a $(PIDGIN_PLUGINDIR)/$(PLUGIN) .

install: all
	cp $(PIDGIN_PLUGINDIR)/$(PLUGIN) $(PIDGIN_LIBDIR)

uninstall: all
	rm $(PIDGIN_LIBDIR)/discordhelper.so

win32: all
	cp $(PIDGIN_PLUGINDIR)/$(PLUGIN) win32
	make -C win32

dist:
	rm -rf discordhelper-$(VERSION)
	mkdir discordhelper-$(VERSION)
	cp -a $(DISTFILES) discordhelper-$(VERSION)
	make -C discordhelper-$(VERSION) clean
	tar czf discordhelper-$(VERSION).tar.gz discordhelper-$(VERSION)
	rm -rf discordhelper-$(VERSION)

clean:
	make -C win32 clean
	rm -f $(PIDGIN_PLUGINDIR)/$(PLUGIN)
