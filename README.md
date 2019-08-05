# PetSynth
Restoration of the PetSynth software created by Chiron Bramberger used on the Commodore PET to play music.

Inspired by LOOK MUM NO COMPUTER https://www.youtube.com/watch?v=vysJEpKIVkU

*Help out if you have experience programming C/Assembly/BASIC or would like to learn!*

## Files downloaded from the archived website:
https://web.archive.org/web/20110727173412/http://www.petsynth.org/downloads_source/


### Installing the Commodore Emulator (VICE):
http://vice-emu.sourceforge.net/

You can use the emulators to upload .prc files and play sounds using PetSynth. Very useful for debugging.

#### Linux (Debian):
```sh
sudo apt-get install libsdl2-dev mawk make
cd ./confiure && make install
```
If you have an error regarding tmp files, add "-pipe" to the CFLAGS in the Makefile after running ./configure or use the Makefile supplied in the VICE directory above.
```
CFLAGS = -pipe -g -O2 -I/usr/include/SDL2 -D_REENTRANT -g -O3 -march=native -Wstrict-prototypes -Wall -W -Wno-unused-parameter  -Wno-sign-compare -Wmissing-prototypes -Werror=implicit-function-declaration -Wfatal-errors -Wshadow
```
#### Windows:
https://vice.pokefinder.org/

https://www.youtube.com/watch?v=-zfe0BKZxuQ


### Commodore Pet Web-Based GUI Emulator:
https://www.masswerk.at/pet/

## Compiler for the Commodore PET:
Linux (Debian):
```sh
$ sudo apt-get install cc65
```
or
```sh
$ git clone https://github.com/cc65/cc65.git
$ cd cc65
$ make
```
Windows:
https://sourceforge.net/projects/cc65/files/cc65-snapshot-win32.zip/download

#### Compiling and linking code
```sh
cl65 -t [commodore_type] -m [commodore_model] file.c -o [output_name].prg
```
Example:
```sh
cl65 -t pet -m 4032 petsynth007.c -o petsynth007.prg
```
The .prg is the executable you can directly load into the Commodore.

## Choosing Commodore model in VICE
```sh
[commodore_emulator] -model [model_number]
```
Example:
```sh
xpet -model [4032]
```

## Informative links:
| Information | Link |
|------|------|
| Archive of source code | [PetSynth Website](https://web.archive.org/web/20110727172426/http://www.petsynth.org/) |
| Compiling and modiyfing source code | [Compile and modify](https://web.archive.org/web/20121014022810/http://www.petsynth.org/support/compiling_and_modifying_the.html) |
| Exporting files to PET (works for emulators) | [Exporting files](https://web.archive.org/web/20120313025210/http://www.petsynth.org/support/getting_files_out_of_your_p.html) |
| Changing PET Model in VICE | https://www.cs.cmu.edu/~dsladic/vice/doc/html/vice_7.html#SEC98 |
| Commodore PET Repair and Restore by The 8-Bit Guy | https://www.youtube.com/watch?v=uHbhH7ISL_Y |
| Repair or upgrade your PET | http://www.tynemouthsoftware.co.uk/ |
| SD Card for PET | https://petsd.net/ |
| Keys for VICE Emulator | https://vice-emu.pokefinder.org/index.php/VICEKB |
| Dangerous pokes (killer poke) | http://www.6502.org/users/andre/petindex/poke/index.html |


## Freenode IRCs
- #vice-dev
- #c64friends
