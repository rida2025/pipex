NAME = pipex

BONUS = pipex_bonus

COMPILER = cc

FLAGS = -Wall -Wextra -Werror

CFILES = pipex.c \
		ft_split.c \
		ft_substr.c \
		ft_strlen.c \
		ft_strjoin.c \
		helper_tools1.c \
		pipex_helper3.c \
		ft_strcmp.c \
		ft_strncmp.c \
		pipex_helper.c \
		ft_putstr.c \
		get_next_line_utils.c

BCFILES = pipex_bonus.c \
		ft_split_bonus.c \
		ft_substr_bonus.c \
		ft_strlen_bonus.c \
		ft_strjoin_bonus.c \
		helper_tools1_bonus.c \
		pipex_helper_bonus.c \
		pipex_helper2_bonus.c \
		pipex_helper3_bonus.c \
		ft_strcmp_bonus.c \
		ft_strncmp_bonus.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \
		ft_putstr_bonus.c \
		check_and_replace_bonus.c

OBJC = $(CFILES:.c=.o)
BOBJC = $(BCFILES:_bonus.c=_bonus.o)

all: $(NAME)

$(NAME): $(OBJC) pipex.h
	$(COMPILER) $(FLAGS) $(OBJC) -o $(NAME)

bonus: $(BONUS)

$(BONUS): $(BOBJC) pipex_bonus.h
	$(COMPILER) $(FLAGS) $(BOBJC) -o $(BONUS)

%.o: %.c pipex.h
	$(COMPILER) $(FLAGS) -c $< -o $@

%_bonus.o: %_bonus.c pipex.h
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJC) $(BOBJC)

fclean: clean
	rm -rf $(NAME) $(BONUS)

re: fclean all
