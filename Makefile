# ---------------------------------------------------------------------
# Compiler
# ---------------------------------------------------------------------

CC  = g++

# ---------------------------------------------------------------------
# Compiler options
# ---------------------------------------------------------------------
DEBUG = -g

ALL_WARNINGS = -Wall

CPP_11 = -std=c++11

CC_FLAGS = $(DEBUG) $(ALL_WARNINGS) $(CPP_11)

#------------------------------------------------------------
#  make all: compiles the program. 
#  make exe: compiles the program and runs exe. 
#------------------------------------------------------------

OBJS = main.o strings.o

EXEC_NAME = out

all: $(OBJS)
	$(CC) $(OBJS) $(CC_FLAGS) -o $(EXEC_NAME)

main.o: main.cpp
	$(CC) $(CC_FLAGS) -c main.cpp

strings.o: strings.cpp
	$(CC) $(CC_FLAGS) -c strings.cpp


exe: all
	make all
	./$(EXEC_NAME)

clean:
	rm -f $(EXEC_NAME) *.o
