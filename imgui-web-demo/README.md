# ImGui Web Demo

This project demonstrates how to run Dear ImGui in a web browser using WebAssembly (Wasm). It uses Emscripten to compile C++ code to WebAssembly and provides a basic web interface to interact with ImGui's demo window.

## Prerequisites

- Git
- CMake (version 3.10 or later)
- Python 3 (for running the local web server)

## Build Instructions

1. Clone the repository:
```bash
git clone <your-repository-url>
cd imgui-web-demo
```

2. Install Emscripten SDK:
```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ..
```

3. Get ImGui source code:
```bash
mkdir -p src/imgui
git clone https://github.com/ocornut/imgui.git temp_imgui
cp -r temp_imgui/* src/imgui/
rm -rf temp_imgui
```

4. Copy required font:
```bash
mkdir -p fonts
cp src/imgui/misc/fonts/DroidSans.ttf fonts/
```

5. Create build directory and compile:
```bash
mkdir -p build
cd build
emcmake cmake ..
emmake make
cd ..
```

## Running the Demo

1. Start a local web server:
```bash
cd web
python3 -m http.server 8080
```

2. Open a web browser and navigate to:
```
http://localhost:8080
```

You should see the ImGui demo window running in your web browser.

## Project Structure

```
imgui-web-demo/
├── CMakeLists.txt      # CMake build configuration
├── src/
│   ├── main.cpp        # Main application code
│   └── imgui/         # ImGui source files
├── web/
│   ├── index.html     # Web page container
│   ├── imgui_demo.js  # Generated JavaScript (after build)
│   └── imgui_demo.wasm # Generated WebAssembly (after build)
└── fonts/            # Font directory
    └── DroidSans.ttf # Default ImGui font
```

## Technical Details

- The project uses WebGL 2.0 for rendering
- GLFW is used for input handling and window management
- The application is compiled to WebAssembly using Emscripten
- The web page provides a canvas element where ImGui renders its interface

## Troubleshooting

1. If you see "command not found" errors, ensure you've sourced the Emscripten environment:
```bash
source ./emsdk/emsdk_env.sh
```

2. If the webpage shows a black screen, check the browser console for WebGL-related errors.

3. Make sure your browser supports WebGL 2.0. You can check support at:
```
chrome://gpu
```
or
```
about:support
```
in Firefox.
