##
## Makefile for r-type server in /home/jartho_d/work/r-type/server/monsters
## 
## Made by adrien1 jarthon
## Login   <jartho_d@epitech.net>
## 
## Started on  Thu Dec  3 16:19:10 2009 adrien1 jarthon
## Last update Wed Dec 16 14:05:48 2009 adrien1 jarthon
##

NAME =	blork.so murloc.so boss.so boss2.so

CC = g++

CFLAGS = -W -Wall -O5 -g -shared -fPIC -I ../include

all: $(NAME)

%.so:
	@echo -n "[36m"
	$(CC) $(CFLAGS) -o $@ $(@:.so=)/main.cpp
	@echo -n "[0m"

clean:
	@echo -n "[33m"
	rm -f *.so
	rm -f *~ */*~ */*/*~
	@echo -n "[0m"

fclean: clean
	@echo -n "[31m"
	rm -f $(NAME)
	@echo -n "[0m"

re: fclean all
