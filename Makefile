NAME			:= anim
BUILD_DIR		:= .build

SRC_DIR			:= src
SRCS			:= 								\
	main.c										\
	window.c									\
	focus.c										\
	question.c									\
	read_file.c									\
	input.c										\
	ui.c										\
	utf8.c										\
	utils.c										\
	won.c										\
	gnl/gnl.c									\
	gnl/gnl_utils.c								\

INCLUDES		:= 								\
	include										\

LIB_DIR			:= lib
LIBS			:=								\
	raylib


SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS			:= $(OBJS:.o=.d)

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g3
CPPFLAGS		:= $(addprefix -I,$(INCLUDES)) -MMD -MP
LDFLAGS 		:= -L$(LIB_DIR) $(addprefix -l,$(LIBS)) -lm -ldl -lpthread -lGL -lX11

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: re
	./$(NAME)

.PHONY: all clean fclean re
