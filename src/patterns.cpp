#include "patterns.h"
#include "simulation.h"

namespace cgl
{

Pattern::Pattern(int reqRows, int reqCols)
    : _requiredRows(reqRows)
    , _requiredCols(reqCols)
{

}

Pattern::Pattern() : Pattern(25, 25)
{

}

Pattern::~Pattern()
{

}

bool Pattern::applyTo(Simulation *sim) const
{
    if (!sim->reset()) return false;
    if (sim->sizeRows() < _requiredRows) return false;
    if (sim->sizeColumns() < _requiredCols) return false;

    toggleCellsOn(sim);

    return true;
}

// ----------------------------------------------------------------------------

#define TGL(r, c) sim->toggleCell(r, c)

// ----------------------------------------------------------------------------

const char *Glider::name() const
{
    return "GLIDER";
}

void Glider::toggleCellsOn(Simulation *sim) const
{
    TGL(1, 3);
    TGL(2, 1);
    TGL(2, 3);
    TGL(3, 2);
    TGL(3, 3);
}

// ----------------------------------------------------------------------------

const char *Period2Oscillators::name() const
{
    return "PERIOD 2 OSCILLATORS";
}

void Period2Oscillators::toggleCellsOn(Simulation *sim) const
{
    TGL(1, 2);
    TGL(2, 2);
    TGL(2, 9);
    TGL(2, 10);
    TGL(2, 11);
    TGL(3, 2);
    TGL(3, 8);
    TGL(3, 9);
    TGL(3, 10);
    TGL(6, 4);
    TGL(6, 5);
    TGL(7, 4);
    TGL(7, 5);
    TGL(8, 6);
    TGL(8, 7);
    TGL(9, 6);
    TGL(9, 7);
}

// ----------------------------------------------------------------------------

GosperGliderGun::GosperGliderGun() : Pattern(30, 50)
{

}

const char *GosperGliderGun::name() const
{
    return "GOSPER GLIDER GUN";
}

void GosperGliderGun::toggleCellsOn(Simulation *sim) const
{
    TGL(5, 1);
    TGL(5, 2);
    TGL(6, 1);
    TGL(6, 2);
    TGL(3, 13);
    TGL(3, 14);
    TGL(4, 12);
    TGL(4, 16);
    TGL(5, 11);
    TGL(5, 17);
    TGL(6, 11);
    TGL(6, 15);
    TGL(6, 17);
    TGL(6, 18);
    TGL(7, 11);
    TGL(7, 17);
    TGL(8, 12);
    TGL(8, 16);
    TGL(9, 13);
    TGL(9, 14);
    TGL(1, 25);
    TGL(2, 23);
    TGL(2, 25);
    TGL(3, 21);
    TGL(3, 22);
    TGL(4, 21);
    TGL(4, 22);
    TGL(5, 21);
    TGL(5, 22);
    TGL(6, 23);
    TGL(6, 25);
    TGL(7, 25);
    TGL(4, 35);
    TGL(4, 36);
    TGL(5, 35);
    TGL(5, 36);
    TGL(5, 45);
}

// ----------------------------------------------------------------------------

const char *StillLifes::name() const
{
    return "STILL LIFES";
}

void StillLifes::toggleCellsOn(Simulation *sim) const
{
    TGL(1, 1);
    TGL(1, 2);
    TGL(1, 7);
    TGL(1, 8);
    TGL(2, 1);
    TGL(2, 2);
    TGL(2, 6);
    TGL(2, 9);
    TGL(3, 7);
    TGL(3, 8);
    TGL(3, 13);
    TGL(4, 12);
    TGL(4, 14);
    TGL(5, 2);
    TGL(5, 3);
    TGL(5, 13);
    TGL(6, 1);
    TGL(6, 4);
    TGL(6, 8);
    TGL(6, 9);
    TGL(7, 2);
    TGL(7, 4);
    TGL(7, 8);
    TGL(7, 10);
    TGL(8, 3);
    TGL(8, 9);
}

// ----------------------------------------------------------------------------

const char *Spaceships::name() const
{
    return "SPACESHIPS";
}

void Spaceships::toggleCellsOn(Simulation *sim) const
{
    TGL(2, 4);
    TGL(2, 5);
    TGL(3, 2);
    TGL(3, 3);
    TGL(3, 5);
    TGL(3, 6);
    TGL(4, 2);
    TGL(4, 3);
    TGL(4, 4);
    TGL(4, 5);
    TGL(5, 3);
    TGL(5, 4);
    TGL(10, 5);
    TGL(10, 6);
    TGL(11, 2);
    TGL(11, 3);
    TGL(11, 4);
    TGL(11, 6);
    TGL(11, 7);
    TGL(12, 2);
    TGL(12, 3);
    TGL(12, 4);
    TGL(12, 5);
    TGL(12, 6);
    TGL(13, 3);
    TGL(13, 4);
    TGL(13, 5);
    TGL(19, 5);
    TGL(19, 6);
    TGL(20, 1);
    TGL(20, 2);
    TGL(20, 3);
    TGL(20, 4);
    TGL(20, 6);
    TGL(20, 7);
    TGL(21, 1);
    TGL(21, 2);
    TGL(21, 3);
    TGL(21, 4);
    TGL(21, 5);
    TGL(21, 6);
    TGL(22, 2);
    TGL(22, 3);
    TGL(22, 4);
    TGL(22, 5);
}

// ----------------------------------------------------------------------------

const char *Pulsar::name() const
{
    return "PULSAR";
}

void Pulsar::toggleCellsOn(Simulation *sim) const
{
    TGL(4, 7);
    TGL(4, 8);
    TGL(4, 9);
    TGL(4, 13);
    TGL(4, 14);
    TGL(4, 15);
    TGL(6, 5);
    TGL(6, 10);
    TGL(6, 12);
    TGL(6, 17);
    TGL(7, 5);
    TGL(7, 10);
    TGL(7, 12);
    TGL(7, 17);
    TGL(8, 5);
    TGL(8, 10);
    TGL(8, 12);
    TGL(8, 17);
    TGL(9, 7);
    TGL(9, 8);
    TGL(9, 9);
    TGL(9, 13);
    TGL(9, 14);
    TGL(9, 15);
    TGL(11, 7);
    TGL(11, 8);
    TGL(11, 9);
    TGL(11, 13);
    TGL(11, 14);
    TGL(11, 15);
    TGL(12, 5);
    TGL(12, 10);
    TGL(12, 12);
    TGL(12, 17);
    TGL(13, 5);
    TGL(13, 10);
    TGL(13, 12);
    TGL(13, 17);
    TGL(14, 5);
    TGL(14, 10);
    TGL(14, 12);
    TGL(14, 17);
    TGL(16, 7);
    TGL(16, 8);
    TGL(16, 9);
    TGL(16, 13);
    TGL(16, 14);
    TGL(16, 15);
}

// ----------------------------------------------------------------------------

const char *KoksGalaxy::name() const
{
    return "KOK'S GALAXY";
}

void KoksGalaxy::toggleCellsOn(Simulation *sim) const
{
    TGL(5, 5);
    TGL(5, 6);
    TGL(5, 7);
    TGL(5, 8);
    TGL(5, 9);
    TGL(5, 10);
    TGL(5, 12);
    TGL(5, 13);
    TGL(6, 5);
    TGL(6, 6);
    TGL(6, 7);
    TGL(6, 8);
    TGL(6, 9);
    TGL(6, 10);
    TGL(6, 12);
    TGL(6, 13);
    TGL(7, 12);
    TGL(7, 13);
    TGL(8, 5);
    TGL(8, 6);
    TGL(8, 12);
    TGL(8, 13);
    TGL(9, 5);
    TGL(9, 6);
    TGL(9, 12);
    TGL(9, 13);
    TGL(10, 5);
    TGL(10, 6);
    TGL(10, 12);
    TGL(10, 13);
    TGL(11, 5);
    TGL(11, 6);
    TGL(12, 5);
    TGL(12, 6);
    TGL(12, 8);
    TGL(12, 9);
    TGL(12, 10);
    TGL(12, 11);
    TGL(12, 12);
    TGL(12, 13);
    TGL(13, 5);
    TGL(13, 6);
    TGL(13, 8);
    TGL(13, 9);
    TGL(13, 10);
    TGL(13, 11);
    TGL(13, 12);
    TGL(13, 13);
}

// ----------------------------------------------------------------------------

PatternSelector::PatternSelector()
    : _patterns {
        new StillLifes(),
        new Period2Oscillators(),
        new Pulsar(),
        new KoksGalaxy(),
        new Glider(),
        new GosperGliderGun(),
        new Spaceships(),
    }
    , _n(_patterns.size())
    , _current(0)
{

}

const Pattern *PatternSelector::selectedPattern() const
{
    return _patterns[_current];
}

void PatternSelector::moveForwards()
{
    if (_current == _n-1) _current = 0;
    else ++_current;
}

void PatternSelector::moveBackwards()
{
    if (_current == 0) _current = _n-1;
    else --_current;
}

} // namespace cgl
