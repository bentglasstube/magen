#pragma once

#include <memory>

#include "music_generator.h"

#include "framework/graphics.h"
#include "framework/input.h"
#include "framework/screen.h"
#include "framework/text.h"

class MusicScreen : public Screen {
  public:

    void init();
    bool update(Input& input, unsigned int elapsed);
    void draw(Graphics& graphics) const;

    Screen* next_screen();

  private:

    int index_, offset_;
    std::unique_ptr<Text> text_;
    std::unique_ptr<MusicGenerator> mgen_;
};
