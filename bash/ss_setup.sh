#! /usr/bin/env bash

if [ $1 = ubuntu ]; then
	apt-get update
	echo y|apt-get install python-pip
	pip install shadowsocks
fi

if [ $1 = centos ]; then
	yum install python-setuptools && easy_install pip
	pip install shadowsocks
fi


ipaddress=$(ifconfig eth0 | grep "inet addr" | cut -d ':' -f 2 | cut -d ' ' -f 1)

cat  <<EOF > /etc/shadowsocks.json
{
    "server":"$ipaddress",
	"local_address": "127.0.0.1",
	"local_port":1080,
	"port_password": {
		"8388": "boom123456",
		"8382": "TxVD980Xv",
		"8383": "foobar3",
		"8384": "foobar4"
	},
	"timeout":300,
	"method":"aes-256-cfb",
	"fast_open": false
}
EOF

ssserver -c /etc/shadowsocks.json -d start


