CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra -Wpedantic

BIN_DIR = build
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
TEST_PARSER = tests/unit/test_parser.cpp
TEST_MAIN_PARSER = tests/unit/main/test_main_parser.cpp
TEST_BIN_PARSER = build/test_parser
CORE_SRC = src/core/*.cpp
TEST_BAT = tests/unit/test_battery.cpp
TEST_MAIN_BAT = tests/unit/main/test_main_battery.cpp
TEST_BIN_BAT = build/test_battery
TEST_PATH = tests/unit/test_pathfinder.cpp
TEST_MAIN_PATH = tests/unit/main/test_main_pathfinder.cpp
TEST_BIN_PATH = build/test_pathfinder
TEST_COVERAGE = tests/unit/test_coverageplanner.cpp
TEST_MAIN_COVERAGE = tests/unit/main/test_main_coverageplanner.cpp
TEST_BIN_COVERAGE = build/test_coverageplanner
TEST_RDEC = tests/unit/test_roomdecomposer.cpp
TEST_MAIN_RDEC = tests/unit/main/test_main_roomdecomposer.cpp
TEST_BIN_RDEC = build/test_roomdecomposer
TEST_RSTR = tests/unit/test_roomstrategy.cpp
TEST_MAIN_RSTR = tests/unit/main/test_main_roomstrategy.cpp
TEST_BIN_RSTR = build/test_roomstrategy
DATA_DIR = data
RUN_INPUTS = $(DATA_DIR)/small_room.json $(DATA_DIR)/dirtyroom.json $(DATA_DIR)/obstacle_heavy.json $(DATA_DIR)/invalid_grid.json $(DATA_DIR)/input_sample.json
RUN_BIN = build/run
FRONTEND_SRC = src/frontend/TUI.cpp src/frontend/main.cpp
APP_SRC = src/frontend/main.cpp

.PHONY: test clean

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

test: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(TEST_SRCS) -o $(TEST_BIN)
	@./$(TEST_BIN)
	@echo

clear:
	@echo
	@rm -f $(TEST_BIN)
	@rm -f -r $(BIN_DIR)
	@echo "-----CLEARED-----"
	@echo
	
clean:
	@echo
	@rm -f $(TEST_BIN)
	@rm -f -r $(BIN_DIR)
	@echo "-----CLEANED-----"
	@echo
	
test_linkedlist: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_MAIN_LL) $(TEST_LL) -o $(TEST_BIN_LL)
	@./$(TEST_BIN_LL)
	@echo
	
test_stack: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_MAIN_STCK) $(TEST_STCK) -o $(TEST_BIN_STCK)
	@./$(TEST_BIN_STCK)
	@echo
	
test_queue: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_MAIN_QUEUE) $(TEST_QUEUE) -o $(TEST_BIN_QUEUE)
	@./$(TEST_BIN_QUEUE)
	@echo
	
test_hashset: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_MAIN_HASHSET) $(TEST_HASHSET) -o $(TEST_BIN_HASHSET)
	@./$(TEST_BIN_HASHSET)
	@echo
	
test_all: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(TEST_SRCS) -o $(TEST_BIN)
	@./$(TEST_BIN)
	@echo
	
test_parser: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(TEST_MAIN_PARSER) $(TEST_PARSER) -o $(TEST_BIN_PARSER)
	@./$(TEST_BIN_PARSER)
	@echo

test_battery: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(TEST_MAIN_BAT) $(TEST_BAT) -o $(TEST_BIN_BAT)
	@./$(TEST_BIN_BAT)
	@echo
	
test_pathfinder: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(TEST_MAIN_PATH) $(TEST_PATH) -o $(TEST_BIN_PATH)
	@./$(TEST_BIN_PATH)
	@echo
	
test_coverageplanner: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(TEST_MAIN_COVERAGE) $(TEST_COVERAGE) -o $(TEST_BIN_COVERAGE)
	@./$(TEST_BIN_COVERAGE)
	@echo

test_roomdecomposer: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(TEST_MAIN_RDEC) $(TEST_RDEC) -o $(TEST_BIN_RDEC)
	@./$(TEST_BIN_RDEC)
	@echo

test_roomstrategy: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(TEST_MAIN_RSTR) $(TEST_RSTR) -o $(TEST_BIN_RSTR)
	@./$(TEST_BIN_RSTR)
	@echo
	
run_smallroom: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(FRONTEND_SRC) -o $(RUN_BIN)
	@./$(RUN_BIN) data/small_room.json
	@echo
	
run_obstacleheavy: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(FRONTEND_SRC) -o $(RUN_BIN)
	@./$(RUN_BIN) data/obstacle_heavy.json
	@echo

run_invalid: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(FRONTEND_SRC) -o $(RUN_BIN)
	@./$(RUN_BIN) data/invalid_grid.json
	@echo
	
run_dirtyroom: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(FRONTEND_SRC) -o $(RUN_BIN)
	@./$(RUN_BIN) data/dirty_room.json
	@echo
	
run_input: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(FRONTEND_SRC) -o $(RUN_BIN)
	@./$(RUN_BIN) data/input_sample.json
	@echo
	
run: $(BIN_DIR)
	@echo
	@$(CXX) $(CXXFLAGS) $(CORE_SRC) $(FRONTEND_SRC) -o $(RUN_BIN)
	@bash -c '\
		files=( $(RUN_INPUTS) ); \
		if [ $${#files[@]} -eq 0 ]; then \
			echo "error"; exit 1; \
		fi; \
		for i in "$${!files[@]}"; do \
			echo "$$((i+1))) $${files[$$i]}"; \
		done; \
		echo -n "Choose input: "; \
		read n; \
		if ! [[ "$$n" =~ ^[0-9]+$$ ]]; then echo "error"; exit 1; fi; \
		idx=$$((n-1)); \
		if [ $$idx -lt 0 ] || [ $$idx -ge $${#files[@]} ]; then echo "error"; exit 1; fi; \
		file="$${files[$$idx]}"; \
		echo "Running: $$file"; \
		./$(RUN_BIN) "$$file"; \
	'
	@echo
