#pragma once

#include <memory>

#include "music_generator.h"

#include "screen.h"
#include "text.h"

class MusicScreen : public Screen {
  public:

    void init();
    bool update(const Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;

    Screen* next_screen();

  private:

    int index_, offset_;
    std::unique_ptr<Text> text_;
    std::unique_ptr<MusicGenerator> mgen_;
};
