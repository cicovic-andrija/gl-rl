#include "graphics.h"

namespace graphics
{

namespace globals
{
    int cellSize = CELL_SIZE_L;
    int clockTicksHz = 1;
    bool showControls = false;
    Font monoFont;
}

const Color BACKGROUND_COLOR = { 29, 29, 29, 255 };
const Color LIVE_CELL_COLOR = { 0, 255, 0, 255 };
const Color DEAD_CELL_COLOR = { 55, 55, 55, 255 };
const Color TEXT_COLOR = { 255, 255, 255, 255 };

void initialize()
{
    InitWindow(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX, "Conway's Game of Life");
    SetExitKey(KEY_NULL);
    SetTargetFPS(TARGET_FPS);
    globals::monoFont = LoadFont("resources/JetBrainsMono-Bold.ttf");
}

void finalize()
{
    CloseWindow();
}

void beginFrame()
{
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
}

void endFrame()
{
    EndDrawing();
}

bool checkClock()
{
    static float accumulator = 0.0f;
    accumulator += GetFrameTime();;
    if (accumulator >= 1.0f/globals::clockTicksHz) {
        accumulator -= 1.0f/globals::clockTicksHz;
        return true;
    }
    return false;
}

bool tickFaster()
{
    if (globals::clockTicksHz < 16) {
        globals::clockTicksHz += 1;
        return true;
    }
    return false;
}

bool tickSlower()
{
    if (globals::clockTicksHz > 1) {
        globals::clockTicksHz -= 1;
        return true;
    }
    return false;
}

bool increaseCellSize()
{
    switch (globals::cellSize)
    {
        case CELL_SIZE_S:
            globals::cellSize = CELL_SIZE_M;
            break;
        case CELL_SIZE_M:
            globals::cellSize = CELL_SIZE_L;
            break;
        case CELL_SIZE_L:
            globals::cellSize = CELL_SIZE_XL;
            break;
        default:
            return false;
    }
    return true;
}

bool decreaseCellSize()
{
    switch (globals::cellSize)
    {
        case CELL_SIZE_M:
            globals::cellSize = CELL_SIZE_S;
            break;
        case CELL_SIZE_L:
            globals::cellSize = CELL_SIZE_M;
            break;
        case CELL_SIZE_XL:
            globals::cellSize = CELL_SIZE_L;
            break;
        default:
            return false;
    }
    return true;
}

InputEvent pollInput(bool allowCellResizing)
{
    if (WindowShouldClose()) {
        return Event::EXIT_REQUESTED;
    }
    if (IsKeyPressed(KEY_C)) {
        globals::showControls = !globals::showControls;
        return Event::CONTROLS_DISPLAY_TOGGLED;
    }
    if (IsKeyPressed(KEY_F)) {
        return tickFaster() ? Event::FPS_TARGET_CHANGED : Event::NIL;
    }
    if (IsKeyPressed(KEY_S)) {
        return tickSlower() ? Event::FPS_TARGET_CHANGED : Event::NIL;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        return Event::RUN_PAUSE_SIM_REQUESTED;
    }
    if (allowCellResizing && IsKeyPressed(KEY_E)) {
        return increaseCellSize() ? Event::CELL_SIZE_CHANGED : Event::NIL;
    }
    if (allowCellResizing && IsKeyPressed(KEY_H)) {
        return decreaseCellSize() ? Event::CELL_SIZE_CHANGED : Event::NIL;
    }
    if (IsKeyPressed(KEY_R)) {
        return Event::RESET_SIM_REQUESTED;
    }
    if (IsKeyPressed(KEY_Z)) {
        return Event::RANDOMIZE_SIM_REQUESTED;
    }
    if (IsKeyPressed(KEY_A)) {
        return Event::APPLY_PATTERN_REQUESTED;
    }
    if (IsKeyPressed(KEY_N)) {
        return Event::NEXT_PATTERN_REQUESTED;
    }
    if (IsKeyPressed(KEY_P)) {
        return Event::PREV_PATTERN_REQUESTED;
    }
    if (IsKeyPressed(KEY_D)) {
        return Event::DUMP_REQUESTED;
    }

    auto clickEvent = [](bool flag = false) ->InputEvent {
        Vector2 mousePosition = GetMousePosition();
        if (mousePosition.y >= GRID_ORIGIN_Y) {
            InputEvent event(Event::TOGGLE_CELL_REQUESTED);
            event.first = (mousePosition.y - GRID_ORIGIN_Y) / globals::cellSize;
            event.second = mousePosition.x / globals::cellSize;
            event.flagged = flag;
            return event;
        }
        return Event::NIL;
    };
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        return clickEvent();
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        return clickEvent(true /* flag the event*/);
    }

    return Event::NIL;
}

void drawHUD(const cgl::Simulation &sim, const cgl::PatternSelector& selector)
{
    static const char *option0Messages[] = {
        "GAME PAUSED",
        "",
    };
    static const char *option1Messages[] = {
        "RUNNING.",
        "RUNNING..",
        "RUNNING...",
        "RUNNING....",
    };

    const char *hud = nullptr;
    int secOrdinal = static_cast<int>(GetTime());

    if (globals::showControls)
    {
        hud = "run/pause (SPACE), (f)aster, (s)lower, (r)eset, randomi(z)e, (e)nlarge, s(h)rink, (a)pply, (n)ext, (p)revious, (c)lose";
    }
    else
    {
        hud = TextFormat(
            "[gen/sec %2i] [%-11s] [gen %5ld] | [p(a)ttern %20s] | (c)ontrols ",
            globals::clockTicksHz,
            sim.running()
                ? option1Messages[secOrdinal % (sizeof(option1Messages) / sizeof(option1Messages[0]))]
                : option0Messages[secOrdinal % (sizeof(option0Messages) / sizeof(option0Messages[0]))],
            sim.age(),
            selector.selectedPattern()->name()
        );
    }

    Vector2 position = { HUD_POS_X, HUD_POS_Y };
    DrawTextEx(globals::monoFont, hud, position, HUD_TEXT_HEIGHT_PX, HUD_TEXT_SPACING, TEXT_COLOR);
}

std::pair<int, int> calcSimulationDimensions()
{
    return std::make_pair(GRID_HEIGHT_PX / globals::cellSize, GRID_WIDTH_PX / globals::cellSize);
}

void drawFrame(const cgl::Simulation& sim, const cgl::PatternSelector& selector)
{
    drawHUD(sim, selector);

    const cgl::Grid *grid = sim.currentGeneration();
    for (int row = 0; row < grid->sizeRows(); ++row)
    {
        for (int col = 0; col < grid->sizeColumns(); ++col)
        {
            Color color = grid->cellState(row, col) == cgl::LIVE ? LIVE_CELL_COLOR : DEAD_CELL_COLOR;
            DrawRectangle(
                col * globals::cellSize,
                row * globals::cellSize + HUD_HEIGHT_PX,
                globals::cellSize-1,
                globals::cellSize-1,
                color
            );
        }
    }
}

} // namespace graphics
