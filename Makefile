CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lpthread -lxml2
INCDIR=-I./include -I/usr/include/libxml2/
LIBDIR=-L/usr/lib/x86_64-linux-gnu
SRCDIR=./source/
SOURCES=$(SRCDIR)xmlHandle.c $(SRCDIR)server.c $(SRCDIR)bsp.c 
    
OBJECTS=$(SOURCES:.cpp=.o)
	EXECUTABLE=server_test

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) 
	    $(CC)  -g $(INCDIR) $(LIBDIR)  $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	    $(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o server_test
