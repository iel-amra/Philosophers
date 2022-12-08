NAME = philo
NAME_BONUS =
SRC_DIR = src
OBJ_DIR = obj
HEADER_DIR = includes
SRC_FILES = 
SRC_FILES_BONUS = 
SRC = $(wildcard ${SRC_DIR}/*.c)
#SRC = $(addprefix ${SRC_DIR}/,${SRC_FILES})
SRC_BONUS = $(addprefix ${SRC_DIR}/,${SRC_FILES_BONUS})
OBJ = $(SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o)
OBJ_BONUS = $(SRC_BONUS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o)
HEADER = ${HEADER_DIR}/principal.h
LIBFT = libft/libft.a 
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread

all : ${NAME} ${NAME_BONUS}

${NAME} : ${OBJ}
	gcc $(FLAGS) $(OBJ) ${LIBFT} -o $(NAME)

${NAME_BONUS} : ${OBJ_BONUS} 
	gcc $(FLAGS) $(OBJ_BONUS) ${LIBFT} -o checker

${OBJ_DIR}/%.o : ${SRC_DIR}/%.c ${HEADER} Makefile ${LIBFT} | ${OBJ_DIR}
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
	rm -f checker
	rm -f ${OBJ}
	make -C libft fclean

re : fclean all

.PHONY : clean fclean re checkLibft bonus FORCE
