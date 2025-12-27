CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -Wpedantic

TEST_SRCS = tests/test_main.cpp tests/unit/*.cpp
TEST_BIN = build/data_tests_all
TEST_LL = tests/unit/test_linkedlist.cpp
TEST_MAIN_LL = tests/unit/main/test_main_linkedlist.cpp
TEST_BIN_LL = build/test_ll
TEST_STCK = tests/unit/test_stack.cpp
TEST_MAIN_STCK = tests/unit/main/test_main_stack.cpp
TEST_BIN_STCK = build/test_stack
TEST_QUEUE = tests/unit/test_queues.cpp
TEST_MAIN_QUEUE = tests/unit/main/test_main_queue.cpp
TEST_BIN_QUEUE = build/test_queues
TEST_HASHSET = tests/unit/test_hashset.cpp
TEST_MAIN_HASHSET = tests/unit/main/test_main_hashset.cpp
TEST_BIN_HASHSET = build/test_hashset
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
	
test_linkedlist:
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_MAIN_LL) $(TEST_LL) -o $(TEST_BIN_LL)
	@./$(TEST_BIN_LL)
	@echo
	
test_stack:
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_MAIN_STCK) $(TEST_STCK) -o $(TEST_BIN_STCK)
	@./$(TEST_BIN_STCK)
	@echo
	
test_queue:
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_MAIN_QUEUE) $(TEST_QUEUE) -o $(TEST_BIN_QUEUE)
	@./$(TEST_BIN_QUEUE)
	@echo
	
test_hashset:
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_MAIN_HASHSET) $(TEST_HASHSET) -o $(TEST_BIN_HASHSET)
	@./$(TEST_BIN_HASHSET)
	@echo
	
test_all:
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $(TEST_BIN)
	@./$(TEST_BIN)
	@echo
	
