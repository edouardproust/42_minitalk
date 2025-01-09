#======================== NAME ================================#

CLIENT = client
SERVER = server

CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

#======================== SOURCES =============================#

C_DIR = src
OBJ_DIR = src/obj

C_FILES_SE = server.c
SRCS_SE = $(addprefix $(C_DIR)/,$(C_FILES_SE))

C_FILES_CL = client.c
SRCS_CL = $(addprefix $(C_DIR)/,$(C_FILES_CL))

C_FILES_SE_BONUS = server_bonus.c
SRCS_SE_BONUS = $(addprefix $(C_DIR)/,$(C_FILES_SE_BONUS))

C_FILES_CL_BONUS = client_bonus.c
SRCS_CL_BONUS = $(addprefix $(C_DIR)/,$(C_FILES_CL_BONUS))

#======================== OBJECTS =============================#

OBJS_SE = $(addprefix $(OBJ_DIR)/,$(C_FILES_SE:.c=.o))
OBJS_CL = $(addprefix $(OBJ_DIR)/,$(C_FILES_CL:.c=.o))

OBJS_SE_BONUS = $(addprefix $(OBJ_DIR)/,$(C_FILES_SE_BONUS:.c=.o))
OBJS_CL_BONUS = $(addprefix $(OBJ_DIR)/,$(C_FILES_CL_BONUS:.c=.o))

#======================== HEADERS =============================#

H_DIR = include

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

bonus: libft $(SERVER_BONUS) $(CLIENT_BONUS)

$(OBJ_DIR)/%.o: $(C_DIR)/%.c Makefile $(HEADERS) $(LIBFT)
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@ $(INCLUDES)

libft:
	$(MAKE) -C $(LIBFT_DIR)

$(SERVER): $(OBJS_SE)
	cc $^ -o $@ $(LIBS)

$(CLIENT): $(OBJS_CL)
	cc $^ -o $@ $(LIBS)

$(SERVER_BONUS): $(OBJS_SE_BONUS)
	cc $^ -o $@ $(LIBS)

$(CLIENT_BONUS): $(OBJS_CL_BONUS)
	cc $^ -o $@ $(LIBS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

#======================== PHONY ===============================#

.PHONY: all bonus libft clean fclean re
