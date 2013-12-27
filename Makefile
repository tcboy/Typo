#Executable
EXE    = Typofinder

# Compiler, Linker Defines
CC      = g++ 
LIBS    = 
LDFLAGS = $(LIBS)

# Compile and Assemble C++ Source Files into Object Files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Source and Object files
SRC    = $(wildcard *.cpp)
OBJ    = $(patsubst %.cpp, %.o, $(SRC))
FLAG   =
CFLAGS = -O3 -s
# Link all Object Files with external Libraries into Binaries
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) $(FLAG) -o $(EXE) -lpthread -lz

.PHONY: clean
clean:
	 -rm -f core *.o

