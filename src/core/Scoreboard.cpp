#include "core/Scoreboard.h"

#include <string>

bool Scoreboard::ScoreEntryComparator::operator()(const ScoreEntry &left,
                                                  const ScoreEntry &right) const {
    if (left.score != right.score) {
        return left.score > right.score;
    }

    if (left.player_name != right.player_name) {
        return left.player_name < right.player_name;
    }

    return false;
}

void Scoreboard::add_score(const std::string &player_name, std::size_t score) {
    entries.insert(ScoreEntry{player_name, score});
}

std::vector<ScoreEntry> Scoreboard::top_scores(std::size_t max_count) const {
    std::vector<ScoreEntry> result;
    result.reserve(max_count);

    std::size_t count = 0;
    for (const ScoreEntry &entry : entries) {
        if (count >= max_count) {
            break;
        }

        result.push_back(entry);
        count++;
    }

    return result;
}

void Scoreboard::draw(const Rectangle &bounds,
                      const Color &accent_color,
                      std::size_t max_count) const {
    const int scores_title_text_size = 28;
    const float table_header_y_offset = 36.0f;
    const float table_separator_y_offset = 66.0f;
    const float first_table_row_y_offset = 74.0f;
    const float score_line_spacing = 28.0f;
    const int score_line_text_size = 24;
    const float table_line_thickness = 2.0f;

    DrawText("Top Scores",
             (int)bounds.x,
             (int)bounds.y,
             scores_title_text_size,
             accent_color);

    std::vector<ScoreEntry> top = top_scores(max_count);
    if (top.empty()) {
        return;
    }

    float header_y = bounds.y + table_header_y_offset;

    std::string name_header = "Name";
    DrawText(name_header.c_str(),
             (int)bounds.x,
             (int)header_y,
             score_line_text_size,
             accent_color);

    std::string score_header = "Score";
    int score_header_width = MeasureText(score_header.c_str(), score_line_text_size);
    int score_header_x = (int)(bounds.x + bounds.width - (float)score_header_width);
    DrawText(score_header.c_str(),
             score_header_x,
             (int)header_y,
             score_line_text_size,
             accent_color);

    float separator_y = bounds.y + table_separator_y_offset;
    DrawLineEx(Vector2{bounds.x, separator_y},
               Vector2{bounds.x + bounds.width, separator_y},
               table_line_thickness,
               accent_color);

    for (std::size_t i = 0; i < top.size(); ++i) {
        float row_y = bounds.y + first_table_row_y_offset + (float)i * score_line_spacing;

        DrawText(top[i].player_name.c_str(),
                 (int)bounds.x,
                 (int)row_y,
                 score_line_text_size,
                 accent_color);

        std::string score_text = std::to_string(top[i].score);
        int score_width = MeasureText(score_text.c_str(), score_line_text_size);
        int score_x = (int)(bounds.x + bounds.width - (float)score_width);
        DrawText(score_text.c_str(),
                 score_x,
                 (int)row_y,
                 score_line_text_size,
                 accent_color);
    }
}