# Makefile

CC = gcc -fsanitize=address 
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -lm -g -lSDL -lSDL_image 
LDFLAGS =
LDLIBS = -lm -lSDL -lSDL_image 

OBJ = convert.o Image_Func.o ImageTraining.o MathForOcr.o Matrix.o Network.o xor.o main.o
DEP = ${OBJ:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} main

-include ${DEP}

# END
