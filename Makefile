NAME=scop

SRC= main.c \
		init.c \
		clean.c

OBJ= $(SRC:.c=.o)

LIB= -lGL -lSDL2 -lGLEW

DIRSRC= src/
DIROBJ= obj/
DIROBJS= $(addprefix $(DIROBJ), $(OBJ))

CC=clang

FLAGS= -Werror -Wextra -Wall

INC= -I ./includes

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
