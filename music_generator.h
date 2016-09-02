#pragma once

#include "SDL2/SDL.h"

class MusicGenerator {
  public:

    MusicGenerator (int frequency);
    ~MusicGenerator ();

    Uint8 sample(int t) const;
    void audio_callback(Uint8 *stream, int length);

    int frequency() const;

    int get(int n) const;

    void set(int n, int v);
    void increment(int n);
    void decrement(int n);
    void reset();

    bool muted() const;
    void mute();
    void unmute();

  private:
    int freq_, pos_, x_[6];
    bool muted_;
};

void __audio_callback(void *c, Uint8 *stream, int length);
