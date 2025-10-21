#ifndef CGL_GRAPHICS_H
#define CGL_GRAPHICS_H

#include <utility>
#include <raylib.h>

#include "simulation.h"
#include "patterns.h"

namespace graphics
{

inline constexpr int CELL_SIZE_S  = 5; // px
inline constexpr int CELL_SIZE_M  = CELL_SIZE_S * 2;
inline constexpr int CELL_SIZE_L  = CELL_SIZE_M * 2;
inline constexpr int CELL_SIZE_XL = CELL_SIZE_L * 2;

inline constexpr int WINDOW_WIDTH_PX = 1440;
inline constexpr int WINDOW_HEIGHT_PX = 910;

inline constexpr int HUD_HEIGHT_PX = 30;
inline constexpr int HUD_WIDTH_PX = WINDOW_WIDTH_PX;
inline constexpr int HUD_TEXT_FONT_SIZE_PX = HUD_HEIGHT_PX - 10;
inline constexpr int HUD_TEXT_SPACING = 2;

inline constexpr int GRID_ORIGIN_Y = HUD_HEIGHT_PX;
inline constexpr int GRID_HEIGHT_PX = WINDOW_HEIGHT_PX - GRID_ORIGIN_Y;
static_assert(GRID_HEIGHT_PX % CELL_SIZE_XL == 0);

[[maybe_unused]] inline constexpr int GRID_ORIGIN_X = 0;
[[maybe_unused]] inline constexpr int GRID_WIDTH_PX = WINDOW_WIDTH_PX;
static_assert(GRID_WIDTH_PX % CELL_SIZE_XL == 0);

inline constexpr int FPS_INIT_VALUE = 12;
static_assert((FPS_INIT_VALUE & 0x1) == 0);

inline constexpr int FPS_LOWER_LIMIT = 4;
inline constexpr int FPS_UPPER_LIMIT = 60;
inline constexpr int FPS_INCREMENT = 2;

enum class Event
{
    NIL,
    CONTROLS_DISPLAY_TOGGLED,
    FPS_TARGET_CHANGED,
    CELL_SIZE_CHANGED,
    RUN_PAUSE_SIM_REQUESTED,
    RANDOMIZE_SIM_REQUESTED,
    RESET_SIM_REQUESTED,
    APPLY_PATTERN_REQUESTED,
    NEXT_PATTERN_REQUESTED,
    PREV_PATTERN_REQUESTED,
    TOGGLE_CELL_REQUESTED,
    DUMP_REQUESTED,
    EXIT_REQUESTED,
};

struct InputEvent
{
    InputEvent(Event e): which(e), row(-1), col(-1) {}

    Event which;
    int row;
    int col;
};

void initialize();
void finalize();
void beginFrame();
void endFrame();
bool increaseFPS();
bool decreaseFPS();
InputEvent pollInput(bool allowCellResizing);
std::pair<int, int> calcSimulationDimensions();
void drawFrame(const cgl::Simulation&, const cgl::PatternSelector& selector);

} // namespace graphics

#endif // CGL_GRAPHICS_H
