#ifndef EOMM_SNAKE_SCOREBOARD_H
#define EOMM_SNAKE_SCOREBOARD_H

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "raylib.h"

struct ScoreEntry {
    std::string player_name;
    std::size_t score;
};

class Scoreboard {
public:
    void add_score(const std::string &player_name, std::size_t score);
    std::vector<ScoreEntry> top_scores(std::size_t max_count) const;
    void draw(const Rectangle &bounds, const Color &accent_color, std::size_t max_count) const;

private:
    struct ScoreEntryComparator {
        bool operator()(const ScoreEntry &left, const ScoreEntry &right) const;
    };

    std::multiset<ScoreEntry, ScoreEntryComparator> entries;
};

#endif //EOMM_SNAKE_SCOREBOARD_H