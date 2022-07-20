SOURCES = main.c parser.c pipes.c files.c start.c error.c
NAME = pipex
LIBFT = ./libft/libft.a
SRCS_PATH = srcs
OBJS_PATH = objs
SRCS = ${addprefix ${SRCS_PATH}/, ${SOURCES}}
OBJS = ${addprefix ${OBJS_PATH}/, ${SOURCES:.c=.o}}
FLAGS = -g
CC = gcc

# Colors
GREEN =	\33[1;32m
L_CYAN = \33[1;36m
L_BLUE = \33[1;34m
L_GREEN = \33[1;92m
NC = \033[0m

all: ${NAME}

bonus: all

${NAME}: ${LIBFT} ${OBJS}
		@ ${CC} ${OBJS} ${LIBFT} -o ${NAME}
		@ echo "${GREEN}Pipex successfully compiled! ${NC}"

${OBJS_PATH}/%.o: ${SRCS_PATH}/%.c
				@ echo "Compiling: $<"
				@ mkdir -p ${OBJS_PATH}
				@ ${CC} ${FLAGS} -c $< -o $@ -I ./include -I ./libft/include

${LIBFT}:
		@ echo "Compiling Libft..."
		@ make -C ./libft --no-print-directory

clean:
		@ rm -rf ${OBJS_PATH}/
		@ echo "${L_CYAN}Pipex objects deleted!${NC}"

fclean: clean
		@ make fclean -C ./libft --no-print-directory
		@ rm -f ${NAME}
		@ echo "${L_BLUE}Pipex deleted!${NC}"

re: fclean all

norma:
		norminette srcs/ include/

.PHONY: all bonus clean fclean re norma