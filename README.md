# Autonomous Vacuum Cleaner – Multi-Room Coverage Planner
CSE 211 - Data Structures Term Project

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

## Build and Run Test Files
RUN TEST: 
    make test
    
CLEAR:
    make clean
    make clear
        
## Notes
The README will be updated as implementation progresses.

## Contributors
CSE 211 Project 8 Group

