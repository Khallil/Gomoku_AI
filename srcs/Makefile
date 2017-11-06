CC	:= g++

RM	:= rm -f

LIBS =  -lsfml-graphics -lsfml-system -lsfml-window

CXXFLAGS := -I./includes

CFLAGS	:= -g  -std=c++11

SRCS	:= $(shell find srcs -type f -name "*.cpp")

OBJS	:= $(SRCS:.cpp=.o)

NAME	:= gomoku

all: $(NAME)

$(NAME):
	$(CC) -o $(NAME) $(CXXFLAGS) $(SRCS) $(CFLAGS) $(LIBS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
