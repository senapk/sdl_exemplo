CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf

all: 01_janela 02_input 03_time 04_image 05_vector 06_sound 07_font

clean:
	find . -maxdepth 1 -type f -executable -exec rm {} +

%:%.c
	$(CC) $@.c -o $@ $(CFLAGS)

