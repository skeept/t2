# MAKEFILE WORKS ONLY IN UBUNTU. NEED TO FIX IT NOT WORKING ON MAC
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

SRC_DIR = cpp-tests

OBJS = main.o algos.o boost.o pointers.o strings.o

EXEC_NAME = out

all: $(OBJS)
	$(CC) $(OBJS) $(CC_FLAGS) -o $(EXEC_NAME)

main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/main.cpp

algos.o: $(SRC_DIR)/algos.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/algos.cpp

boost.o: $(SRC_DIR)/boost.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/boost.cpp

pointers.o: $(SRC_DIR)/pointers.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/pointers.cpp

strings.o: $(SRC_DIR)/strings.cpp
	$(CC) $(CC_FLAGS) -c $(SRC_DIR)/strings.cpp


exe: all
	make all
	./$(EXEC_NAME)

clean:
	rm -f $(EXEC_NAME) *.o
