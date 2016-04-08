PROJ_DIR = .
INCLUDE_DIR     = $(PROJ_DIR)/include
SRC_DIR         = $(PROJ_DIR)/src
OBJ_DIR         = $(PROJ_DIR)/obj

INCLUDE = -I $(INCLUDE_DIR)
CFLAGS  =  -fno-builtin -c -Wall $(INCLUDE)
CC      = /usr/bin/gcc
BIN	= server


SRC =	$(SRC_DIR)/http_server.c	\
	$(SRC_DIR)/config_ip.c		\
	$(SRC_DIR)/html_editor.c		\
	$(SRC_DIR)/process_request.c	

#OBJ =   ${SRC:%.c=%.o}
OBJ =	$(OBJ_DIR)/http_server.o	\
	$(OBJ_DIR)/config_ip.o		\
	$(OBJ_DIR)/html_editor.o		\
	$(OBJ_DIR)/process_request.o	

#---make targets
all:	$(BIN)
#%.o:	%.c
#	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$@

$(OBJ_DIR)/http_server.o: $(SRC_DIR)/http_server.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/config_ip.o: $(SRC_DIR)/config_ip.c
	$(CC) -c $(CFLAGS) $< -o $@
$(OBJ_DIR)/html_editor.o:	$(SRC_DIR)/html_editor.c
	$(CC) -c $(CFLAGS) $< -o $@
$(OBJ_DIR)/process_request.o:	$(SRC_DIR)/process_request.c
	$(CC) -c $(CFLAGS) $< -o $@


server: $(OBJ)
	$(CC) -o $(OBJ_DIR)/$(BIN) $(OBJ) 

.PHONY : clean
clean:	
	rm -f $(OBJ_DIR)/*.o
	rm -f $(OBJ_DIR)/server
