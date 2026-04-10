#include "Game.h"

#include <memory>

Game::Game(Config &config) : config(config),
                             snake(std::make_unique<Snake>(config)),
                             running(true),
                             score(0)
{
    std::deque<Vector2> snake_body = snake->get_body();
    food = std::make_unique<Food>(config , generate_random_position(snake_body));

    InitAudioDevice();
    eat_sound = LoadSound("resources/sounds/eat.mp3");
    wall_sound = LoadSound("resources/sounds/wall.mp3");
}

Game::~Game() {
    UnloadSound(eat_sound);
    UnloadSound(wall_sound);
    CloseAudioDevice();
}

void Game::update() {
    if (running) {
        bool add = check_collision_with_food();
        snake->update(add);
        bool game_over = check_collision_with_wall() || check_collision_with_tail();
        if (game_over) {
            this->game_over();
        }
    }
}

void Game::draw() {
    food->draw();
    snake->draw();
}

bool Game::check_collision_with_food() {
    std::deque<Vector2> snake_body = snake->get_body();
    if (Vector2Equals(snake_body.front(), food->get_position())){
        food->set_position(generate_random_position(snake_body));
        score++;
        PlaySound(eat_sound);
        return true;
    }
    return false;
}
bool Game::check_collision_with_wall() {
    std::deque<Vector2> snake_body = snake->get_body();
    if (snake_body.front().x == config.cell_count
        || snake_body.front().x == -1
        || snake_body.front().y == config.cell_count
        || snake_body.front().y == -1)
    {
        return true;
    }
    return false;
}

bool Game::check_collision_with_tail() {
    std::deque<Vector2> snake_body = snake->get_body();
    Vector2 head = snake_body.front();
    snake_body.pop_front();
    // pop the head so we check if any cell except the head collide with the head
    if (check_element_in_deque(head , snake_body)) {
        return true;
    }

    return false;
}

void Game::game_over() {
    std::deque<Vector2> snake_body = snake->get_body();
    snake->reset();
    food->set_position(generate_random_position(snake_body));
    running = false;
    score = 0;
    PlaySound(wall_sound);
}

Vector2 Game::generate_random_cell() {
    float x = GetRandomValue(0 , config.cell_count - 1);
    float y = GetRandomValue(0 , config.cell_count - 1);

    return Vector2{x,y};
}

bool Game::check_element_in_deque(Vector2 element, std::deque<Vector2>snake_body) {
    for (auto &node : snake_body) {
        if (Vector2Equals(node , element)) {
            return true;
        }
    }

    return false;
}

Vector2 Game::generate_random_position(std::deque<Vector2>snake_body) {
    Vector2 position = generate_random_cell();
    while (check_element_in_deque(position , snake_body)) {
        position = generate_random_cell();
    }

    return position;
}

Vector2 Game::get_snake_current_direction() {
    return snake->get_direction();
}

void Game::set_snake_direction(Vector2 direction) {
    snake->set_direction(direction);
}

bool Game::is_running() {
    return running;
}

void Game::set_running(bool running) {
    this->running = running;
}

std::size_t Game::get_score() {
    return score;
}

