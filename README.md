# greentext
### cmatrix in 131 lines of code

## y tho?
I wanted to see how far I could push malloc and free...
There may be a memory leak, please let me know!

## Building:
To install, just use
`$ sudo make install`
and it will install into $PREFIX/bin

to install to a different $PREFIX, use
`$ vi Makefile`

**change the PREFIX**

`$ sudo make install`

## Known Issues:
It's a memory hog (For a tiny program anyway). But it never surpasses 2.1 megabytes, so I don't think its a memory leak...
