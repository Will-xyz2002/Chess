# Define the compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Define any directories containing header files
INCLUDES = -I.

# Define the source files
SOURCES = chessPiece.cc bishop.cc king.cc empty.cc chessSquare.cc test_bishop.cc

# Define the object files
OBJECTS = $(SOURCES:.cc=.o)

# Define the executable file
EXECUTABLE = testChessPiece

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) -o $@

.cc.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o *~ $(EXECUTABLE)
