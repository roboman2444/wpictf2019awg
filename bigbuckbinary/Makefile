example: loader
	objdump -d loader | grep '[0-9a-f]:'| grep -v 'file' | cut -f2 -d':' | cut -f1-7 -d ' '| tr -s ' '| tr '\t' ' ' | sed "s/ $$//g"| sed 's/ /\\x/g'|paste -d '' -s | sed 's/^/"/'| sed 's/$$/"/g' > shellcode.h
#	gcc -fno-stack-protector -z execstack example.c -o loader
loader:
	nasm -felf64 loader.nasm -o loader.o && ld loader.o -o loader
	rabin2 -O d/S/.text -o loader.dump ./loader.o
	rabin2 -O d/S/.text ./loader.o

example2: player
	objdump -d player | grep '[0-9a-f]:'| grep -v 'file' | cut -f2 -d':' | cut -f1-7 -d ' '| tr -s ' '| tr '\t' ' ' | sed "s/ $$//g"| sed 's/ /\\x/g'|paste -d '' -s | sed 's/^/"/'| sed 's/$$/"/g' > shellcode.h
#	gcc -fno-stack-protector -z execstack example.c -o player2
player:
	nasm -felf64 player.nasm -o player.o && ld player.o -o player
	rabin2 -O d/S/.text -o player.dump ./player.o
	rabin2 -O d/S/.text ./player.o


encode:
	gcc -o encode encode.c
jamit:
	gcc -o jamit jamit.c
