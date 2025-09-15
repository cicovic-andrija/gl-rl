#include <utility>

#include "graphics.h"
#include "simulation.h"
#include "patterns.h"

cgl::Simulation *makeSimulation()
{
    std::pair<int, int> dimensions = graphics::calcSimulationDimensions();
    return new cgl::Simulation(dimensions.first, dimensions.second);
}

int main()
{
    graphics::initialize();

    cgl::Simulation *sim = makeSimulation();
    cgl::PatternSelector selector;

    bool exit = false;
    while (!exit)
    {
        graphics::InputEvent event = graphics::pollInput(!sim->running() /* allowCellResizing */);
        switch (event.which)
        {
            case graphics::Event::EXIT_REQUESTED:
                exit = true;
                continue;
            case graphics::Event::RUN_PAUSE_SIM_REQUESTED:
                if (sim->running()) sim->pause();
                else sim->run();
                break;
            case graphics::Event::RANDOMIZE_SIM_REQUESTED:
                sim->randomize();
                break;
            case graphics::Event::RESET_SIM_REQUESTED:
                sim->reset();
                break;
            case graphics::Event::APPLY_PATTERN_REQUESTED: {
                selector.selectedPattern()->applyTo(sim);
                break;
            }
            case graphics::Event::NEXT_PATTERN_REQUESTED:
                selector.moveForwards();
                break;
            case graphics::Event::PREV_PATTERN_REQUESTED:
                selector.moveBackwards();
                break;
            case graphics::Event::CELL_SIZE_CHANGED:
                delete sim;
                sim = makeSimulation();
                break;
            case graphics::Event::TOGGLE_CELL_REQUESTED:
                event.flagged ? sim->markCellDead(event.first, event.second)
                    : sim->markCellLive(event.first, event.second);
                break;
            case graphics::Event::DUMP_REQUESTED:
                sim->dump();
                break;
            default:
                break;
        }

        while (graphics::checkClock()) {
            sim->advance();
        }

        graphics::beginFrame();
        graphics::drawFrame(*sim, selector);
        graphics::endFrame();
    }

    graphics::finalize();
    return 0;
}
