#ifndef CGL_GRAPHICS_H
#define CGL_GRAPHICS_H

#include <raylib.h>
#include <tuple>

#include "simulation.h"

namespace graphics
{

// Data.
extern int fps;

// Constants.
inline constexpr int HUD_HEIGHT_PX = 20;
inline constexpr int TEXT_HEIGHT_PX = HUD_HEIGHT_PX - 5;

inline constexpr int CELL_SIZE_PX = 5;

inline constexpr int WINDOW_WIDTH_PX = 1440;
static_assert(WINDOW_WIDTH_PX % CELL_SIZE_PX == 0);

inline constexpr int WINDOW_HEIGHT_PX = 900;
static_assert((WINDOW_HEIGHT_PX - HUD_HEIGHT_PX) % CELL_SIZE_PX == 0);

inline constexpr int FPS_INIT_VALUE = 12;
static_assert((FPS_INIT_VALUE & 0x1) == 0);

inline constexpr int FPS_INCREMENT = 2;
inline constexpr int FPS_UPPER_LIMIT = 60;
inline constexpr int FPS_LOWER_LIMIT = 6;

const Color BACKGROUND_COLOR = { 29, 29, 29, 255 };
const Color LIVE_CELL_COLOR = { 0, 255, 0, 255 };
const Color DEAD_CELL_COLOR = { 55, 55, 55, 255 };
const Color TEXT_COLOR = { 255, 0, 0, 255 };

const std::tuple<int, int> INVALID_MOUSE_POSITION = { -1, -1 };

// Types.
enum class Command
{
    NO_COMMAND,
    RUN_OR_PAUSE,
    RANDOMIZE,
    INCREASE_FPS,
    DECREASE_FPS,
    TRY_CLICK_TOGGLE,
    RESET,
    QUIT
};

// Functions.
void initialize();
void finalize();
void beginFrame();
void endFrame();
void increaseFPS();
void decreaseFPS();

Command pollCommand();
std::tuple<int, int> lastMouseCursorPosition();
void drawSimulation(const cgl::Simulation&);

} // namespace graphics

#endif // CGL_GRAPHICS_H
