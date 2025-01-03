#======================== NAME ================================#

CLIENT = client

SERVER = server

#======================== SOURCES =============================#

C_DIR = src
OBJ_DIR = src/obj

C_FILES_SE = server.c

SRCS_SE = $(addprefix $(C_DIR)/,$(C_FILES_SE))

C_FILES_CL = client.c

SRCS_CL = $(addprefix $(C_DIR)/,$(C_FILES_CL))

#======================== OBJECTS =============================#

OBJS_SE = $(addprefix $(OBJ_DIR)/,$(C_FILES_SE:.c=.o))

OBJS_CL = $(addprefix $(OBJ_DIR)/,$(C_FILES_CL:.c=.o))

#======================== HEADERS =============================#

H_DIR = .

H_FILES = minitalk.h

HEADERS = $(addprefix $(H_DIR)/,$(H_FILES))

#======================== FLAGS ===============================#

CFLAGS = -Wall -Wextra -Werror

#======================== LIBRARIES ==========================#

LIBFT_DIR = lib/libft

LIBFT = $(LIBFT_DIR)/libft.a

LIBS = $(LIBFT)

#======================== INCLUDES ============================#

INCLUDES = -I$(H_DIR) -I$(LIBFT_DIR)

#======================== RULES ===============================#

all: libft $(SERVER) $(CLIENT)

$(OBJ_DIR)/%.o: $(C_DIR)/%.c Makefile $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

libft:
	$(MAKE) -C $(LIBFT_DIR)

$(SERVER): $(OBJS_SE)
	cc $^ -o $@ $(LIBS)

$(CLIENT): $(OBJS_CL)
	cc $^ -o $@ $(LIBS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

#======================== PHONY ===============================#

.PHONY: all libft clean fclean re

