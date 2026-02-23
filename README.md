# Umineko Web

ONScripter-RU compiled to WebAssembly via Emscripten. Runs Umineko no Naku Koro ni in the browser.

## Prerequisites

- Docker and Docker Compose

## Building and Running

```bash
docker compose up --build
```

This will:
1. Clone the [patched ONScripter-RU engine](https://github.com/VictoriqueMoe/onscripter-ru)
2. Build SDL2_gpu and FFmpeg 3.3.9 from source with Emscripten
3. Compile the engine to WebAssembly
4. Serve the result with nginx on port 8080

Open `http://localhost:8080` once the container is running.

## Game Assets

The engine expects game files (scripts, images, audio, etc.) to be available at `/usr/share/nginx/html/game/` inside the container. Mount your local game directory as a volume in `docker-compose.yml`:

```yaml
services:
  umineko-web:
    build: .
    ports:
      - "8080:80"
    restart: unless-stopped
    volumes:
      - /path/to/your/umineko/game:/usr/share/nginx/html/game:ro
```

Replace `/path/to/your/umineko/game` with the path to your game directory containing `0.txt`, `nscript.dat`, or whichever script format your version uses, along with the arc/nsa/sar archives.

## Project Structure

```
umineko web/
├── CMakeLists.txt          # Emscripten build configuration
├── Dockerfile              # Multi-stage build (emscripten → nginx)
├── docker-compose.yml
├── src/
│   ├── Resources.cpp       # Embedded GLSL shaders (generated)
│   ├── platform/
│   │   └── web_stubs.cpp   # Stub implementations for libass
│   └── stubs/
│       ├── ass/ass.h       # libass stub header
│       └── smpeg2/smpeg.h  # smpeg2 stub header
└── web/
    └── index.html          # HTML shell with <canvas>
```

The actual engine source (~55 C++ files) comes from the [forked ONScripter-RU repo](https://github.com/VictoriqueMoe/onscripter-ru), which is cloned during the Docker build.

## Current Status

This is an early-stage port. What works:

- Full engine compiles to WebAssembly
- SDL2_gpu GLES2 backend (maps to WebGL)
- FFmpeg 3.3.9 for media decoding
- ASYNCIFY for cooperative multitasking

What doesn't work yet:

- Game asset loading over HTTP (needs lazy-loading implementation)
- Subtitle rendering (libass is stubbed)
- Save file persistence (needs IDBFS integration)
- Video playback (FFmpeg is linked but untested in browser)
