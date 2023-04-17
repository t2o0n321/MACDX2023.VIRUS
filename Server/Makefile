CC = g++
CFLAGS = -Wall -Wextra -g -O3 -static

# Bin name
BIN_NAME = istcRat

# Directories
SRC_DIR := ./src
INC_DIR := ./includes
BLD_DIR := ./build
BIN_DIR := ./bin

# Files
EXEC := $(BIN_DIR)/$(BIN_NAME)
HEADERS := $(shell find $(INC_DIR) -name '*.hpp' -o -name '*.h')
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp' -o -name '*.c')
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BLD_DIR)/%.o,$(filter %.cpp,$(SOURCES))) $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(filter %.c,$(SOURCES)))

# Targets
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $^ -o $@ $(CFLAGS)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) -I$(INC_DIR) -c $< -o $@ $(CFLAGS)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) -I$(INC_DIR) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(BLD_DIR)/*.o $(EXEC)
