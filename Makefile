CFLAGS := -g -Os -Wall -Wextra -Wshadow -Wstrict-prototypes -pedantic
LDFLAGS := -ldl
TARGETS := sdl2v

ifeq ($(shell uname -m), x86_64)
	TARGETS := $(TARGETS) sdl2v32
endif

all : sdl2v sdl2v32

sdl2v : sdl2v.c
	$(CC) $(CFLAGS) -o sdl2v sdl2v.c $(LDFLAGS)

sdl2v32 : sdl2v.c
	$(CC) $(CFLAGS) -m32 -o sdl2v32 sdl2v.c $(LDFLAGS)

clean:
	$(RM) $(TARGETS)
