CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -Wpedantic

TEST_SRCS = tests/test_main.cpp tests/unit/*.cpp
TEST_BIN = tests_all

.PHONY: test clean

test:
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN)