# Makefile

CC=gcc #-fsanitize=address
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500
CFLAGS= -Wall -Wextra -std=c99 -O2 -O0 -g -lm -lSDL -lSDL_image `pkg-config --cflags --libs gtk+-2.0`
LDFLAGS= -fsanitize=address
LDLIBS= -fsanitize=address -lm -lSDL -lSDL_image `pkg-config --cflags --libs gtk+-2.0`

SRC= xor.c MathForOcr.c Matrix.c Network.c ImageTraining.c convert.c Image_Func.c SaveAndLoad.c main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main

# END

