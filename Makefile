NAME=scop

SRC= main.c \
		init.c \
		main_loop.c \
		load_shader.c \
		clean.c

SRCGLMATH= lookat.c

OBJ= $(SRC:.c=.o)
OBJ+= $(SRCGLMATH:.c=.o)

VPATH:= src:glmaths
DIROBJ= obj/
DIROBJS= $(addprefix $(DIROBJ), $(OBJ))

CC=clang

FLAGS= -Werror -Wextra -Wall

INC= -I ./includes -I ./glmaths

UNAME_S := $(shell uname -s)

LIB= -lSDL2 -lGLEW -lm
ifeq ($(UNAME_S),Linux)
LIB+= -lGL
endif
ifeq ($(UNAME_S),Darwin)
LIB+= -framework OpenGL
endif



all: $(NAME)

$(NAME): $(DIROBJS)
	$(CC) $^ -o $@ $(LIB)

$(DIROBJ)%.o: %.c
	mkdir -p $(DIROBJ)
	$(CC) $(FLAGS) -c $^ -o $@  $(INC)

clean:
	rm -rf $(DIROBJ)
fclean: clean
	rm -rf $(NAME)

re: fclean all
