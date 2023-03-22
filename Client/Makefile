# Compiler options
CC = g++.exe
CFLAGS = -Wall -Wextra -g -O3 -static -lwsock32 -lws2_32

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
	$(CC) $^ -o $@ $(CFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CC) -I$(INCDIR) -c $< -o $@ $(CFLAGS)

clean:
# rm -rf $(BUILDDIR)/*.o $(EXEC)
	del build\*.o bin\$(BINNAME).exe
