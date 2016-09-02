#include "music_generator.h"

MusicGenerator::MusicGenerator(int frequency)
  : freq_(frequency), pos_(0), muted_(false)
{
  for (int i = 0; i < 6; ++i) x_[i] = 0;

  SDL_AudioSpec spec;

  spec.freq = freq_;
  spec.format = AUDIO_U8;
  spec.channels = 1;
  spec.samples = 1024;
  spec.callback = __audio_callback;
  spec.userdata = this;

  SDL_OpenAudio(&spec, NULL);

  SDL_PauseAudio(0);
}

MusicGenerator::~MusicGenerator() {
  SDL_CloseAudio();
}

void MusicGenerator::audio_callback(Uint8 *stream, int length) {
  for (int i = 0; i < length; ++i) {
    stream[i] = muted_ ? 0 : sample(pos_ + i);
  }

  pos_ += length;
}

Uint8 MusicGenerator::sample(int t) const {
  return (t >> x_[0] | t | t >> x_[1]) * x_[2] +
    x_[3] * (t & t >> x_[4] | t >> x_[5]);
}

int MusicGenerator::frequency() const {
  return freq_;
}

int MusicGenerator::get(int n) const {
  return x_[n];
}

void MusicGenerator::set(int n, int v) {
  x_[n] = v;
}

void MusicGenerator::increment(int n) {
  ++x_[n];
}

void MusicGenerator::decrement(int n) {
  --x_[n];
}

void MusicGenerator::reset() {
  for (int i = 0; i < 6; ++i) x_[i] = 0;
}

bool MusicGenerator::muted() const {
  return muted_;
}

void MusicGenerator::mute() {
  muted_ = true;
}

void MusicGenerator::unmute() {
  muted_ = false;
}

void __audio_callback(void *userdata, Uint8 *stream, int length) {
  MusicGenerator *gen = (MusicGenerator *)userdata;
  gen->audio_callback(stream, length);
}
