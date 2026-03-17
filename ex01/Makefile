.PHONY: all clean fclean re

NAME := RPN

OBJS_DIR := .build/

SRCS := main.cpp
INCS := .
OBJS := $(addprefix $(OBJS_DIR), $(SRCS:%.cpp=%.o))
DEPS := $(OBJS:.o=.d)

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
CPPFLAGS := $(addprefix -I,$(INCS)) -MMD -MP
MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(OBJS_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJS_DIR)

fclean:
	rm -rf $(OBJS_DIR)
	rm -f $(NAME)

re: fclean
	$(MAKE) all