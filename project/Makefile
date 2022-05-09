##
## EPITECH PROJECT, 2022
## B-EPI-000-PAR-0-0-projectname-user.email
## File description:
## Makefile
##

CXX	=	g++

COPY	=	cp -f
COPY_FILE	=	$(COPY)
COPY_DIR	=	$(COPY) -r

DELETE	=	rm -f
DELETE_FILE	=	$(DELETE)
DELETE_DIR	=	$(DELETE) -r

MAIN_SOURCE	=	Source/main.cpp			\

SOURCE	=	Source/Errors/Errors.cpp	\

MAIN_OBJ	=	$(MAIN_SOURCE:.cpp=.o)

OBJ	=	$(SOURCE:.cpp=.o)

INCLUDE_DIRS	=	-I Source/Errors/

CXXFLAGS	+=	-W -Wall -Wextra
CXXFLAGS	+=	$(INCLUDE_DIRS)
CXXFLAGS	+=	-std=c++2a

NAME	=	project

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(OBJ)
	@$(CXX) -o $(NAME) $(MAIN_OBJ) $(OBJ) $(CXXFLAGS)

clean:
	@$(DELETE_FILE) $(MAIN_OBJ)
	@$(DELETE_FILE) $(OBJ)

fclean:	clean
	@$(DELETE_FILE) $(NAME)

re:	fclean all

.PHONY: all $(NAME) clean fclean re
