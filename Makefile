CPP		= clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3
LDLIBS =

NAME  = tester.out
SRCS	= TESTERS/PERSO/main.cpp TESTERS/PERSO/testvector.cpp TESTERS/PERSO/testset.cpp TESTERS/PERSO/testmap.cpp #TESTERS/PERSO/teststack.cpp 
OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(OBJS) $(CXXFLAGS) $(LDLIBS) -o $@

%.o: %.cpp
	$(CPP) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
		rm -rf $(OBJS) $(DEPS) *.gch
fclean: clean
		rm -rf $(NAME)

re:		fclean $(NAME)

test:	$(NAME)
		./$(NAME)

-include $(DEPS)

.PHONY:			all clean fclean re test -include
