NAME			=		computor
NAME_BONUS			=		computor_bonus

SRC_DIR		=	./src/
OBJ_DIR		=	obj/
OBJ_BONUS_DIR		=	obj_bonus/

IMPS_DIR	=	./includes/implementations/
HDRS_DIR	=	./includes/headers/

MAIN_INC	= -I $(HDRS_DIR) -I $(IMPS_DIR)

IMPS		=	$(shell find $(IMPS_DIR) -type f -name "*.ipp")
HDRS		= 	$(shell find $(HDRS_DIR) -type f -name "*.hpp")

IMPS_BONUS	=	$(shell find $(IMPS_DIR) -type f -name "*_bonus.ipp")
HDRS_BONUS	= 	$(shell find $(HDRS_DIR) -type f -name "*_bonus.hpp")

SRC			=	main.cpp   \

SRC_BONUS	=	main_bonus.cpp \

OBJ			=	$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
OBJ_BONUS	=	$(addprefix $(OBJ_BONUS_DIR), $(SRC_BONUS:.cpp=.o))

CC				=	g++
CFLAGS			=	-Wall -Wextra -Werror -std=c++11

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp $(HDRS) $(IMPS) Makefile
		@mkdir -p $(OBJ_DIR)
		$(CC) ${CFLAGS}  $(MAIN_INC) -o $@ -c $<

$(OBJ_BONUS_DIR)%.o:	$(SRC_DIR)%.cpp $(HDRS_BONUS) $(IMPS_BONUS) Makefile
		@mkdir -p $(OBJ_BONUS_DIR)
		$(CC) ${CFLAGS}  $(MAIN_INC) -o $@ -c $<

$(NAME)		:	$(OBJ) $(HDRS) $(IMPS)
		$(CC) $(CFLAGS) $(OBJ) $(MAIN_INC) -o $(NAME)

$(NAME_BONUS)	:	$(OBJ_BONUS) $(HDRS) $(IMPS)
		$(CC) $(CFLAGS) $(OBJ_BONUS) $(MAIN_INC) -o $(NAME_BONUS)
					
all			:	$(NAME)

bonus		:	$(NAME_BONUS)

clean		:
		@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean		:	clean
		@rm -rf $(NAME) $(NAME_BONUS)

re			:	fclean	all

.PHONY		:	all clean fclean re bonus