#include <utility>
#include <tuple>
#include <vector>
#include <random>
#include <iostream>

#include "simulation.h"

namespace cgl
{

Simulation::Simulation(int rows, int columns)
    : _rows(rows)
    , _columns(columns)
    , _a(_rows, _columns)
    , _b(_rows, _columns)
    , _current(&_a)
    , _temp(&_b)
    , _age(0)
    , _running(false)
{

}

int Simulation::sizeRows() const
{
    return _rows;
}

int Simulation::sizeColumns() const
{
    return _columns;
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
    int nrows = _current->sizeRows();
    int ncols = _current->sizeColumns();

    int liveTotal = 0;
    for (const std::tuple<int, int>& offset : neighbourOffsets)
    {
        int neighbourRow = (row + std::get<0>(offset) + nrows) % nrows;
        int neighbourCol = (col + std::get<1>(offset) + ncols) % ncols;
        liveTotal += _current->cellState(neighbourRow, neighbourCol) == LIVE; // 1/0
    }

    return liveTotal;
}

bool Simulation::advance()
{
    if (!_running) return false;

    for (int row = 0; row < _current->sizeRows(); ++row)
    {
        for (int col = 0; col < _current->sizeColumns(); ++col)
        {
            int live = countLiveNeighbours(row, col);
            int state = _current->cellState(row, col);

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
    std::swap(_current, _temp);

    ++_age;

    return true;
}

bool Simulation::markCellLive(int row, int col)
{
    if (_running) return false;

    return _current->markCellLive(row, col);
}

bool Simulation::markCellDead(int row, int col)
{
    if (_running) return false;

    return _current->markCellDead(row, col);
}

bool Simulation::randomize()
{
    if (_running) return false;

    reset();

    for (int row = 0; row < _current->sizeRows(); ++row)
    {
        for (int col = 0; col < _current->sizeColumns(); ++col)
        {
            if (rand01() > 0.7) _current->markCellLive(row, col);
            else _current->markCellDead(row, col);
        }
    }

    return true;
}

long Simulation::age() const
{
    return _age;
}

bool Simulation::running() const
{
    return _running;
}

const Grid *Simulation::currentGeneration() const
{
    return _current;
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
    _current = &_a;
    _temp = &_b;
    _age = 0;

    return true;
}

void Simulation::dump()
{
    if (_running) return;

    for (int row = 0; row < _current->sizeRows(); ++row)
    {
        for (int col = 0; col < _current->sizeColumns(); ++col)
        {
            if (_current->cellState(row, col) == LIVE)
            {
                std::cout << "TGL(" << row << ", " << col << ");" << std::endl;
            }
        }
    }
}

double Simulation::rand01()
{
    static thread_local std::mt19937 rng{std::random_device{}()};
    static thread_local std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}

} // namespace cgl
