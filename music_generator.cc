#include <cmath>
#include "music_generator.h"

MusicGenerator::MusicGenerator(int frequency)
  : freq_(frequency), pos_(0), generator_(1), waveform_(0), muted_(false)
{
  for (int i = 0; i < 6; ++i) x_[i] = 0;

  SDL_AudioSpec spec;

  spec.freq = freq_;
  spec.format = AUDIO_U8;
  spec.channels = 1;
  spec.samples = 128;
  spec.callback = __audio_callback;
  spec.userdata = this;

  device_ = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);

  SDL_PauseAudioDevice(device_, 0);
}

MusicGenerator::~MusicGenerator() {
  SDL_CloseAudioDevice(device_);
}

void MusicGenerator::audio_callback(Uint8 *stream, int length) {
  for (int i = 0; i < length; ++i) {
    stream[i] = muted_ ? 0 : sample(pos_ + i);
  }

  pos_ += length;
}

int MusicGenerator::saw(int t) const {
    return t;
}

int MusicGenerator::sqr(int t) const {
    int phase = t & 0xff;
    t &= ~0xff;
    if (phase < 128) {
        phase = 0;
    } else {
        phase = 255;
    }
    return t | phase;
}

int MusicGenerator::tri(int t) const {
    int phase = t & 0xff;
    t &= ~0xff;
    if (phase < 128) {
        phase *= 2;
    } else {
        phase = 255 - 2*(phase - 128);

    }
    return t | phase;
}

int MusicGenerator::sin(int t) const {
    int phase = t & 0xff;
    t &= ~0xff;

    phase = 128 + 127 * std::sin(2.0 * M_PI * double(phase) / 255.0);
    return t | phase;
}

Uint8 MusicGenerator::sample(int t) const {
  const int a = x_[0];
  const int b = x_[1];
  const int c = x_[2];
  const int d = x_[3];
  const int e = x_[4];
  const int f = x_[5];

  switch (waveform_) {
    case 0: t = saw(t); break;
    case 1: t = sqr(t); break;
    case 2: t = tri(t); break;
    case 3: t = sin(t); break;
    default:
        ; // Do nothing, same as sawtooth wave.
  }

  switch (generator_) {

    case 1:

      return (t >> a | t | t >> b) * c + d * ((t & t >> e) | t >> f);

    case 2:

      return (t * a & t >> b) | (t * c & t >> d) | (t * e & t >> f);

    default:

      return 0;
  }
}

int MusicGenerator::frequency() const {
  return freq_;
}

Uint8 MusicGenerator::get(int n) const {
  return x_[n];
}

void MusicGenerator::set(int n, Uint8 v) {
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

void MusicGenerator::set_gen(int n) {
  generator_ = n;
}

int MusicGenerator::get_gen() const {
  return generator_;
}

void MusicGenerator::set_waveform(int n) {
  waveform_ = n;
}

int MusicGenerator::get_waveform() const {
  return waveform_;
}

void __audio_callback(void *userdata, Uint8 *stream, int length) {
  MusicGenerator *gen = (MusicGenerator *)userdata;
  gen->audio_callback(stream, length);
}
