NAME = philo
SRC_DIR = src
OBJ_DIR = obj
HEADER_DIR = includes
SRC_FILES = actions.c init.c main.c memory.c parsing.c philo.c time.c
SRC = $(SRC_FILES:%.c=${SRC_DIR}/%.c)
OBJ = $(SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o)
HEADER = ${HEADER_DIR}/principal.h
LIBFT = libft/libft.a 
FLAGS = -Wall -Wextra -Werror

all : ${NAME} 

print :
	echo ${SRC}
	echo ${OBJ}

${NAME} : ${OBJ}
	gcc $(FLAGS) $(OBJ) ${LIBFT} -o $(NAME)

${OBJ_DIR}/%.o : ${SRC_DIR}/%.c ${HEADER} ${LIBFT} | ${OBJ_DIR}
	gcc -include ${HEADER} $(FLAGS) -c $< -o $@

${LIBFT} : FORCE
	make -C libft

FORCE :

${OBJ_DIR} : 
	mkdir $@

clean :
	rm -f ${OBJ}
	make -C libft clean

fclean : clean
	rm -f ${NAME}
	rm -f ${OBJ}
	make -C libft fclean

re : fclean all

.PHONY : clean fclean re checkLibft FORCE
