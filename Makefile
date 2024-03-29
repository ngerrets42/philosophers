# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ngerrets <ngerrets@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/15 14:47:03 by ngerrets      #+#    #+#                  #
#    Updated: 2022/02/21 12:27:39 by ngerrets      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# For now this is the default Makefile I use for C projects
# Manually edit:
NAME := philo
COMPILE_FLAGS ?= -Wall -Wextra -Werror -pthread
LINKING_FLAGS ?= -pthread
LIBRARIES ?=
SOURCE_DIRECTORY ?= src
HEADER_DIRECTORY ?= include
OBJECTS_DIRECTORY ?= objects
BINARIES_DIRECTORY ?= .

# Don't manually edit:
SOURCES :=
include sources.mk
HEADERS :=
include headers.mk

# HEADERS	:= $(shell find $(HEADER_DIRECTORY) -type f -name *.h)
INCLUDES := $(patsubst %,-I%,$(dir $(HEADERS)))
OBJECTS := $(patsubst %,$(OBJECTS_DIRECTORY)/%,$(SOURCES:.c=.o))
NAME := $(BINARIES_DIRECTORY)/$(NAME)

# Default make-rule. Compile and link files.
all: $(NAME)

# Link files
$(NAME): $(BINARIES_DIRECTORY) $(HEADERS) $(OBJECTS)
	@echo "\nLinking files..."
	@$(CC) $(OBJECTS) -o $(NAME) $(LINKING_FLAGS)
	@echo "Done!"

# Create binaries directory
$(BINARIES_DIRECTORY):
	@mkdir -p $(BINARIES_DIRECTORY)

# Compile files
$(OBJECTS_DIRECTORY)/%.o: %.c $(HEADERS)
	@echo "Compiling: $@"
	@mkdir -p $(@D)
	@$(CC) $(COMPILE_FLAGS) $(INCLUDES) -c -o $@ $<

# Clean objects
clean:
	@rm -Rf $(OBJECTS_DIRECTORY)
	@echo "Objects cleaned."

# Clean objects and binaries
fclean: clean
	@rm -f $(BINARIES_DIRECTORY)/$(NAME)
	@echo "Binaries cleaned."

# Clean, recompile and relink project
re: fclean all

# Compile, link and run project
run: all
	@echo "Running..."
	@./$(NAME)

# Prints header and source files
print:
	@echo "---HEADERS: $(HEADERS)" | xargs -n1
	@echo "---SOURCES: $(SOURCES)" | xargs -n1
	@echo "---OBJECTS: $(OBJECTS)" | xargs -n1

.PHONY: all clean fclean re run print
