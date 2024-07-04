#include <bitset>
#include <iostream>
#include <iomanip>

constexpr int GRID_SIZE = 15;
constexpr int TOTAL_BITS = GRID_SIZE * GRID_SIZE;

// Function to calculate the bit position from row and column
int calculateBitPosition(int row, int col) {
    return row * GRID_SIZE + col;
}

// Function to set a bit
void setBit(std::bitset<TOTAL_BITS>& bitmask, int row, int col) {
    int pos = calculateBitPosition(row, col);
    bitmask.set(pos);
}

// Function to clear a bit
void clearBit(std::bitset<TOTAL_BITS>& bitmask, int row, int col) {
    int pos = calculateBitPosition(row, col);
    bitmask.reset(pos);
}

// Function to toggle a bit
void toggleBit(std::bitset<TOTAL_BITS>& bitmask, int row, int col) {
    int pos = calculateBitPosition(row, col);
    bitmask.flip(pos);
}

// Function to check if a bit is set
bool isBitSet(const std::bitset<TOTAL_BITS>& bitmask, int row, int col) {
    int pos = calculateBitPosition(row, col);
    return bitmask.test(pos);
}

// Function to display the grid
void displayGrid(const std::bitset<TOTAL_BITS>& bitmask) {
    std::cout << "    ";
    for (int header = 1; header <= 15; header++)
    {
        std::cout << std::setw(2) << header << " ";
    }
    std::cout << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    for (int row = 0; row < GRID_SIZE; ++row) {
        std::cout << std::setw(2) << row + 1 << " |";
        for (int col = 0; col < GRID_SIZE; ++col) {
            std::cout << std::setw(2) << isBitSet(bitmask, row, col) << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::bitset<TOTAL_BITS> bitmask;

    // Set some bits
    setBit(bitmask, 2, 3);
    setBit(bitmask, 5, 7);
    //setBit(bitmask, 10, 14);

    // Clear a bit
    clearBit(bitmask, 5, 7);

    // Toggle a bit
    toggleBit(bitmask, 10, 14);

    // Check if a bit is set
    int b_row = 10;
    int b_col = 14;
    bool bitStatus = isBitSet(bitmask, b_row, b_col);
    std::cout << "Bit at (" << b_row + 1 << ", " << b_col + 1 << ") is " << (bitStatus ? "set" : "not set") << std::endl;

    // Display the entire grid
    displayGrid(bitmask);

    return 0;
}
