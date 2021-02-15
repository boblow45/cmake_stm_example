#!/bin/bash 

# Install tools to compile code
sudo apt-get install gcc-arm-none-eabi binutils-arm-none-eabi openocd

# will install arm gdb and can be accessed using the following
# arm-none-eabi-gdb
sudo apt install gdb-multiarch
ln -s /usr/bin/gdb-multiarch /usr/bin/arm-none-eabi-gdb

# install cpputest 
sudo apt-get install -y cpputest

# install gcov 
sudo apt-get install -y gcovr
