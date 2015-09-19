# ---------------------------------------------------------------------
# Compiler
# ---------------------------------------------------------------------

CC  = g++

# ---------------------------------------------------------------------
# Compiler options
# ---------------------------------------------------------------------
ALL_WARNINGS = -Wall

BOOST_INC_DIR = ~/boost_1_59_0

CPP_11 = -std=c++11

DEBUG = -g

CC_FLAGS = $(DEBUG) $(ALL_WARNINGS) $(CPP_11) -I$(BOOST_INC_DIR)

#------------------------------------------------------------
#  make all: compiles the program. 
#  make exe: compiles the program and runs exe. 
#------------------------------------------------------------

OBJS = main.o algos.o boost.o pointers.o strings.o

EXEC_NAME = out

all: $(OBJS)
	$(CC) $(OBJS) $(CC_FLAGS) -o $(EXEC_NAME)

main.o: main.cpp
	$(CC) $(CC_FLAGS) -c main.cpp

algos.o: algos.cpp
	$(CC) $(CC_FLAGS) -c algos.cpp

boost.o: boost.cpp
	$(CC) $(CC_FLAGS) -c boost.cpp

pointers.o: pointers.cpp
	$(CC) $(CC_FLAGS) -c pointers.cpp

strings.o: strings.cpp
	$(CC) $(CC_FLAGS) -c strings.cpp


exe: all
	make all
	./$(EXEC_NAME)

clean:
	rm -f $(EXEC_NAME) *.o
