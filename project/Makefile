
INC_DIR = lib
BUILD_DIR = build
OBJ_DIR = obj
SRC_DIR = src
INC = $(addprefix -I, $(INC_DIR))
INC_DLL = $(addprefix -l, $(LLIBS))
SRC = $(notdir $(wildcard $(SRC_DIR)/*.c))
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
CFLAGS := -Wall


all: prebuild prog
	
	
prog: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(INC_DLL)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

prebuild: 
	@-mkdir -p $(OBJ_DIR)

clear:
	@-rm *.log
clean:
	@-rm -rf $(OBJ_DIR)/*.o $(SRC_DIR)/*.o $(OBJ_DIR)
	@-rm prog
