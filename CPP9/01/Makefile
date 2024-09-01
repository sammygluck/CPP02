####################
##FILES, SRC, OBJS##
####################

NAME = rpn
OBJS_DIR = objs
SRCS_DIR = src

INCL_DIR = incl

FILES = main.cpp BitcoinExchange.cpp
SRCS = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJS = $(addprefix $(OBJS_DIR)/, $(FILES:.cpp=.o))

####################
###COMPILER FLAGS###
####################

CC = c++
CFLAGS = -Wall -Wextra -Werror -g
CPPFLAGS = -std=c++98
INCLUDES = -I $(INCL_DIR)

####################
### INSTRUCTIONS ###
####################

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re