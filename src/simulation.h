#ifndef CGL_SIMULATION_H
#define CGL_SIMULATION_H

#include "grid.h"

namespace cgl
{

class Simulation
{
public:
    Simulation(int rows, int columns);
    Simulation() = delete;
    Simulation(const Simulation&) = delete;
    Simulation(Simulation&&) = delete;
    Simulation& operator=(const Simulation&) = delete;
    Simulation& operator=(Simulation&&) = delete;

    int sizeRows() const;
    int sizeColumns() const;
    bool advance();
    bool toggleCell(int row, int col);
    bool randomize();
    long age() const;
    bool running() const;
    const Grid *currentGeneration() const;
    void run();
    void pause();
    bool reset();
    void dump();

private:
    const int _rows;
    const int _columns;
    Grid _a;
    Grid _b;
    Grid *_current;
    Grid *_temp;
    long _age;
    bool _running;

    int countLiveNeighbours(int row, int col) const;
    static double rand01();
};

} // namespace cgl

#endif // CGL_SIMULATION_H
