#!/bin/bash 

# Install tools to compile code
sudo apt-get install gcc-arm-none-eabi binutils-arm-none-eabi openocd -y

wget https://www.segger.com/downloads/jlink/JLink_Linux_V698b_x86_64.deb
sudo dpkg -i JLink*.deb
rm JLink*.deb

# will install arm gdb and can be accessed using the following
# arm-none-eabi-gdb
sudo apt install gdb-multiarch
ln -s /usr/bin/gdb-multiarch /usr/bin/arm-none-eabi-gdb

# install cpputest 
sudo apt-get install -y cpputest

# install gcov 
sudo apt-get install -y gcovr

# install google mock
sudo apt-get install -y google-mock
