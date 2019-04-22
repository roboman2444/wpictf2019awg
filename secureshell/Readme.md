
Important. Make sure the clock is synched up with ntp.
Binary should be distributed.


How to:
	Srand from time, but on microsecond level. So if you know the second, you still have 1 million guesses.... not really feasable to bruteforce.

	The "canary" is generated from rand. The "incident ids" are weird md5sums of a rand() value. Therefore, if you have a incident id, you can do a local bruteforce of srand (with some estimates based on the time) until your generated incident id and the one that you got are the same. Then you can figure out what the next few canaries will be. At that point, overflow and partially overflow the return address to go to the shell function.

the Test program shows that 1 million srand guesses (with a bunch of rands and a md5) can be done in approx 1.5 seconds on a laptop. Faster if its multithreaded. If the attacker guesses the second (but not the microsecond), then it should take only a few seconds at most to bruteforce the canary. 

So the time should be synced pretty well, or they are going to be guessing for a while.



TODO:
	figure out how to put a time limit (like 30 seconds or so) on here... I think signal will do it?
