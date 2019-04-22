"Two level challenge"

First level - pretty simple buffer overflow. Just overflow until you set the "auth" variable to something other than 0. That will grant you access to view the source code in less.

Second level - get a shell on it. People would first try !sh in less, but LESSSECURE env variable is set. You need to ROP to set that variable to "". (this can be done by ropping to the setenv call, but incrementing the "1" string pointer by one first... pretty simple see the solution)


Since it uses less, it needs a valid TTY. Not easily doable over ssh?

So we should host it as a "ssh challenge"... treat it kinda like one of ben's shell jails from last year
We can also set up ssh so that it doesnt give you a shell when you connect, but instead runs the program. There is a native way for ssh to do this. - THis might break my solution though (set login for the user? idk)

^^^^ best way to do it



Should probably tell them the exact GCC version used for compilation.....

Ideally we wouldn't distribute anything. They get access to the source code, see the exact version used to compile, and can create a copy locally. (needs testing, and maybe a different binary)


probably needs to be modified
