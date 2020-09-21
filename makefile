BIN_DIR := ./bin
INC_DIR := ./include
LIB_DIR := ./lib
OBJ_DIR := ./obj
SRC_DIR := ./src
VPATH := $(SRC_DIR)
CXXFLAGS := -O2 -I $(INC_DIR) #-pedantic-errors -Wall -Wextra -Werror

SRC := $(SRC_DIR)/cache_block.cpp $(SRC_DIR)/cache_set.cpp $(SRC_DIR)/cache.cpp $(SRC_DIR)/global.cpp $(SRC_DIR)/mainfile.cpp  

OBJECTS := $(subst $(SRC_DIR),$(OBJ_DIR),$(SRC:%.cpp=%.o))
LIBS := $(LIB_DIR)/cache_block.a $(LIB_DIR)/cache_set.a $(LIB_DIR)/cache.a $(LIB_DIR)/global.a
HEADERS := $(INC_DIR)/cache_block.h $(INC_DIR)/cache_set.h $(INC_DIR)/cache.h $(INC_DIR)/global.h 
EXEC := $(BIN_DIR)/exec

.PHONY: all clean execute
all: $(EXEC)
#	g++ mainfile.o -o exec -L. -lcache_set -lcache_block -lglobal -lcache

$(BIN_DIR)/exec: $(OBJECTS) $(LIBS)
	@mkdir -p $(BIN_DIR)
	g++ $(CXXFLAGS) -o $(BIN_DIR)/exec $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	g++ $(CXXFLAGS) -c $< -o $@

$(LIB_DIR)/%.a: $(OBJ_DIR)/%.o
	@mkdir -p $(LIB_DIR)
	ar cr $@ $<

clean :
	$(RM) $(OBJECTS) $(LIBS) $(BIN_DIR)/exec

execute:
	$(BIN_DIR)/exec