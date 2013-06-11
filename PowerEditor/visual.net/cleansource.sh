#!/bin/bash

cd ../../

#make clean copy from backup directory

cp -R second/PowerEditor/ .

cd PowerEditor

#remove old base files
find . -iname '*.base' | xargs rm

#run filename lowering

./lowercase.sh h
./lowercase.sh cpp
./lowercase.sh ico
./lowercase.sh bmp

#lower includes
find . -iname '*.cpp' | xargs perl -0pi -e 's/#include "([^"]+)"/#include "\L$1\E"/g'
find . -iname '*.cxx' | xargs perl -0pi -e 's/#include "([^"]+)"/#include "\L$1\E"/g'
find . -iname '*.rc' | xargs perl -0pi -e 's/#include "([^"]+)"/#include "\L$1\E"/g'

#extract source code
find . -iname "*.h" | xargs ./visual.net/findclassmethods.pl

cd visual.net

#and run winemaker
/usr/bin/winemaker --nomsvcrt --lower-all --windows --guiexe -icomdlg32 -ishell32 -ishlwapi -iuser32 -igdi32 -iadvapi32 notepadplus.vcproj
