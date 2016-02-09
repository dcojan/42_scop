NAME=scop

SRC= main.c \
		scop.c \
		init.c \
		main_loop.c \
		object_loader.c \
		object_loader_label_1.c \
		object_loader_label_2.c \
		glsl_loader.c \
		shaders.c \
		camera.c \
		light.c \
		buffers.c \
		object.c \
		clean.c \
		utils.c

SRCGLMATH= lookat.c \
			vec3operations.c \
			mat4x4operations.c \
			perspective.c

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
