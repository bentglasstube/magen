#include "music_screen.h"

void MusicScreen::init() {
  index_ = 0;
  offset_ = 0;
  text_.reset(new Text("text"));
  mgen_.reset(new MusicGenerator(28160));
}

bool MusicScreen::update(Input& input, unsigned int elapsed) {
  offset_ += elapsed * mgen_->frequency() / 1000;

  if (input.key_pressed(SDL_SCANCODE_UP))    mgen_->increment(index_);
  if (input.key_pressed(SDL_SCANCODE_W))     mgen_->increment(index_);
  if (input.key_pressed(SDL_SCANCODE_K))     mgen_->increment(index_);

  if (input.key_pressed(SDL_SCANCODE_DOWN))  mgen_->decrement(index_);
  if (input.key_pressed(SDL_SCANCODE_S))     mgen_->decrement(index_);
  if (input.key_pressed(SDL_SCANCODE_J))     mgen_->decrement(index_);

  if (input.key_pressed(SDL_SCANCODE_LEFT))  --index_;
  if (input.key_pressed(SDL_SCANCODE_A))     --index_;
  if (input.key_pressed(SDL_SCANCODE_H))     --index_;

  if (input.key_pressed(SDL_SCANCODE_RIGHT)) ++index_;
  if (input.key_pressed(SDL_SCANCODE_D))     ++index_;
  if (input.key_pressed(SDL_SCANCODE_L))     ++index_;

  if (input.key_pressed(SDL_SCANCODE_SPACE)) mgen_->reset();

  if (input.key_pressed(SDL_SCANCODE_M)) {
    mgen_->muted() ? mgen_->unmute() : mgen_->mute();
  }

  if (input.key_pressed(SDL_SCANCODE_R)) {
    for (int i = 0; i < 6; ++i) mgen_->set(i, rand() % 16);
  }

  if (input.key_pressed(SDL_SCANCODE_TAB)) {
    mgen_->set_gen(mgen_->get_gen() % 2 + 1);
  }

  if (input.key_pressed(SDL_SCANCODE_Q)) {
    mgen_->set_waveform((mgen_->get_waveform() + 1) % 4);
  }

  if (index_ < 0) index_ = 0;
  if (index_ > 5) index_ = 5;

  return !input.key_pressed(SDL_SCANCODE_ESCAPE);
}

void MusicScreen::draw(Graphics& graphics) const {
  const int color = mgen_->muted() ? 0xff0000ff : 0xffffffff;
  int v1 = mgen_->sample((-640) * 4 + offset_ - offset_ % 512);
  for (int x = 1; x < 128; ++x) {
    const int v2 = mgen_->sample((x - 512) * 4 + offset_ - offset_ % 512);
    const int px = 4 * x + 64;
    graphics.draw_line(px - 4, 128 - v1 / 4, px, 128 - v2 / 4, color);
    v1 = v2;
  }

  char buffer[10];
  snprintf(buffer, 10, "G:%1d", mgen_->get_gen());
  text_->draw(graphics, buffer, 160, 144);

  snprintf(buffer, 10, "W:%1d", mgen_->get_waveform());
  text_->draw(graphics, buffer, 120, 144);

  for (int i = 0; i < 6; ++i) {
    snprintf(buffer, 10, "[%02X]", mgen_->get(i));
    text_->draw(graphics, buffer, 204 + 40 * i, 144);
  }

  text_->draw(graphics, "^^", 212 + 40 * index_, 160);

  text_->draw(graphics, "    r - random", 264, 192);
  text_->draw(graphics, "    m - mute",   264, 208);
  text_->draw(graphics, "    q - waveform", 264, 224);
  text_->draw(graphics, "  tab - generator", 264, 240);
  text_->draw(graphics, "space - reset",  264, 256);
  text_->draw(graphics, "  esc - quit",   264, 272);
}

Screen* MusicScreen::next_screen() {
  return NULL;
}
