all: gen lm solv.so
lm: lm.c ben
	gcc lm.c -o lm -Ofast -g
gen: gen.c
	gcc gen.c -o gen -g -lm -Ofast
solv.so: solv.c
	gcc solv.c -o solv.so -g -shared -fPIC -ldl
ben: gen
	./gen ./flag.png 1555286399 > paxels.h
