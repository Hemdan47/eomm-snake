#include "Application.h"

Application::Application() : last_updated_time(0),
                             controller(std::make_unique<Controller>()){}


void Application::run() {
    InitWindow(2 * config.offset + config.cell_size * config.cell_count,
        2 * config.offset + config.cell_size * config.cell_count,
        config.title);
    SetTargetFPS(config.target_fps);

    game = std::make_unique<Game>(config);

    while (!WindowShouldClose()) {
        BeginDrawing();

        if (event_triggered(config.speed)) {
            game->update();
        }

        bool is_running = game->is_running();
        Vector2 current_direction = game->get_snake_current_direction();
        Vector2 direction = controller->handle_movement(current_direction,
                                                        is_running);

        game->set_running(is_running);
        game->set_snake_direction(direction);


        ClearBackground(config.light_sand);
        DrawRectangleLinesEx(Rectangle{(float)config.offset - (float)config.board_frame_offset,
                                       (float)config.offset - (float)config.board_frame_offset,
                                       (float)config.cell_size * config.cell_count + (float)config.board_frame_extra_size,
                                       (float)config.cell_size * config.cell_count + (float)config.board_frame_extra_size},
                                  (float)config.board_frame_line_thickness,
                                          config.burnt_orange);
        DrawText("Eomm Snake",
                 (int)config.offset - config.board_frame_offset,
                 config.ui_text_y,
                 config.ui_text_size,
                 config.burnt_orange);
        DrawText(TextFormat("%i", (int)game->get_score()),
                 (int)config.offset - config.board_frame_offset,
                 (int)(config.offset + config.cell_size * config.cell_count + config.board_frame_extra_size),
                 config.ui_text_size,
                 config.burnt_orange);
        game->draw();

        EndDrawing();
    }

    game.reset();
    CloseWindow();
}

bool Application::event_triggered(double interval) {
    double current_time = GetTime();
    if (current_time - last_updated_time >= interval) {
        last_updated_time = current_time;
        return true;
    }
    return false;
}