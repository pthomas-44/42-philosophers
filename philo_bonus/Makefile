# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pthomas <pthomas@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 17:05:21 by pthomas           #+#    #+#              #
#    Updated: 2021/11/25 15:04:32 by pthomas          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

#========================================#
#=============== VARIABLES ==============#
#========================================#

#~~~~ Output ~~~~#

NAME		=	philo_bonus

#~~~~ Paths ~~~~#

VPATH		=	src/
PATH_INC	=	include/
PATH_OBJ	=	obj/

#~~~~ Files ~~~~#
 
SRCS		=	main_bonus.c			\
				init_bonus.c			\
				program_bonus.c			\
				libft_functions_bonus.c	\
				utils_bonus.c

INCS		=	$(addprefix $(PATH_INC), philo_bonus.h)

OBJS		=	$(addprefix $(PATH_OBJ), $(SRCS:.c=.o))

#~~~~ Macros ~~~~#

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -pthread# -fsanitize=address -fsanitize=thread
INCLUDE		=	-I$(PATH_INC)
RM			=	rm -rf

#========================================#
#=============== TARGETS ================#
#========================================#

#~~~~ Main Rules ~~~~#

all :			$(NAME)

bonus :			all

$(NAME) :		$(OBJS)
				$(CC) $(CFLAGS) $^ -o $@ $(INCLUDE)

re :			fclean all

#~~~~ Compilation Rules ~~~~#

$(PATH_OBJ)%.o :	%.c $(INCS)
					@mkdir -p $(dir $@);
					$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

#~~~~ Cleaning Rules ~~~~#

clean :
				$(RM) $(PATH_OBJ)

fclean :		clean
				$(RM) $(NAME)

#~~~~ Eugene ~~~~#

eugene :	
			@ echo "               _,........__"
			@ echo "            ,-'            \"\`-."
			@ echo "          ,'                   \`-."
			@ echo "        ,'                        \\"
			@ echo "      ,'                           ."
			@ echo "      .'\\               ,\"\".       \`"
			@ echo "     ._.'|             / |  \`       \\"
			@ echo "     |   |            \`-.'  ||       \`."
			@ echo "     |   |            '-._,'||       | \\"
			@ echo "     .\`.,'             \`..,'.'       , |\`-."
			@ echo "     l                       .'\`.  _/  |   \`."
			@ echo "     \`-.._'-   ,          _ _'   -\" \\  .     \`"
			@ echo "\`.\"\"\"\"\"'-.\`-...,---------','         \`. \`....__."
			@ echo ".'        \`\"-..___      __,'\\          \\  \\     \\"
			@ echo "\\_ .          |   \`\"\"\"\"'    \`.           . \\     \\"
			@ echo "  \`.          |              \`.          |  .     L"
			@ echo "    \`.        |\`--...________.'.        j   |     |"
			@ echo "      \`._    .'      |          \`.     .|   ,     |"
			@ echo "         \`--,\\       .            \`7\"\"' |  ,      |"
			@ echo "            \` \`      \`            /     |  |      |    _,-'\"\"\"\`-."
			@ echo "             \\ \`.     .          /      |  '      |  ,'          \`."
			@ echo "              \\  v.__  .        '       .   \\    /| /              \\"
			@ echo "               \\/    \`\"\"\\\"\"\"\"\"\"\"\`.       \\   \\  /.''                |"
			@ echo "                \`        .        \`._ ___,j.  \`/ .-       ,---.     |"
			@ echo "                ,\`-.      \\         .\"     \`.  |/        j     \`    |"
			@ echo "               /    \`.     \\       /         \\ /         |     /    j"
			@ echo "              |       \`-.   7-.._ .          |\"          '         /"
			@ echo "              |          \`./_    \`|          |            .     _,'"
			@ echo "              \`.           / \`----|          |-............\`---'"
			@ echo "                \\          \\      |          |"
			@ echo "               ,'           )     \`.         |"
			@ echo "                7____,,..--'      /          |"
			@ echo "                                  \`---.__,--.'"

.PHONY:		all bonus clean fclean re eugene
