#include <algorithm>

#include "grid.h"

namespace cgl
{

Grid::Grid(int rows, int columns)
    : _rows(rows)
    , _columns(columns)
    , _cells(rows, std::vector<int>(columns, DEAD /* initial cell state*/))
{

}

bool Grid::testBounds(int row, int col) const
{
    return row >= 0 && row < _rows && col >= 0 && col < _columns;
}

int Grid::cellState(int row, int col) const
{
    if (!testBounds(row, col)) return DEAD;
    return _cells[row][col];
}

bool Grid::markCellLive(int row, int col)
{
    if (!testBounds(row, col)) return false;
    _cells[row][col] = LIVE;
    return true;
}

bool Grid::markCellDead(int row, int col)
{
    if (!testBounds(row, col)) return false;
    _cells[row][col] = DEAD;
    return true;
}

bool Grid::toggleCellState(int row, int col, int& state)
{
    if (!testBounds(row, col)) return false;
    state = _cells[row][col] = _cells[row][col] == LIVE ? DEAD : LIVE;
    return true;
}

bool Grid::toggleCellState(int row, int col)
{
    [[maybe_unused]] int x;
    return toggleCellState(row, col, x);
}

int Grid::sizeRows() const
{
    return _rows;
}

int Grid::sizeColumns() const
{
    return _columns;
}

void Grid::clear()
{
    std::for_each(
        _cells.begin(),
        _cells.end(),
        [](std::vector<int>& v) {
            std::fill(v.begin(), v.end(), DEAD /* initial cell state*/);
        }
    );
}

} // namespace cgl
