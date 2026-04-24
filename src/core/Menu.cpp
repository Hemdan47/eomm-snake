#include "core/Menu.h"

#include <cstddef>
#include <string>

#include "ui/SceneFrame.h"

Menu::Menu(Config &config)
    : config(config),
      selected_mode(GameMode::Classic),
      name_input(create_name_input_box()),
      start_requested(false) {
    const int play_button_index = 0;
    const int classic_button_index = 1;
    const int wrap_button_index = 2;

    buttons.push_back(create_menu_button("Play", play_button_index, MenuAction::Play));
    buttons.push_back(create_menu_button("Classic Mode", classic_button_index, MenuAction::SelectClassicMode));
    buttons.push_back(create_menu_button("Wrap Around Mode", wrap_button_index, MenuAction::SelectWrapAroundMode));
}

void Menu::update() {
    name_input.update();

    MenuAction action = controller.handle_menu(buttons);

    switch (action) {
        case MenuAction::SelectClassicMode:
            selected_mode = GameMode::Classic;
            break;
        case MenuAction::SelectWrapAroundMode:
            selected_mode = GameMode::WrapAround;
            break;
        case MenuAction::Play:
            if (name_input.get_text().empty()) {
                name_input.set_text("Player");
            }
            start_requested = true;
            break;
        case MenuAction::None:
            break;
    }
}

void Menu::draw() const {
    const int player_name_text_size = 28;
    const float player_name_y_offset = 32.0f;

    const float scores_title_y_offset = 22.0f;
    const std::size_t top_scores_limit = 3;

    SceneFrame::draw(config);

    for (const MenuButtonDescriptor &descriptor : buttons) {
        descriptor.button.draw(config.burnt_orange,
                               config.light_sand,
                               is_button_selected(descriptor.action));
    }

    Rectangle input_bounds = name_input.get_bounds();
    std::string player_name_title = "Player Name";
    int player_name_width = MeasureText(player_name_title.c_str(), player_name_text_size);
    int player_name_x = (int)(input_bounds.x + (input_bounds.width - (float)player_name_width) / 2.0f);
    DrawText(player_name_title.c_str(),
             player_name_x,
             (int)(input_bounds.y - player_name_y_offset),
             player_name_text_size,
             config.burnt_orange);
    name_input.draw(config.burnt_orange, config.light_sand);

    float scores_y = input_bounds.y + input_bounds.height + scores_title_y_offset;
    scoreboard.draw(Rectangle{input_bounds.x, scores_y, input_bounds.width, 0.0f},
                    config.burnt_orange,
                    top_scores_limit);
}

void Menu::add_score(std::size_t score) {
    std::string player_name = name_input.get_text();
    if (player_name.empty()) {
        player_name = "Player";
    }

    scoreboard.add_score(player_name, score);
}

bool Menu::consume_start_request() {
    bool was_requested = start_requested;
    start_requested = false;
    return was_requested;
}

GameMode Menu::get_selected_mode() const {
    return selected_mode;
}

TextInputBox Menu::create_name_input_box() const {
    const float controls_width_factor = 0.7f;
    const float name_input_height = 62.0f;
    const float name_input_y = 500.0f;
    const float menu_vertical_shift = -25.0f;
    const int name_input_text_size = 28;
    const std::size_t name_input_max_length = 14;

    float board_size = (float)config.cell_size * (float)config.cell_count;
    float input_width = board_size * controls_width_factor;
    float x = (float)config.offset + (board_size - input_width) / 2.0f;
    float y = (float)config.offset + name_input_y + menu_vertical_shift;
    return TextInputBox(Rectangle{x, y, input_width, name_input_height},
                        name_input_text_size,
                        name_input_max_length);
}

MenuButtonDescriptor Menu::create_menu_button(const std::string &label,
                                              int index,
                                              MenuAction action) const {
    const float controls_width_factor = 0.7f;
    const float menu_button_height = 70.0f;
    const float menu_button_start_y = 170.0f;
    const float menu_button_spacing_y = 110.0f;
    const float menu_vertical_shift = -25.0f;
    const int menu_button_text_size = 34;

    float board_size = (float)config.cell_size * (float)config.cell_count;
    float button_width = board_size * controls_width_factor;
    float x = (float)config.offset + (board_size - button_width) / 2.0f;
    float y = (float)config.offset + menu_button_start_y + menu_button_spacing_y * (float)index + menu_vertical_shift;
    return MenuButtonDescriptor{
        Button(Rectangle{x, y, button_width, menu_button_height}, label, menu_button_text_size),
        action
    };
}

bool Menu::is_button_selected(MenuAction action) const {
    switch (action) {
        case MenuAction::SelectClassicMode:
            return selected_mode == GameMode::Classic;
        case MenuAction::SelectWrapAroundMode:
            return selected_mode == GameMode::WrapAround;
        case MenuAction::Play:
        case MenuAction::None:
            return false;
    }

    return false;
}