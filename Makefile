NAME=scop

SRC= main.c \
		init.c \
		main_loop.c \
		clean.c

OBJ= $(SRC:.c=.o)

LIB= -lGL -lSDL2 -lGLEW

DIRSRC= src/
DIROBJ= obj/
DIROBJS= $(addprefix $(DIROBJ), $(OBJ))

CC=clang

FLAGS= -Werror -Wextra -Wall

INC= -I ./includes

UNAME_S := $(shell uname -s)

INC= -I ./includes
LIB= -lSDL2 -lGLEW
ifeq ($(UNAME_S),Linux)
LIB+= -lGL
endif
ifeq ($(UNAME_S),Darwin)
LIB+= -framework OpenGL
endif



all: $(NAME)

$(NAME): $(DIROBJS)
	$(CC) $^ -o $@ $(LIB)

$(DIROBJ)%.o: $(DIRSRC)%.c
	mkdir -p $(DIROBJ)
	$(CC) $(FLAGS) -c $^ -o $@  $(INC)

clean:
	rm -rf $(DIROBJ)
fclean: clean
	rm -rf $(NAME)

re: fclean all
