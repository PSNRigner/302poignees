CXX     =   g++

RM      =   rm -f

NAME    =   302poignees

SRC     =   main.cpp user.cpp

OBJ     =   $(SRC:.cpp=.o)

all:        $(NAME)

$(NAME):    $(OBJ)
            $(CXX) -o $(NAME) $(OBJ)

clean:
            $(RM) $(OBJ)

fclean:     clean
            $(RM) $(NAME)

re:         fclean all