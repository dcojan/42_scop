NAME=scop

SRC= main.c \
		scop.c \
		init.c \
		main_loop.c \
		event.c \
		event_handlers.c \
		object_loader.c \
		object_loader_label_1.c \
		object_loader_label_2.c \
		glsl_loader.c \
		shaders.c \
		camera.c \
		rotation.c \
		light.c \
		buffers.c \
		object.c \
		clean.c \
		utils.c

SRCGLMATH= lookat.c \
			vec3operations.c \
			vec4operations.c \
			mat4x4operations.c \
			perspective.c \
			quaternions.c

OBJ= $(SRC:.c=.o)
OBJ+= $(SRCGLMATH:.c=.o)

VPATH:= src:glmaths
DIROBJ= obj/
DIROBJS= $(addprefix $(DIROBJ), $(OBJ))

CC=clang

FLAGS= -Werror -Wextra -Wall

INC= -I ./includes -I ./glmaths

UNAME_S := $(shell uname -s)

LIB= -lGLEW -lm
ifeq ($(UNAME_S),Linux)
LIB+= -lGL -lSDL2
endif
ifeq ($(UNAME_S),Darwin)
LIB+= -framework OpenGL -L $(HOME)/.brew/lib -lSDL2
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
