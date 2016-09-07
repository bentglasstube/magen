#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class MusicGenerator {
  public:

    MusicGenerator();
    ~MusicGenerator();

    Uint8 sample(int t) const;
    void audio_callback(Uint8 *stream, int length);

    Uint8 get(int n) const;

    void set(int n, Uint8 v);
    void increment(int n);
    void decrement(int n);
    void reset();

    bool muted() const;
    void mute();
    void unmute();

    void set_gen(int n);
    int get_gen() const;

    void set_waveform(int n);
    int get_waveform() const;

  private:
    int sqr(int t) const;
    int saw(int t) const;
    int tri(int t) const;
    int sin(int t) const;

    int pos_, x_[6], generator_;
    int waveform_;
    bool muted_;
    SDL_AudioDeviceID device_;
};
