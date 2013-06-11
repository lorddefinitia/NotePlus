NotePlus
========

Notepad++ for Linux

Compiles (32-bit)

Does not (seem to) run correctly.

License
=====
This code is a fork of Don HR's excellent Notepad++ for Windows. As such, original copyrights are his, code licensed under the GPL.

As of now, original images etc. are kept with the code for simplicity; if future objections are made I am happy to author my own images. :)

Based on Notepad++ 6.3.3

Prerequisites
=====

- wine (32bit)
- wine-dev (32bit)
- g++ (make sure you have the 32 bit compiler tool chain and libraries)
- make
- scintilla

Roadmap
=====

- Get UI running
- Remove as many warnings as possible
- Abstract/port as many w32 api call away as possible
- Work on a Qt UI port.


Building
=====

cd to the visual.net directory under PowerEditor, and type 

`./makeit`

Running
=====

Once you have successfully built the exe, copy both notepad++.exe and notepad++.exe.so to a 32bit wine prefix, run:

`./notepad++.exe`

To debug, you can try

`WINEDEBUG=warn+all wine ./notepad++.exe.so`

or

`winedbg --gdb ./notepad++.exe.so`


