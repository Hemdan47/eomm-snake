#include "core/Menu.h"

#include "ui/SceneFrame.h"

Menu::Menu(Config &config)
    : config(config),
      selected_mode(GameMode::Classic),
      start_requested(false) {
    buttons.push_back(create_menu_button("Play", 0, MenuAction::Play));
    buttons.push_back(create_menu_button("Classic Mode", 1, MenuAction::SelectClassicMode));
    buttons.push_back(create_menu_button("Wrap Around Mode", 2, MenuAction::SelectWrapAroundMode));
}

void Menu::update(MenuController &controller) {
    MenuAction action = controller.handle_menu(buttons);

    switch (action) {
        case MenuAction::SelectClassicMode:
            selected_mode = GameMode::Classic;
            break;
        case MenuAction::SelectWrapAroundMode:
            selected_mode = GameMode::WrapAround;
            break;
        case MenuAction::Play:
            start_requested = true;
            break;
        case MenuAction::None:
            break;
    }
}

void Menu::draw() const {
    SceneFrame::draw(config);

    for (const MenuButtonDescriptor &descriptor : buttons) {
        descriptor.button.draw(config.burnt_orange,
                               config.light_sand,
                               is_button_selected(descriptor.action));
    }
}

bool Menu::consume_start_request() {
    bool was_requested = start_requested;
    start_requested = false;
    return was_requested;
}

GameMode Menu::get_selected_mode() const {
    return selected_mode;
}

MenuButtonDescriptor Menu::create_menu_button(const char *label,
                                              int index,
                                              MenuAction action) const {
    float board_size = (float)config.cell_size * (float)config.cell_count;
    float button_width = board_size * 0.7f;
    float button_height = 70.0f;
    float x = (float)config.offset + (board_size - button_width) / 2.0f;
    float y = (float)config.offset + 170.0f + 110.0f * (float)index;
    return MenuButtonDescriptor{
        Button(Rectangle{x, y, button_width, button_height}, label, 34),
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