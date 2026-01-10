# Autonomous Vacuum Cleaner – Multi-Room Coverage Planner

## Project Overview
This project aims to design and implement **a coverage path planning system** for an autonomous vaccum cleaner operating in a multi-room indoor enviroment.

The enviroment is represented as a grid-based layout, where each cell corresponds to a specific type of space such as floor, wall, obstacle, doorway or charging dock. The vacuum cleaner must navigate this environment and clean all reachable floor cells at least once, while respecting battery constraints and ensuring it can always return safely to the charging dock. 

The project focuses on data structures and algorithmic reasoning, rather than UI or external frameworks. All core components are implemented using plain C++ with custom pointer-based data structures.

## Core Objectives
1. Represent a multi-room home enviroment using a grid model.
2. Track visited and unvisited (cleaned / uncleaned) cells.
3. Ensure complete coerage of all floor cells.
4. Enforce battery constraints and safe return to the charging dock.
5. Support returning to charge and resuming cleaning afterward.

## Design Limitations

### Battery Management and Return-to-Dock Behavior

The current implementation successfully handles core coverage path planning functionality, including grid-based navigation, obstacle avoidance, multi-room decomposition, and complete floor cell coverage using BFS/DFS-based traversal algorithms. The system correctly tracks cleaned and uncleaned cells and generates efficient coverage paths through the environment.

However, the system includes a deliberate design limitation regarding automatic return-to-dock behavior when battery levels become critically low. Specifically, the `CoveragePlanner` component includes battery-aware path planning logic that evaluates whether sufficient battery remains to reach a target location and return to the charging dock. This planning phase correctly identifies scenarios where battery constraints would be violated and can request a return-to-dock operation through the provided hook mechanism.

The limitation occurs in the execution phase: while the planner can detect low battery conditions and generate return paths during path planning, the main execution loop does not implement proactive battery monitoring during path traversal. When battery depletion occurs during movement (reaching zero or below a critical threshold), the system halts execution at the current position rather than immediately executing a pre-computed return path to the charging dock.

This behavior is an intentional design decision for the current version of the system, focusing the implementation scope on coverage path planning algorithms and data structure correctness rather than real-time battery management during execution. The navigation, coverage, and obstacle handling components function correctly within this design framework.

## Run Project
    
    make run

## Test Projects / Files
RUN TEST: 
    
    make test
    
    make test_all
    
RUN INDIVIDUAL TESTS:

    make test_linkedlist
    
    make test_queue
    
    make test_hashset
    
    make test_stack
    
    make test_parser
    
    make test_battery
    
    make test_pathfinder
    
    make test_coverageplanner
    
    make test_roomdecomposer
    
    make test_roomstrategy
    
    make run_smallroom
    
    make run_obstacleheavy
    
    make run_dirtyroom
    
    make run_input
    
    make run_invalid (#For test purposes)

CLEAR:
    
    make clean
    
    make clear
        
## Project Structure
    CSE211-TermProject/
    ├── LICENSE
    ├── Makefile
    ├── README.md
    ├── build
    │   ├── data_tests_all
    │   └── run
    ├── data
    │   ├── dirtyroom.json
    │   ├── input_sample.json
    │   ├── invalid_grid.json
    │   ├── obstacle_heavy.json
    │   └── small_room.json
    ├── docs
    │   └── Project Report.pdf
    ├── include
    │   ├── core
    │   │   ├── BatteryManager.hpp
    │   │   ├── CoveragePlanner.hpp
    │   │   ├── GridModel.hpp
    │   │   ├── GridParser.hpp
    │   │   ├── PathFinder.hpp
    │   │   ├── Position.hpp
    │   │   ├── Room.hpp
    │   │   ├── RoomDecomposer.hpp
    │   │   └── RoomStrategy.hpp
    │   ├── data_structures
    │   │   ├── HashSet.h
    │   │   ├── LinkedList.h
    │   │   ├── Queues.h
    │   │   └── Stack.h
    │   ├── frontend
    │   │   ├── DisplayMode.hpp
    │   │   └── TUI.hpp
    │   └── libraries
    │       └── json.hpp
    ├── src
    │   ├── core
    │   │   ├── BatteryManager.cpp
    │   │   ├── CoveragePlanner.cpp
    │   │   ├── PathFinder.cpp
    │   │   ├── RoomDecomposer.cpp
    │   │   └── RoomStrategy.cpp
    │   ├── data_structures
    │   └── frontend
    │       ├── TUI.cpp
    │       └── main.cpp
    └── tests
        ├── test_main.cpp
        └── unit
            ├── TestUtil.hpp
            ├── main
            │   ├── test_main_battery.cpp
            │   ├── test_main_coverageplanner.cpp
            │   ├── test_main_hashset.cpp
            │   ├── test_main_linkedlist.cpp
            │   ├── test_main_parser.cpp
            │   ├── test_main_pathfinder.cpp
            │   ├── test_main_queue.cpp
            │   ├── test_main_roomdecomposer.cpp
            │   ├── test_main_roomstrategy.cpp
            │   └── test_main_stack.cpp
            ├── test_battery.cpp
            ├── test_coverageplanner.cpp
            ├── test_hashset.cpp
            ├── test_linkedlist.cpp
            ├── test_parser.cpp
            ├── test_pathfinder.cpp
            ├── test_queues.cpp
            ├── test_roomdecomposer.cpp
            ├── test_roomstrategy.cpp
            └── test_stack.cpp
        
## Notes
The README will be updated as implementation progresses.

## Contributors
**CSE 211 Project 8 Group**
- Ege Huriel
- Pelin Görer
- Emirhan Eren Elibol
- Eylül Pirinçal
- Selin Suna Kaya
