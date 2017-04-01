#! /usr/bin/env bash

# usage:  create_new [centos|ubuntu]


read -p "Username:" name

if [ -z "$name" ]; then
   echo "username is empty"
   exit 1
fi

groupadd -g 1234 pikachu
useradd -d /home/"$name" -g 1234 -m -s /bin/bash "$name"

if [ $? -eq 0 ]; then
   echo "Now set your password~"
   passwd "$name"
fi

echo "user create finished!"

if [[ $1 = ubuntu ]]; then
	usermod -aG sudo "$name"
	echo "user add to sudo"
fi

if [[ $1 = centos ]]; then
	usermod -aG wheel "$name"
	cp /etc/sudoers /etc/sudoers_tmp
	chmod 666 /etc/sudoers
	sed "/root	ALL/ a$name  ALL=(ALL) ALL" -i /etc/sudoers
	if [ $? -eq 0 ]; then
		chmod 200 /etc/sudoers 
		rm /etc/sudoers_tmp
	fi
fi

