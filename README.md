# greentext
### cmatrix in 108 lines of code

## y tho?
I wanted to see how far I could push malloc and free...
There may be a memory leak, please let me know!

## Known issues
On some systems, the `ncurses.h` file might just be in `/usr/include` rather than `/usr/include/ncurses`.

I don't think that is very common, but what do I know, I'm developing my stuff using a NetBSD Thinkpad.

## Building:
To install, just use
`$ sudo make install`
and it will install into $PREFIX/bin

to install to a different $PREFIX, use
`$ vi Makefile`

**change the PREFIX**

`$ sudo make install`
