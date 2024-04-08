##
## EPITECH PROJECT, 2024
## B-PDG-300-PAR-3-1-PDGRUSH3-naira.awadin
## File description:
## Makefile
##
SRC = src/main.cpp

CC ?= g++

OBJ = $(SRC:.cpp=.o)

NAME = arcade

NCURSES_LIB = lib/arcade_ncurses.so

SDL2_LIB = lib/arcade_sdl2.so

SFML_LIB = lib/arcade_sfml.so

LDFLAGS = -ldl -lstdc++

CFLAGS = -Wall -Wextra

RM = rm -f

all: $(NAME) $(NCURSES_LIB) $(SDL2_LIB) $(SFML_LIB)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)

$(NCURSES_LIB): src/ncurses_library.cpp
	$(CC) -shared -fPIC -o $(NCURSES_LIB) src/ncurses_library.cpp -lncurses

$(SDL2_LIB): src/sdl2_library.cpp
	$(CC) -shared -fPIC -o $(SDL2_LIB) src/sdl2_library.cpp -lSDL2 -lSDL2_image

$(SFML_LIB): src/sfml_library.cpp
	$(CC) -shared -fPIC -o $(SFML_LIB) src/sfml_library.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lc++

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(NCURSES_LIB) $(SDL2_LIB) $(SFML_LIB)

re: fclean all

.PHONY: all clean fclean re
