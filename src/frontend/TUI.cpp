#include "frontend/TUI.hpp"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>
#include <cstdlib>

// Define static const member
const int TUI::FAST_MODE_DELAY_MS;

TUI::TUI() : mode(DisplayMode::STEP) {}

void TUI::setMode(DisplayMode m) {
    mode = m;
}

void TUI::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

char TUI::cellTypeToChar(const GridModel& grid, int r, int c) const {
    if (!grid.inBounds(r, c)) {
        return '?';
    }
    
    CellType type = grid.cells[r][c];
    
    switch (type) {
        case CellType::WALL:
            return 'W';
        case CellType::DIRTY:
            return 'F';  // Floor (uncleaned)
        case CellType::CLEAN:
            return 'F';  // Floor (uncleaned, pre-marked as clean but not cleaned yet)
        case CellType::DOCK:
            return 'C';  // Charging dock
        case CellType::DOOR:
            return 'D';  // Doorway
        case CellType::CLEANED:
            return '.';  // Cleaned floor
        default:
            return '?';
    }
}

void TUI::render(const GridModel& grid, const Position& vacuumPos, int battery) {
    clearScreen();
    
    std::cout << "=== Vacuum Cleaner Simulation ===\n";
    std::cout << "Battery: " << battery << "\n\n";
    
    // Print grid with vacuum overlay
    for (int r = 0; r < grid.R(); r++) {
        for (int c = 0; c < grid.C(); c++) {
            if (vacuumPos.r == r && vacuumPos.c == c) {
                // Overlay vacuum position
                std::cout << 'V';
            } else if (grid.isCleaned(r, c)) {
                // Show cleaned cells with dot
                std::cout << '.';
            } else {
                // Show normal cell type
                std::cout << cellTypeToChar(grid, r, c);
            }
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

void TUI::waitForNext() {
    if (mode == DisplayMode::STEP) {
        // Wait for Enter key press
        std::cout << "Press Enter to continue...";
        std::cin.get();
    } else {
        // Fast mode: sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(FAST_MODE_DELAY_MS));
    }
}

void TUI::printSummary(const GridModel& grid, int totalSteps, int totalBatteryUsed) {
    clearScreen();
    
    std::cout << "=== Simulation Complete ===\n\n";
    
    // Count cleaned cells
    int cleanedCount = 0;
    int totalFloorCount = 0;
    for (int r = 0; r < grid.R(); r++) {
        for (int c = 0; c < grid.C(); c++) {
            if (grid.isFloor(r, c)) {
                totalFloorCount++;
                if (grid.isCleaned(r, c)) {
                    cleanedCount++;
                }
            }
        }
    }
    
    std::cout << "Total Steps: " << totalSteps << "\n";
    std::cout << "Total Battery Used: " << totalBatteryUsed << "\n";
    std::cout << "Floors Cleaned: " << cleanedCount << " / " << totalFloorCount << "\n";
    std::cout << "Coverage: " << (totalFloorCount > 0 ? (cleanedCount * 100 / totalFloorCount) : 0) << "%\n\n";
    
    // Print final grid state
    std::cout << "Final Grid State:\n";
    for (int r = 0; r < grid.R(); r++) {
        for (int c = 0; c < grid.C(); c++) {
            if (grid.isCleaned(r, c)) {
                std::cout << '.';
            } else {
                std::cout << cellTypeToChar(grid, r, c);
            }
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

