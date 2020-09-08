# recover-jpegs
C program to recover and write .jpg files from forensic image

'forensic_img.raw' mimics an erased memory card that had 50 JPEGS saved on it. It functions as if the memory card has not yet been overwritten.

In principle, the algorithm could be used to recover and write arbitrary file types from an arbitrary forensic image.

Linux command line/Mac Terminal zsh usage:

~/recover-jpegs % make recover-jpegs.c
~/recover-jpegs % ./recover-jpegs forensic_img.raw
