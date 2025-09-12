#ifndef CGL_GRID_H
#define CGL_GRID_H

#include <vector>

namespace cgl
{

// allows for future expansion of state definitions
inline constexpr int LIVE = 1;
inline constexpr int DEAD = 0;

class Grid
{
public:
    Grid(int rows, int columns);
    Grid() = delete;
    Grid(const Grid&) = delete;
    Grid(Grid&&) = delete;
    Grid& operator=(const Grid&) = delete;
    Grid& operator=(Grid&&) = delete;

    int cellState(int row, int col) const;
    bool markCellLive(int row, int col);
    bool markCellDead(int row, int col);
    bool toggleCellState(int row, int col);
    bool toggleCellState(int row, int col, int& state);
    int sizeRows() const;
    int sizeColumns() const;
    void clear();
private:
    int _rows;
    int _columns;
    std::vector<std::vector<int>> _cells;

    bool testBounds(int row, int col) const;
};

} // namespace cgl

#endif // CGL_GRID_H
