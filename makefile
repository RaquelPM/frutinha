EXECUTABLE = output.out

SRCDIR = src
HEADER = header
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -I $(HEADER)
LIBS = `pkg-config --cflags opencv4` `pkg-config --libs --static opencv4`

all: $(EXECUTABLE)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE)