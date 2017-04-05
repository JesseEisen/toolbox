#!/usr/bin/env bash

#There are three ways to install tmux, chose the best way to install
#./tmux_install [1|2|3] 

#first use the official deb package to install
if [ "$1" -eq 1 ]; then
   echo y |sudo apt-get install tmux
   exit 0
fi

#compile from source code

######################################
#         install libeventn2         #
######################################

if [ "$1" -eq 2 ]; then
    echo y |sudo apt-get install libevent-dev
    echo -e "\n===================libevnet install finished!====================\n"
    echo -e "\n===================start to install tmux by git!=================\n"
    git clone https://github.com/tmux/tmux.git
    cd tmux
    sh autogen.sh
    ./configure && make
    sudo mv tmux /usr/bin/local/
    if  [ ! -d /usr/local/share/man/man1 ]; then
        sudo mkdir /usr/local/share/man/man1
    fi
    sudo mv tmux.1 /usr/local/share/man/man1/
    echo -e "\n======================tmux install finished =======================\n"
    tmux -V
fi

# use ppa to install tmux 2.0

if [ "$1" -eq 3 ]; then
  sudo apt-get update
  sudo apt-get install -y python-software-properties software-properties-common
  sudo add-apt-repository -y ppa:pi-rho/dev
  sudo apt-get update
  sudo apt-get install -y tmux
  tmux -V
fi

