#ifndef TUI_HPP
#define TUI_HPP

#include "core/GridModel.hpp"
#include "core/Position.hpp"
#include "frontend/DisplayMode.hpp"

class TUI {
public:
    TUI();
    
    // Render the grid with vacuum position overlay
    void render(const GridModel& grid, const Position& vacuumPos, int battery);
    
    // Set display mode (STEP or FAST)
    void setMode(DisplayMode mode);
    
    // Wait for next step (STEP mode) or sleep (FAST mode)
    void waitForNext();
    
    // Clear the screen
    void clearScreen();
    
    // Print final summary
    void printSummary(const GridModel& grid, int totalSteps, int totalBatteryUsed);

private:
    DisplayMode mode;
    
    // Convert CellType to display character
    char cellTypeToChar(const GridModel& grid, int r, int c) const;
    
    // Fast mode sleep duration (milliseconds)
    static const int FAST_MODE_DELAY_MS = 100;
};

#endif

