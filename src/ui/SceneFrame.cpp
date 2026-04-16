#include "ui/SceneFrame.h"

void SceneFrame::draw(const Config &config) {
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
}