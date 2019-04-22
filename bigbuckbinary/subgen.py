#!/usr/bin/env python
import time,datetime
taxt = '4831f65648bf6262622e6f676700574889e7b0020f054989c04831ffba05000000be796565744d31c941b202b0090f0548ffc08b580239f375f6ffd0'



out = [(taxt[i:i+2]) for i in range(0, len(taxt), 2)]

print('')

i = 1
for j in out:
	print(str(i))
	t1 = time.strftime('%H:%M:%S,000', time.gmtime(i))
	t2 = time.strftime('%H:%M:%S,500', time.gmtime(i))
	i+=1
	print('{} --> {}'.format(t1, t2))
	print(j)
	print('')



print(str(i))
t1 = time.strftime('%H:%M:%S,000', time.gmtime(i+5))
t2 = time.strftime('%H:%M:%S,500', time.gmtime(i+5))
i+=1
print('{} --> {}'.format(t1, t2))
print('md5sum')
print('')

print(str(i))
t1 = time.strftime('%H:%M:%S,000', time.gmtime(i+5))
t2 = time.strftime('%H:%M:%S,500', time.gmtime(i+5))
i+=1
print('{} --> {}'.format(t1, t2))
print('8792ba3802320cbe2d7f61063bdc23a4')
print('')


