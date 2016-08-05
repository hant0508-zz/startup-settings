all:
	make -C src/ -s release

install:
	cp startup-settings /usr/bin/
	cp src/startup-settings.desktop /usr/share/applications/
	mkdir -p /usr/share/startup-settings/
	cp src/gui.glade /usr/share/startup-settings/
	chmod -R 755 /usr/share/startup-settings/

uninstall:
	rm -f /usr/bin/startup-settings
	rm -f /usr/share/startup-settings/gui.glade
	rm -f /usr/share/applications/startup-settings.desktop
