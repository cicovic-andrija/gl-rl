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

    bool advance();
    bool toggleCell(int row, int col);
    bool randomize();
    bool running() const;
    const Grid *currentGeneration() const;
    void run();
    void pause();
    bool reset();

private:
    Grid _a;
    Grid _b;
    Grid *_main;
    Grid *_temp;
    bool _running;

    int countLiveNeighbours(int row, int col) const;
    static double rand01();
};

} // namespace cgl

#endif // CGL_SIMULATION_H
