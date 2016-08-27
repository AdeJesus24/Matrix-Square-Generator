CXX = g++
RM = rm -f
CXXFLAGS = -Wall -std=c++11
TARGET = densemult

all: $(TARGET) demo

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp

demo: demo.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(TARGET) *.diff *.stdout *.stderr TIMEOUT COMPILE.err *.out
