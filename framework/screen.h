#pragma once

#include <string>

#include "graphics.h"
#include "input.h"

class Screen {

  public:

    virtual void init() {}
    virtual bool update(Input& input, unsigned int elapsed) = 0;
    virtual void draw(Graphics& graphics) const = 0;
    virtual Screen* next_screen() = 0;
    virtual std::string get_music_track() const { return ""; }

    bool process_input(Input& input);
};
