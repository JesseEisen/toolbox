#!/usr/bin/env bash

#Copyright (c) 2016 J.C.  <lkchan0719@gmail.com> 


# This is a script to install some basic tools
# the recommend way to run this script is :
#
# 	sudo  sh install_basics_centos.sh
# 
# To add new install in it, you can use
#
# message_title 'xxxx'
# [install command]  - if not the package manager may need to check
# wait
#
# more can refer the next code.



# Reset color
RS="\e[0m"
# Basic Colors
BLACK="\e[0;30m"
RED="\e[0;31m"
GREEN="\e[0;32m"
YELLOW="\e[0;33m"
BLUE="\e[0;34m"
PURPLE="\e[0;35m"
CYAN="\e[0;36m"
WHITE="\e[0;37m"

message_title () {
  echo -e "${CYAN}"
  echo -e "# | ::::::::::::::::::::::::::::::::::::::::::::: | #"
  echo -e "# |      ${RS} $1 ${CYAN}"
  echo -e "# | ::::::::::::::::::::::::::::::::::::::::::::: | #"
  echo -e "${RS}"
}

check_install () {
    type -P "$1" &>/dev/null && echo -e  "- Installed - ${GREEN} Ok ${RS} - $1" || echo -e  "- Install - ${RED} No ${RS} - $1"
}

Alread_install() {
	echo -e "${RED}"
	echo -e "############   $1  is installed  #############"
	echo -e "${RS}"
}

if [ "$1"  = ubuntu ]; then
	pkg_manager="apt-get"
else
	pkg_manager="yum"
fi

message_title '- **Tree**'
"$pkg_manager" -y install tree
wait

message_title '- **GCC**'
"$pkg_manager" -y install gcc
wait

message_title '- **Lsb_release**'
if [ $pkg_manager = yum ]; then
	"$pkg_manager" -y install redhat-lsb-core
else
	"$pkg_manager" -y install lsb_release
fi
wait

# this will install git 2.11.0
message_title '- **Git**'
type -P  git &>/dev/null 
if [ $? -ne 0 ]; then
	"$pkg_manager" -y install curl-devel expat-devel gettext-devel \
		    openssl-devel zlib-devel
	"$pkg_manager" -y install asciidoc xmlto docbook2x
	wget -c https://github.com/git/git/archive/v2.11.0.tar.gz
	tar -zxf v2.11.0.tar.gz
	cd git-2.11.0
	make configure
	./configure --prefix=/usr
	make all doc info
	sudo make install install-doc install-html install-info
	cd ..; rm -rf v2.11.0.tar.gz; rm -rf git-2.11.0;
else
	Alread_install 'GIT'
fi
wait

message_title '- **Git-extras**'
which git-extras &>/dev/null
if  [ $? -ne 0 ]; then
	git clone https://github.com/tj/git-extras.git
	cd git-extras
	git checkout $(git describe --tags $(git rev-list --tags --max-count=1))
	make install
	cd ..
	rm -rf git-extras
else
	Alread_install 'Git-extras'
fi
wait

message_title '- **Ruby**'
cd
git clone https://github.com/rbenv/rbenv.git ~/.rbenv
echo 'export PATH="$HOME/.rbenv/bin:$PATH"' >> ~/.bashrc
echo 'eval "$(rbenv init -)"' >> ~/.bashrc
exec $SHELL

git clone https://github.com/rbenv/ruby-build.git ~/.rbenv/plugins/ruby-build
echo 'export PATH="$HOME/.rbenv/plugins/ruby-build/bin:$PATH"' >> ~/.bashrc
exec $SHELL

rbenv install 2.4.0
rbenv global 2.4.0
gem install bundler
wait


check_install tree
check_install gcc
check_install lsb_release
check_install git
check_install git-extras
check_install ruby
