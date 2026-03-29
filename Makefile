NAME			:= anim
BUILD_DIR		:= .build

SRC_DIR			:= src
SRCS			:= 								\
	main.c										\
	window.c									\
	focus.c										\
	input.c										\
	ui.c										\

INCLUDES		:= 								\
	include										\

LIB_DIR			:= lib
LIBS			:=								\
	raylib


SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS			:= $(OBJS:.o=.d)

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
CPPFLAGS		:= $(addprefix -I,$(INCLUDES)) -MMD -MP
LDFLAGS 		:= -L$(LIB_DIR) $(addprefix -l,$(LIBS)) -lm -ldl -lpthread -lGL -lX11

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: re
	./$(NAME)

.PHONY: all clean fclean re
