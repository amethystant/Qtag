Qtag is a new cross-platform Qt-based application for editing audio tags. 
It is licensed under the Mozzila Public License v2.0. ( https://www.mozilla.org/MPL/2.0/index.txt )


**Linux:**
I currently work on an RPM and DEB package.
If you want to compile it right now, install Qt 5 and TagLib (and obviously GNU G++ and Git) and open a command line:
$git clone http://www.github.com/amethystAnt/Qtag.git
$cd Qtag/src
$qmake #on Fedora, it might be qmake-qt5 instead
$make
$./Qtag

**Windows:**
Download the Windows installer from here: 
https://github.com/amethystAnt/Qtag-installer/releases/download/0.1-1/Qtag-install.exe

If you'd like to compile it on *BSD or OS X, do it on your own.
