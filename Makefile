# Compiler options
CC = g++
CFLAGS = -Wall -Wextra -g -O3 -static

# Directories
SRCDIR = src
INCDIR = includes
BUILDDIR = build
BINDIR = bin

# Files
BINNAME = reporter
EXEC = $(BINDIR)/$(BINNAME)
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
HEADERS = $(wildcard $(INCDIR)/*.hpp)

# Targets
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
# rm -rf $(BUILDDIR)/*.o $(EXEC)
	del build\*.o bin\$(BINNAME).exe
