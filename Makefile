CXX = gcc
CXXFLAGS = -Wno-unused-result -Wall -Wextra -g
VAL = valgrind -q --tool=memcheck --track-origins=no --error-exitcode=1 --track-origins=yes
SRC_DIR = src/*.c
LINEAR_ALGEBRA = src/lin_alg/*.c
LIBS = -lm
EXEC = myprog
ARGS = -wh 630 230 -fill . -dist 50 -fov 45

all:
	$(CXX) $(SRC_DIR) $(LINEAR_ALGEBRA) -o$(EXEC) $(CXXFLAGS) $(LIBS)
	./$(EXEC) $(ARGS) -fin input/input2.txt
rm:
	rm $(EXEC)