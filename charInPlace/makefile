#Make file for TestDriver
PROG ?= charInPlace
SRCS = charInPlace.cpp  
OBJS = $(SRCS:.cpp=.o)
FLAGS = -Wall -Wextra -pedantic -ggdb -O2


all: $(PROG) classes

#CPP STUFF -----------------------------------
.cpp.o:
	g++ $(FLAGS) -c -o $@ $< 
$(PROG): $(OBJS)
	g++ $(FLAGS) -o $@ $^ 


#CLEAN STUFF ---------------------------------
clean:
	rm *.o testdriver *.class;
