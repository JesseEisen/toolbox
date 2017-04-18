install:
	mkdir ~/.mad && mkdir ~/.mad/share
	cp -f mad ~/.mad/mad
	cp -f mad.config ~/.mad/mad.config
	cp -f mad.md ~/.mad/share/mad.md
	echo "export PATH=~/.mad:$PATH" >> ~/.bashrc

uninstall:
	rm -rf ~/.mad

.PHONY: install unisntall
    	
