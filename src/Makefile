CC=g++
#CC=clang++
ACFLAGS = -O2
#ACFLAGS = -Wall -g
CFLAGS = -c -std=c++11 `pkg-config --cflags gtk+-3.0` 
LDFLAGS= -rdynamic `pkg-config --libs gtk+-3.0`
SOURCES=main.cpp gui.cpp autostart.cpp item.cpp fs.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=startup-settings

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS)$(ACFLAGS) $< -o $@

remake: clean all

debug: clean all
	gdb ./$(EXECUTABLE)

run: all
	./$(EXECUTABLE)

release: all clean
	cp $(EXECUTABLE) ../

clean:
	rm -f $(OBJECTS)
