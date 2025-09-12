#include <utility>
#include <tuple>
#include <vector>
#include <random>

#include "simulation.h"

namespace cgl
{

Simulation::Simulation(int rows, int columns)
    : _a(rows, columns)
    , _b(rows, columns)
    , _main(&_a)
    , _temp(&_b)
    , _running(false)
{

}

int Simulation::countLiveNeighbours(int row, int col) const
{
    static const std::vector<std::tuple<int, int>> neighbourOffsets = {
        { -1,  0 },
        {  1,  0 },
        {  0, -1 },
        {  0,  1 },
        { -1, -1 },
        { -1,  1 },
        {  1, -1 },
        {  1,  1 }
    };
    int nrows = _main->sizeRows();
    int ncols = _main->sizeColumns();

    int liveTotal = 0;
    for (const std::tuple<int, int>& offset : neighbourOffsets)
    {
        int neighbourRow = (row + std::get<0>(offset) + nrows) % nrows;
        int neighbourCol = (col + std::get<1>(offset) + ncols) % ncols;
        liveTotal += _main->cellState(neighbourRow, neighbourCol) == LIVE; // 1/0
    }

    return liveTotal;
}

bool Simulation::advance()
{
    if (!_running) return false;

    for (int row = 0; row < _main->sizeRows(); ++row)
    {
        for (int col = 0; col < _main->sizeColumns(); ++col)
        {
            int live = countLiveNeighbours(row, col);
            int state = _main->cellState(row, col);

            if (state == LIVE)
            {
                if (live > 3 || live < 2) _temp->markCellDead(row, col);
                else _temp->markCellLive(row, col);

            }
            else // DEAD
            {
                if (live == 3) _temp->markCellLive(row, col);
                else _temp->markCellDead(row, col);
            }
        }
    }

    // for this to work, update every cell in *_temp before the swap
    std::swap(_main, _temp);

    return true;
}

bool Simulation::toggleCell(int row, int col)
{
    if (_running) return false;
    return _main->toggleCellState(row, col);
}

bool Simulation::randomize()
{
    if (_running) return false;

    for (int row = 0; row < _main->sizeRows(); ++row)
    {
        for (int col = 0; col < _main->sizeColumns(); ++col)
        {
            if (rand01() > 0.7) _main->markCellLive(row, col);
            else _main->markCellDead(row, col);
        }
    }

    return true;
}

bool Simulation::running() const
{
    return _running;
}

const Grid *Simulation::currentGeneration() const
{
    return _main;
}

void Simulation::run()
{
    _running = true;
}

void Simulation::pause()
{
    _running = false;
}

bool Simulation::reset()
{
    if (_running) return false;

    _a.clear();
    // _b.clear(); // not necessary
    _main = &_a;
    _temp = &_b;

    return true;
}

double Simulation::rand01()
{
    static thread_local std::mt19937 rng{std::random_device{}()};
    static thread_local std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}

} // namespace cgl
