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

SRCDIR := src
OBJDIR := dist

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

app: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

# app: dist/main.o
# 	$(CC) $^ -o $@ $(LDFLAGS)

# dist/main.o: src/main.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) app
