#include "graphics.h"
#include "simulation.h"
#include <iostream>


int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    graphics::initialize();

    cgl::Simulation sim(
        graphics::WINDOW_HEIGHT_PX / graphics::CELL_SIZE_PX,
        graphics::WINDOW_WIDTH_PX / graphics::CELL_SIZE_PX
    );

    // helper variables
    std::tuple<int, int> position;

    // main game loop (all in single thread)
    bool quit = false;
    while (!quit)
    {
        // 1 - execute a command if available
        switch (graphics::pollCommand()) {
            case graphics::Command::QUIT:
                quit = true;
                continue;
            case graphics::Command::INCREASE_FPS:
                graphics::increaseFPS();
                break;
            case graphics::Command::DECREASE_FPS:
                graphics::decreaseFPS();
                break;
            case graphics::Command::RUN_OR_PAUSE:
                if (sim.running()) sim.pause();
                else sim.run();
                break;
            case graphics::Command::RANDOMIZE:
                sim.randomize();
                break;
            case graphics::Command::RESET:
                sim.reset();
                break;
            case graphics::Command::TRY_CLICK_TOGGLE:
                position = graphics::lastMouseCursorPosition();
                sim.toggleCell(std::get<0>(position), std::get<1>(position));
                break;
            default:
                break;
        }

        // 2 - advance the game to the next generation
        sim.advance();

        // 3 - draw the next generation
        graphics::beginFrame();
        graphics::drawSimulation(sim);
        graphics::endFrame();
    }

    graphics::finalize();
    return 0;
}
