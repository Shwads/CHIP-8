CC      := gcc

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LIBS   := $(shell sdl2-config --libs)

WARN := -Wall -Wextra

MODE ?= debug

ifeq ($(MODE),debug)
  CFLAGS  := $(WARN) -O0 -g3 -DDEBUG $(SDL_CFLAGS)
  LDFLAGS := $(SDL_LIBS)
else ifeq ($(MODE),release)
  CFLAGS  := $(WARN) -O2 -DNDEBUG $(SDL_CFLAGS)
  LDFLAGS := $(SDL_LIBS)
else
  $(error Unknown MODE=$(MODE). Use MODE=debug or MODE=release)
endif

app: main.o
	$(CC) $^ -o $@ $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o app
