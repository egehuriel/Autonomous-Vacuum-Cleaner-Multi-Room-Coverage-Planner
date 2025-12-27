CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -Wpedantic

TEST_SRCS = tests/test_main.cpp tests/unit/*.cpp
TEST_BIN = build/data_tests_all

.PHONY: test clean

test:
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $(TEST_BIN)
	@./$(TEST_BIN)
	@echo

clear:
	@echo
	@rm -f $(TEST_BIN)
	@echo "-----CLEARED-----"
	@echo
	
clean:
	@echo
	@rm -f $(TEST_BIN)
	@echo "-----CLEANED-----"
	@echo
	

