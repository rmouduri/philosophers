SRCS		=	srcs/main.c	\
				srcs/ft_strcpy.c	\
				srcs/ft_strlen.c	\
				srcs/ft_isdigit.c	\
				srcs/ft_atoi.c	\
				srcs/return_error.c	\
				srcs/error.c	\
				srcs/structs.c	\
				srcs/threads.c	\
				srcs/simulation.c	\
				srcs/time.c	\
				srcs/print.c	\
				srcs/forks.c	\
				srcs/monitoring.c
OBJS_SRCS	=	$(SRCS:.c=.o)

.c.o:
				${CC} ${CFLAGS} -c ${INCLUDES} $< -o ${<:.c=.o}

INCLUDES	=	-I./includes/

NAME		=	philo

CFLAGS      =   -Wall -Werror -Wextra

CC			=	clang -g3 -fsanitize=thread

RM			=	rm -f

${NAME}:		${OBJS_SRCS}
				${CC} -o ${NAME} ${SRCS} ${CFLAGS} ${INCLUDES} -pthread

all:			${NAME}

clean:
				find . -type f \( -name "*~" -o -name "#*#" -o -name "*.o" -o -name "*.gch" \) -delete

fclean:			clean
				${RM} ${NAME}

re:				fclean all

mv_objs:		find . -type f -name "*.o" -exec mv -ft objs {} +

.PHONY:			all clean fclean re
