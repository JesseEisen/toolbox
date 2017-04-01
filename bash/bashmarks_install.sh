#!/usr/bin/env  bash

#bashmarks allow you to save and jump to commonly used directoires

git clone git://github.com/huyng/bashmarks.git
cd bashmarks
make install
echo "source ~/.local/bin/bashmarks.sh" >> ~/.bashrc
source ~/.bashrc

cd ..
rm -rf bashmarks
echo "install finished !"
echo -e "==============HIH~=================\n"
