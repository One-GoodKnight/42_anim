NAME			:= anim
BUILD_DIR		:= .build

SRC_DIR			:= src
SRCS			:= 								\
	file_op/read_file.c							\
												\
	gnl/gnl.c									\
	gnl/gnl_utils.c								\
												\
	logic/nb_question.c							\
	logic/question.c							\
	logic/shuf_str_question.c					\
	logic/str_question.c						\
	logic/won.c									\
												\
	utils/utf8.c								\
	utils/utils.c								\
	utils/utils_n.c								\
	utils/utils_str.c							\
	utils/utils_uchar.c							\
												\
	window/input.c								\
	window/rendering/box.c						\
	window/rendering/input_render.c				\
	window/rendering/ui.c						\
	window/focus.c								\
	window/window.c								\
												\
	main.c										\

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

run: all
	./$(NAME)

val: all
	valgrind --leak-check=full --suppressions=val.supp ./anim

.PHONY: all clean fclean re
