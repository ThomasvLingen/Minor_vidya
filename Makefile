SILENT = @

# Compiler
CC = g++
LD = $(CC)

# Compiler flags
# Wall = all warnings
# Wextra = extra warnings
# g = debug symbols
# std=c++11 = C++11
INCLUDE_PATHS = -Isrc/
COMPILER_FLAGS = -Wall -Wextra -g -std=c++11 $(INCLUDE_PATHS)

# Linker flags
# g = debug symbols
LIBS_PATH =
LIBS = -lSDL2 -lSDL2_ttf
LINKER_FLAGS = -g

# Files to compile
SRC_PATH = src/
SRC_FILES = $(shell find $(SRC_PATH) -name '*.cpp')
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Path for the resulting file
BUILD_PATH = build/
RES_PATH = res/
PROGRAM_NAME = vidya
EXEC = $(BUILD_PATH)$(PROGRAM_NAME)

# Compile stuff
%.o : %.cpp
	@echo CC $<
	$(SILENT) $(CC) -c $< $(COMPILER_FLAGS) -o $@

$(EXEC) : $(OBJ_FILES)
	@echo
	mkdir -p $(BUILD_PATH)
	@echo LD $@
	$(SILENT) $(LD) $(COMPILER_FLAGS) $(OBJ_FILES) $(LINKER_FLAGS) $(LIBS) -o $(EXEC)
	@echo
	@echo "Moving resources to build"
	cp -r $(RES_PATH) $(BUILD_PATH)
	@echo

all : $(EXEC)

run : $(EXEC)
	$(EXEC)

libs : $(FMT_TARGET_PATH)

debug: $(EXEC)
	gdb $(EXEC)

memory_leaks: $(EXEC)
	valgrind --tool=memcheck --leak-check=full $(EXEC)

.PHONY: clean
clean:
	@echo "Cleaning build"
	rm -rf $(shell find $(SRC_PATH) -name '*.o')
	rm -rf $(BUILD_PATH)*
