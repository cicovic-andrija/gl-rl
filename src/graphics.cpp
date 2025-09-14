#include "graphics.h"

namespace graphics
{

namespace globals
{
    int fps = FPS_INIT_VALUE;
    int cellSize = CELL_SIZE_L;
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
    SetTargetFPS(globals::fps);
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

bool increaseFPS()
{
    if (globals::fps < FPS_UPPER_LIMIT) {
        globals::fps += FPS_INCREMENT;
        SetTargetFPS(globals::fps);
        return true;
    }
    return false;
}

bool decreaseFPS()
{
    if (globals::fps > FPS_LOWER_LIMIT) {
        globals::fps -= FPS_INCREMENT;
        SetTargetFPS(globals::fps);
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
        return increaseFPS() ? Event::FPS_TARGET_CHANGED : Event::NIL;
    }
    if (IsKeyPressed(KEY_S)) {
        return decreaseFPS() ? Event::FPS_TARGET_CHANGED : Event::NIL;
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
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 mousePosition = GetMousePosition();
        if (mousePosition.y >= GRID_ORIGIN_Y) {
            InputEvent event(Event::TOGGLE_CELL_REQUESTED);
            event.row = (mousePosition.y - GRID_ORIGIN_Y) / globals::cellSize;
            event.col = mousePosition.x / globals::cellSize;
            return event;
        }
        return Event::NIL;
    }

    return Event::NIL;
}

void drawHUD(const cgl::Simulation &sim)
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
        hud = "run/pause (SPACE), (f)aster, (s)lower, (r)eset, randomi(z)e, (e)nlarge, s(h)rink, (c)lose";
    }
    else
    {
        hud = TextFormat(
            "[fps %02i] [%-11s] [gen %5ld] | [%s] | (c)ontrols ",
            globals::fps,
            sim.running()
                ? option1Messages[secOrdinal % (sizeof(option1Messages) / sizeof(option1Messages[0]))]
                : option0Messages[secOrdinal % (sizeof(option0Messages) / sizeof(option0Messages[0]))],
            sim.age(),
            "pattern GLIDER GUN"
        );
    }

    Vector2 position = { HUD_POS_X, HUD_POS_Y };
    DrawTextEx(globals::monoFont, hud, position, HUD_TEXT_HEIGHT_PX, HUD_TEXT_SPACING, TEXT_COLOR);
}

std::pair<int, int> calcSimulationDimensions()
{
    return std::make_pair(GRID_HEIGHT_PX / globals::cellSize, GRID_WIDTH_PX / globals::cellSize);
}

void drawSimulation(const cgl::Simulation& sim)
{
    drawHUD(sim);

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
