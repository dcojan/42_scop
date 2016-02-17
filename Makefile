NAME=scop

SRC= main.c \
		scop.c \
		init.c \
		main_loop.c \
		event.c \
		event_handlers.c \
		dot_mtl_file_loader.c \
		dot_obj_file_loader.c \
		dot_obj_file_loader_label_1.c \
		dot_obj_file_loader_label_2.c \
		glsl_file_loader.c \
		shaders.c \
		camera.c \
		rotation.c \
		light.c \
		buffers.c \
		mesh_building.c \
		mesh_setup.c \
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



all: makedir $(NAME)

makedir:
	mkdir -p $(DIROBJ)

$(NAME): $(DIROBJS)
	$(CC) $^ -o $@ $(LIB)

$(DIROBJ)%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@  $(INC)

clean:
	rm -rf $(DIROBJ)
fclean: clean
	rm -rf $(NAME)

re: fclean all
