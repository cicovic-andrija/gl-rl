#include <utility>

#include "graphics.h"
#include "simulation.h"

cgl::Simulation *makeSimulation()
{
    std::pair<int, int> dimensions = graphics::calcSimulationDimensions();
    return new cgl::Simulation(dimensions.first, dimensions.second);
}

int main()
{
    graphics::initialize();

    cgl::Simulation *sim = makeSimulation();

    bool exit = false;
    while (!exit)
    {
        // 1 - execute a request if available
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
                // does nothing if the sim is running
                sim->randomize();
                break;
            case graphics::Event::RESET_SIM_REQUESTED:
                // does nothing if the sim is running
                sim->reset();
                break;
            case graphics::Event::CELL_SIZE_CHANGED:
                delete sim;
                sim = makeSimulation();
                break;
            case graphics::Event::TOGGLE_CELL_REQUESTED:
                // does nothing if the sim is running
                sim->toggleCell(event.row, event.col);
                break;
            default:
                break;
        }

        // 2 - advance the game to the next generation
        sim->advance();

        // 3 - draw the next generation
        graphics::beginFrame();
        graphics::drawSimulation(*sim);
        graphics::endFrame();
    }

    graphics::finalize();
    return 0;
}
