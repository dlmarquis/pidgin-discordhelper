NSIS_PATH=`cygpath -u "c:\\Program Files\\NSIS"`

all:
	PATH="$$PATH:$(NSIS_PATH)" makensis.exe discordhelper.nsi

clean:
	rm -f discordhelper.exe discordhelper.dll
