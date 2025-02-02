NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

OBJDIR = ./obj/
SRCDIR = ./srcs/
INCDIR = ./include/

SERVER_SRC = utils.cpp \
	Server.cpp Client.cpp Channel.cpp

COMMAND_SRC = 	cmds/PassCommand.cpp cmds/NickCommand.cpp cmds/UserCommand.cpp \
	cmds/JoinCommand.cpp cmds/PartCommand.cpp cmds/PrivmsgCommand.cpp cmds/PingCommand.cpp \
	cmds/KickCommand.cpp cmds/ModeCommand.cpp cmds/InviteCommand.cpp cmds/TopicCommand.cpp \
	cmds/UserhostCommand.cpp cmds/PongCommand.cpp cmds/ListCommand.cpp cmds/QuitCommand.cpp \
	cmds/WhoisCommand.cpp

BASE_SRC = $(SERVER_SRC) $(COMMAND_SRC)
SRC =  $(BASE_SRC) main.c

OBJS = $(OBJDIR)Server.o $(OBJDIR)Client.o $(OBJDIR)Channel.o $(OBJDIR)utils.o \
	$(OBJDIR)cmds/PassCommand.o $(OBJDIR)cmds/NickCommand.o $(OBJDIR)cmds/UserCommand.o \
	$(OBJDIR)cmds/JoinCommand.o $(OBJDIR)cmds/PartCommand.o $(OBJDIR)cmds/PrivmsgCommand.o \
	$(OBJDIR)cmds/PingCommand.o $(OBJDIR)cmds/KickCommand.o $(OBJDIR)cmds/ModeCommand.o \
	$(OBJDIR)cmds/InviteCommand.o $(OBJDIR)cmds/TopicCommand.o $(OBJDIR)cmds/UserhostCommand.o \
	$(OBJDIR)cmds/PongCommand.o $(OBJDIR)cmds/ListCommand.o $(OBJDIR)cmds/QuitCommand.o \
	$(OBJDIR)cmds/WhoisCommand.o $(OBJDIR)main.o
# $(SRC:%.c=$(OBJDIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
# $(CXX) $(OBJS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p $(dir $@) $(OBJDIR)cmds
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -I$(INCDIR)cmds -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
