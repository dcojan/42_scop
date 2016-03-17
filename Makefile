NAME=scop

SRC= main.c \
		scop.c \
		init.c \
		main_loop.c \
		event.c \
		event_handlers.c \
		event_handlers_2.c \
		framerate.c \
		shaders.c \
		camera.c \
		rotation.c \
		light.c \
		gl_shortcuts.c \
		mesh_building.c \
		textures.c \
		mesh_setup.c \
		clean.c

SRC_WAVEFRONT_LOADER=	dot_obj_file_loader.c \
		dot_mtl_file_loader_label_1.c \
		dot_mtl_file_loader_label_2.c \
		dot_mtl_file_loader.c \
		dot_obj_file_loader_label_1.c \
		dot_obj_file_loader_label_2.c \
		dot_obj_file_loader_label_3.c \
		dot_obj_file_loader_utils.c \
		dot_obj_file_loader_utils_2.c

SRCGLMATH= lookat.c \
		vec3operations.c \
		convertions.c \
		mat4x4operations.c \
		perspective.c \
		quaternions.c \
		print.c

SRC_TGA_LOADER= tga_loader.c
SRC_BMP_LOADER= glsl_file_loader.c
SRC_GLSL_LOADER= bmp_loader.c

OBJ= $(SRC:.c=.o)
OBJ+= $(SRC_WAVEFRONT_LOADER:.c=.o)
OBJ+= $(SRC_GLSL_LOADER:.c=.o)
OBJ+= $(SRC_BMP_LOADER:.c=.o)
OBJ+= $(SRC_TGA_LOADER:.c=.o)
OBJ+= $(SRCGLMATH:.c=.o)

VPATH:= src:src/wavefront_loader:lib/glmaths:lib/glsl_loader:lib/bmp_loader:lib/tga_loader
DIROBJ= obj/
DIROBJS= $(addprefix $(DIROBJ), $(OBJ))

CC=clang -g

FLAGS= -Werror -Wextra -Wall

INC= -I ./includes -I ./lib/glmaths -I ./lib/glsl_loader -I ./lib/bmp_loader -I ./lib/tga_loader

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
