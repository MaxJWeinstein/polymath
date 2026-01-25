CC=gcc
CXX=g++
CPPFLAGS=-std=c++23 -g
LDFLAGS=-g

TARGET=mathtools

SRCDIR=src
SRCS=$(shell find src -name "*.cpp")

INCLUDEDIR=include

BUILDDIR=build
OBJS=$(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(OBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c $^ -o $@ -I$(INCLUDEDIR)

clean:
	rm -f $(OBJS) $(TARGET)


.PHONY: all clean