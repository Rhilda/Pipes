NAME 	= pipe.a
EXE		= pipex

SRCS 	= pipe.c
OBJS 	= ${SRCS:.c=.o}
MAIN	= pipe.c

SRCS_B	= pipe_bonus.c util.c
OBJS_B	= ${SRCS_B:.c=.o}
MAIN_B	= pipe_bonus.c

D_FILES = $(patsubst %.c, %.d,$(SRCS) $(SRCS_B))

CC 		= gcc -Wall -Wextra -Werror

.c.o:		%.o : %.c
					$(CC) -I./ -c $< -o $(<:.c=.o) -MD

include $(wildcard $(D_FILES))

$(NAME):	${OBJS}
					make re -C ./libft
					cp libft/libft.a ./$(NAME)
					ar -rcs ${NAME} ${OBJS}
					$(CC) $(NAME) ${MAIN} -o ${EXE}

all: 		${NAME}

bonus:		${OBJS_B}
					make re -C ./libft
					cp libft/libft.a ./$(NAME)
					ar -rcs ${NAME} ${OBJS_B}
					$(CC) $(NAME) ${MAIN_B} -o ${EXE}

clean:
					make clean -C ./libft
					rm -f ${OBJS} ${OBJS_B} *.d

fclean: 	clean
					make fclean -C ./libft
					rm -f $(NAME)
					rm -f ${EXE}

re:			fclean all

.PHONY: all clean fclean re bonus