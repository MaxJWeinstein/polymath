CC=gcc
CXX=g++
CPPFLAGS=-std=c++23 -g
LDFLAGS=-g

SRCDIR=src
SRCS=$(shell find src -name "*.cpp")

BUILDDIR=build
OBJS=$(subst .cpp,.o,$(SRCS))
#OBJS=$(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(OBJFILES))

all: mathtools

mathtools: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o mathtools $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^ >> ./.depend

clean:
	rm -f $(OBJS)

distclean: clean
	rm -f *~ .depend

include .depend

