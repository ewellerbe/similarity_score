COMPILER = g++
OPTIONS = -Wall
PROGRAM = cpscRatings.out

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM) cpscCourses.txt cpscRatings.txt

$(PROGRAM): Course.cpp Rating.cpp main.cpp
	$(COMPILER) $(OPTIONS) -o $(PROGRAM) Course.cpp Rating.cpp main.cpp

clean:
	rm $(PROGRAM)
