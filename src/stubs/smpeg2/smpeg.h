#pragma once

#include <SDL2/SDL.h>

typedef struct _SMPEG SMPEG;

typedef struct {
    Uint32 type;
    int width;
    int height;
    int current_frame;
    double current_fps;
    char audio_string[80];
    int audio_current_frame;
    Uint32 current_offset;
    Uint32 total_size;
    double current_time;
    double total_time;
} SMPEG_Info;

static inline SMPEG *SMPEG_new_rwops(SDL_RWops *src, SMPEG_Info *info, int freesrc, int sdl_audio) {
    (void)src; (void)info; (void)freesrc; (void)sdl_audio;
    return nullptr;
}

static inline void SMPEG_wantedSpec(SMPEG *mpeg, SDL_AudioSpec *wanted) {
    (void)mpeg; (void)wanted;
}

static inline void SMPEG_delete(SMPEG *mpeg) {
    (void)mpeg;
}
