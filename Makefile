# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-maze <bde-maze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/02 13:52:37 by bde-maze          #+#    #+#              #
#    Updated: 2016/09/17 02:54:57 by cmichaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

HEADER = includes/shell.h

FLAGS = -Wall -Werror -Wextra -g3 -O3

SRC = 	builtin_exit_error.c \
		designator_string.c \
		history_show_func.c \
		split_inib_tools.c \
		new_arg_to_list.c \
		space_treatment.c \
		term_functions.c \
		history_option.c \
		split_on_spec.c \
		old_functions.c \
		history_tools.c \
		parseandexc2.c \
		ft_redirect4.c \
		tools_split.c \
		parseandexc.c \
		nsplit_inib.c \
		check_error.c \
		press_key1.c \
		press_key2.c \
		press_key3.c \
		press_key4.c \
		press_key5.c \
		press_key6.c \
		add_letter.c \
		good_order.c \
		term_read2.c \
		term_read3.c \
		designator.c \
		shell_lvl.c \
		allwrites.c \
		term_read.c \
		unsetenv.c \
		builenv3.c \
		builenv2.c \
		go_words.c \
		testredi.c \
		newredi11.c \
		is_key1.c \
		is_key2.c \
		is_key3.c \
		is_key4.c \
		is_key5.c \
		to_tree.c \
		history.c \
		setenv2.c \
		spliter.c \
		builenv.c \
		prompt.c \
		tools2.c \
		setenv.c \
		signal.c \
		cursor.c \
		shell2.c \
		shell3.c \
		error2.c \
		tools.c \
		error.c \
		agreg.c \
		shell.c \
		main2.c \
		main3.c \
		hash2.c \
		hash3.c \
		echo.c \
		env2.c \
		env3.c \
		ifcd.c \
		main.c \
		free.c \
		hash.c \
		env.c \
		cd2.c \
		cd3.c \
		cd.c \

OBJDIR = obj/

OBJ = $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)

norm:
	@norminette $(SRC) $(HEADER)

$(NAME): compile_lib compile_p $(OBJ)
		@clang $(FLAGS) -ltermcap -o $(NAME) $(OBJ) -L libft -lft
		@echo ""
		@echo "\033[32mCompilation Succeeded\033[39m"
		@echo ""

compile_p:
		@echo "\n\033[34mCompiling Project Wait...\033[39m"
		@echo ""

compile_lib:
		@make -C libft/

$(OBJDIR)%.o: %.c
		@mkdir -p $(OBJDIR)
		@clang $(FLAGS) -I libft/includes -o $@ -c $<
		@printf "\033[33m. \033[39m"
		@echo ""

clean_proj:
		@/bin/rm -f $(OBJ)

clean:
		@make -C libft/ fclean
		@/bin/rm -rf $(OBJDIR)

fclean: clean
		@/bin/rm -f $(NAME)
		@echo "\033[31mRemove\033[39m $(NAME)"

re: fclean all

.PHONY: clean fclean clean_proj compile_lib compile_p norm all
