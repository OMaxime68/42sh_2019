##
## EPITECH PROJECT, 2020
## PSU_minishell1_2019
## File description:
## Makefile
##

CFLAGS 	=	-Iinclude -Wall
LDFLAGS	+=	
     qsdsqd
EXEC 	=	42sh

SRC		=	main.c							\
			core/sh.c						\
			core/command.c					\
			core/command_run.c				\
			core/command_build.c			\
			core/command_wait.c				\
			core/command_error.c			\
			core/stat.c						\
			core/env.c						\
			core/raw_env.c					\
			core/fs.c						\
			core/path.c						\
			builtins/exit.c					\
			builtins/env.c					\
			builtins/setenv.c				\
			builtins/unsetenv.c				\
			builtins/execute.c				\
			builtins/cd.c					\
			utils/my_puts.c					\
			utils/string_utils.c			\
			utils/string_convert.c			\
			utils/my_str_to_word_array.c	\
			utils/input_to_commands.c

OBJ		=	$(SRC:.c=.o)

all:		$(EXEC)

$(EXEC):	$(OBJ)
	gcc -o $(EXEC) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re:	fclean	all

cdb:
	compiledb make re
