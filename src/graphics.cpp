#include "graphics.h"
#include <iostream>

namespace graphics
{

int fps = FPS_INIT_VALUE;
Font monoFont;

void initialize()
{
    InitWindow(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX, "Conway's Game of Life"); // TODO move const
    SetTargetFPS(fps);
    monoFont = LoadFont("resources/JetBrainsMono-Bold.ttf");
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

void increaseFPS()
{
    if (fps < FPS_UPPER_LIMIT) fps += FPS_INCREMENT;
    SetTargetFPS(fps);
}

void decreaseFPS()
{
    if (fps > FPS_LOWER_LIMIT) fps -= FPS_INCREMENT;
    SetTargetFPS(fps);
}

Command pollCommand()
{
    if (WindowShouldClose()) {
        return Command::QUIT;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        return Command::RUN_OR_PAUSE;
    }
    if (IsKeyPressed(KEY_F)) {
        return Command::INCREASE_FPS;
    }
    if (IsKeyPressed(KEY_S)) {
        return Command::DECREASE_FPS;
    }
    if (IsKeyPressed(KEY_R)) {
        return Command::RESET;
    }
    if (IsKeyPressed(KEY_Q)) {
        return Command::RANDOMIZE;
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        return Command::TRY_CLICK_TOGGLE;
    }
    return Command::NO_COMMAND;
}

std::tuple<int, int> lastMouseCursorPosition()
{
    Vector2 mousePosition = GetMousePosition();
    if (mousePosition.y - HUD_HEIGHT_PX < 0) return INVALID_MOUSE_POSITION;
    return { (mousePosition.y - HUD_HEIGHT_PX) / CELL_SIZE_PX, mousePosition.x / CELL_SIZE_PX };
}

const char *activityMessageForHUD(int option)
{
    static const char *option0Messages[] = {
        "PAUSED",
        "",
    };
    static const char *option1Messages[] = {
        "RUNNING",
        "RUNNING.",
        "RUNNING..",
        "RUNNING...",
    };

    int secOrdinal = static_cast<int>(GetTime());
    switch (option)
    {
    case 0:
        return option0Messages[secOrdinal % (sizeof(option0Messages) / sizeof(option0Messages[0]))];
        break;
    case 1:
        return option1Messages[secOrdinal % (sizeof(option1Messages) / sizeof(option1Messages[0]))];
        break;
    }

    return "???";
}

void drawHUD([[maybe_unused]] const cgl::Simulation &sim)
{
    Vector2 position;
    position.x = 5;
    position.y = (HUD_HEIGHT_PX - TEXT_HEIGHT_PX)/2;
    DrawTextEx(
        monoFont,
        TextFormat(
            "FPS: %02i ### %-10s ### %s",
            fps,
            activityMessageForHUD(sim.running()),
            "TEMPLATE: GLIDER GUN"
        ),
        position,
        TEXT_HEIGHT_PX,
        2,
        TEXT_COLOR
    );
    // DrawText(
    //     TextFormat(
    //         "FPS: %02i | %-10s",
    //         fps,
    //         activityMessageForHUD(sim.running())
    //     ),
    //     5,
    //     (HUD_HEIGHT_PX - TEXT_HEIGHT_PX) / 2,
    //     TEXT_HEIGHT_PX,
    //     TEXT_COLOR
    // );
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
                col * CELL_SIZE_PX,
                row * CELL_SIZE_PX + HUD_HEIGHT_PX,
                CELL_SIZE_PX-1,
                CELL_SIZE_PX-1,
                color
            );
        }
    }
}

} // namespace graphics
