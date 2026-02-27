CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = runner

SOURCES = main.cpp arr.cpp doubly_list.cpp list.cpp queue.cpp stack.cpp tree.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
