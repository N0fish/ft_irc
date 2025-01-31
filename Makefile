NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

OBJDIR = ./obj/
SRCDIR = ./srcs/
INCDIR = ./include/

SRC = Server.cpp Client.cpp Channel.cpp \
	PassCommand.cpp NickCommand.cpp UserCommand.cpp \
	JoinCommand.cpp PartCommand.cpp PrivmsgCommand.cpp PingCommand.cpp \
	KickCommand.cpp ModeCommand.cpp InviteCommand.cpp TopicCommand.cpp \
	main.cpp 
OBJS = $(SRC:%.cpp=$(OBJDIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
