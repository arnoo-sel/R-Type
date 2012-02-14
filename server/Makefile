##
## Makefile for r-type server in /home/jartho_d/work/r-type/server
## 
## Made by adrien1 jarthon
## Login   <jartho_d@epitech.net>
## 
## Started on  Thu Dec  3 16:19:10 2009 adrien1 jarthon
## Last update Wed Dec 16 14:05:48 2009 adrien1 jarthon
##

FOLDER = `uname -s`_`uname -m`

NAME =	bin/$(FOLDER)/rtype_server

SRCS =	src/main.cpp \
	src/filesystem/fileUnix.cpp \
	src/filesystem/fileException.cpp \
	src/threads/threadUnix.cpp \
	src/threads/threadException.cpp \
	src/library/libraryUnix.cpp \
	src/library/libraryException.cpp \
	src/sockets/socketUnix.cpp \
	src/sockets/socketException.cpp \
	src/game.cpp \
	src/identifiable.cpp \
	src/level.cpp \
	src/monster.cpp \
	src/monsterType.cpp \
	src/spawn.cpp \
	src/time.cpp \
	src/math/vertex.cpp \
	src/player.cpp \
	src/server.cpp \
	src/bullet.cpp \
	src/rocket.cpp \
	src/entity.cpp

CC = g++

OBJS =	$(SRCS:.cpp=.o)

LIBS = -lpthread -ldl

CFLAGS = -W -Wall -O5 -g $(INCLUDE)

INCLUDE = -I../include -Iinclude

all:	init $(OBJS)
	@echo -n "[32m"
	@echo "start linking process ..."
	@echo -n "[35m"
	@mkdir -p bin/$(FOLDER)	
	$(CC) -o $(NAME) $(OBJS) $(LIBS)
	@echo -n "[0m"

init:
	@echo -n "[32m"
	@echo "start compiling process ..."
	@echo -n "[0m"

.cpp.o:
	@echo -n "[36m"
	@mkdir -p `dirname $@`
	$(CC) $(CFLAGS) -o $@ -c $<
	@echo -n "[0m"

clean:
	@echo -n "[33m"
	rm -f $(OBJS)
	rm -f *~ */*~ */*/*~
	@echo -n "[0m"

fclean: clean
	@echo -n "[31m"
	rm -f $(NAME)
	@echo -n "[0m"

re: fclean all
