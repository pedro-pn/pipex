SOURCES = main.c parser.c pipes.c files.c start.c
NAME = pipex
LIBFT = ./libft/libft.a
SRCS_PATH = srcs
OBJS_PATH = objs
SRCS = ${addprefix ${SRCS_PATH}/, ${SOURCES}}
OBJS = ${addprefix ${OBJS_PATH}/, ${SOURCES:.c=.o}}
FLAGS = -g
CC = gcc


all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
		${CC} ${OBJS} ${LIBFT} -o ${NAME}

${OBJS_PATH}/%.o: ${SRCS_PATH}/%.c
				mkdir -p ${OBJS_PATH}
				${CC} ${FLAGS} -c $< -o $@ -I ./include -I ./libft/include

${LIBFT}:
		make -C ./libft --no-print-directory

clean:
		rm -rf ${OBJS_PATH}/

norma:
		norminette srcs/ include/