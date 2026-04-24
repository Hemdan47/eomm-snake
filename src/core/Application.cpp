#include "core/Application.h"

#include "modes/ClassicMode.h"
#include "modes/WrapAroundMode.h"
#include "ui/SceneFrame.h"

Application::Application() : menu(std::make_unique<Menu>(config)),
                             current_scene(Scene::Menu),
                             last_updated_time(0){}


void Application::run() {
    InitWindow(2 * config.offset + config.cell_size * config.cell_count,
        2 * config.offset + config.cell_size * config.cell_count,
        config.title);
    InitAudioDevice();
    SetTargetFPS(config.target_fps);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(config.light_sand);

        switch (current_scene) {
            case Scene::Game:
                if (!game) {
                    current_scene = Scene::Menu;
                    break;
                }

                if (event_triggered(config.speed)) {
                    bool was_running = game->is_running();
                    game->update();

                    if (was_running && !game->is_running()) {
                        if (menu) {
                            menu->add_score(game->get_last_score());
                        }
                        current_scene = Scene::Menu;
                        break;
                    }
                }

                if (game) {
                    game->handle_input();

                    SceneFrame::draw(config);
                    DrawText(TextFormat("%i", (int)game->get_score()),
                             (int)config.offset - config.board_frame_offset,
                             (int)(config.offset + config.cell_size * config.cell_count + config.board_frame_extra_size),
                             config.ui_text_size,
                             config.burnt_orange);
                    game->draw();
                }
                break;

            case Scene::Menu: {
                if (menu) {
                    menu->draw();
                    menu->update();

                    if (menu->consume_start_request()) {
                        game = create_game_for_selected_mode(menu->get_selected_mode());
                        current_scene = Scene::Game;
                        last_updated_time = GetTime();
                    }
                }
                break;
            }
        }

        EndDrawing();
    }

    game.reset();
    if (IsAudioDeviceReady()) {
        CloseAudioDevice();
    }
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

std::unique_ptr<Game> Application::create_game_for_selected_mode(GameMode mode) {
    if (mode == GameMode::WrapAround) {
        return std::make_unique<WrapAroundMode>(config);
    }

    return std::make_unique<ClassicMode>(config);
}
