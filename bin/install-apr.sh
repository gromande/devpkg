#!/bin/bash
set -e

#Download source
cd /tmp
curl -L -O http://archive.apache.org/dist/apr/apr-1.5.2.tar.gz

#Extract
tar xvfz apr-1.5.2.tar.gz
cd apr-1.5.2

#configure, make, install
./configure
make
sudo make install

#reset and cleanup
cd /tmp
rm -rf apr-1.5.2 apr-1.5.2.tar.gz

#Do the same with apr-util
curl -L -O http://archive.apache.org/dist/apr/apr-util-1.5.4.tar.gz

#Extract
tar xvfz apr-util-1.5.4.tar.gz
cd apr-util-1.5.4

#configure, make, install
./configure --with-apr=/usr/local/apr
make
sudo make install

#reset and cleanup
cd /tmp
rm -rf apr-util-1.5.4 apr-util-1.5.4.tar.gz
