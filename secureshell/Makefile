all: secureshell test brute_rand
secureshell: secureshell.c
	gcc secureshell.c -fno-stack-protector -Og -no-pie -lcrypto -lssl -o secureshell
test: test.c
	gcc test.c -Ofast -o test -lssl -lcrypto
brute_rand: brute_rand.c
	gcc brute_rand.c -Ofast -o brute_rand -lssl -lcrypto
