CC=g++
LDFLAGS= 
CFLAGS=-c
LIBS += -lm
SOURCES= lab3.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET= main 	

all: $(TARGET)
    
$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

%.o: %.cpp 
	$(CC) $(CFLAGS) $< $(LIBS)

clean:
	rm *.o $(TARGET)
