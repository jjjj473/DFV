CC = gcc
CFLAGS = -Wall -O3 -march=native -msse2 $(shell pkg-config --cflags gtk+-3.0 webkit2gtk-4.0)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0 webkit2gtk-4.0)

ASM_SRCS = asm/fast_add.S asm/fast_memcpy.S asm/fast_strlen.S \
            asm/fast_uppercase.S asm/fast_memset.S asm/fast_strcmp.S
ASM_OBJS = $(ASM_SRCS:.S=.o)

SRCS = src/dfv_browser.c
OBJS = $(SRCS:.c=.o) $(ASM_OBJS)

dfv_browser: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) -c $< -o $@


clean:
	$(RM) $(OBJS) dfv_browser
