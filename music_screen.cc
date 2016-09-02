#include "music_screen.h"

void MusicScreen::init() {
  index_ = 0;
  offset_ = 0;
  text_.reset(new Text("text"));
  mgen_.reset(new MusicGenerator(44100));
}

bool MusicScreen::update(Input& input, unsigned int elapsed) {
  offset_ += elapsed * mgen_->frequency() / 1000;

  if (input.key_pressed(SDL_SCANCODE_UP))    mgen_->increment(index_);
  if (input.key_pressed(SDL_SCANCODE_DOWN))  mgen_->decrement(index_);

  if (input.key_pressed(SDL_SCANCODE_LEFT))  --index_;
  if (input.key_pressed(SDL_SCANCODE_RIGHT)) ++index_;

  if (input.key_pressed(SDL_SCANCODE_SPACE)) mgen_->reset();

  if (input.key_pressed(SDL_SCANCODE_M)) {
    mgen_->muted() ? mgen_->unmute() : mgen_->mute();
  }

  if (input.key_pressed(SDL_SCANCODE_R)) {
    for (int i = 0; i < 6; ++i) mgen_->set(i, rand() % 16);
  }

  if (index_ < 0) index_ = 0;
  if (index_ > 5) index_ = 5;

  return !input.key_pressed(SDL_SCANCODE_ESCAPE);
}

void MusicScreen::draw(Graphics& graphics) const {
  const int color = mgen_->muted() ? 0xff0000ff : 0xffffffff;
  for (int x = 0; x < 640; ++x) {
    const int v = mgen_->sample((x - 640) * 4 + offset_ - offset_ % 512);
    graphics.draw_pixel(x, 256 - v / 4, color);
  }

  char buffer[10];
  for (int i = 0; i < 6; ++i) {
    snprintf(buffer, 10, "[%02d]", mgen_->get(i));
    text_->draw(graphics, buffer, 204 + 40 * i, 272);
  }

  text_->draw(graphics, "^^", 212 + 40 * index_, 288);
  text_->draw(graphics, "Esc to quit", 320, 340, Text::Alignment::CENTER);
}

Screen* MusicScreen::next_screen() {
  return NULL;
}
