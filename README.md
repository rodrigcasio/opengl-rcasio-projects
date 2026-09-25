# opengl-rcasio-projects

### Quick workflow

- run within project directory (e.g '01-creating-a-window') to scan systems config and create build tracks.
`cmake -S . -G Ninja -B build`

- The auto-complete bridge, (run once per machine) (LazyVim can provide code completions)
`ln -sf build/compile_commands.json .`

- Run every time code is edited within `src/main.cpp` (compilation loop)
`cmake --build build` preparing changes into a binary executable
`./build/opengl-exe` launching OpenGL application


#### Directory Structure
```
Directory structure:
└── rodrigcasio-opengl-rcasio-projects/
    ├── README.md
    ├── 01-creating-a-window/
    │   ├── CMakeLists.txt
    │   └── src/
    │       └── main.cpp
    ├── 02-ex1/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   └── src/
    │       ├── fragment-shader.glsl
    │       ├── main.cpp
    │       └── vertex-shader.glsl
    ├── 02-ex2/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   └── src/
    │       ├── fragment-shader.glsl
    │       ├── main.cpp
    │       └── vertex-shader.glsl
    ├── 02-ex3/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   └── src/
    │       ├── fragm-s-01.glsl
    │       ├── fragm-s-02.glsl
    │       ├── main.cpp
    │       └── vertex-shader.glsl
    ├── 02-hello-triangle/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   └── src/
    │       ├── fragment-shader.glsl
    │       ├── main.cpp
    │       └── vertex-shader.glsl
    ├── 03-ex1/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   └── shader.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    ├── 03-ex2/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   └── shader.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    ├── 03-ex3/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   └── shader.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    ├── 03-shaders/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   └── shader.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    ├── 04-ex1/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   ├── shader.h
    │   │   └── KHR/
    │   │       └── khrplatform.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       ├── stb_image.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    ├── 04-ex2/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   ├── shader.h
    │   │   └── KHR/
    │   │       └── khrplatform.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       ├── stb_image.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    ├── 04-ex3/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   ├── shader.h
    │   │   └── KHR/
    │   │       └── khrplatform.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       ├── stb_image.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    ├── 04-ex4/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   ├── shader.h
    │   │   └── KHR/
    │   │       └── khrplatform.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       ├── stb_image.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    ├── 04-textures/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   ├── shader.h
    │   │   └── KHR/
    │   │       └── khrplatform.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       ├── stb_image.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    ├── 05-ex1/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   ├── shader.h
    │   │   └── KHR/
    │   │       └── khrplatform.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       ├── stb_image.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    ├── 05-ex2/
    │   ├── README.md
    │   ├── CMakeLists.txt
    │   ├── include/
    │   │   ├── shader.h
    │   │   └── KHR/
    │   │       └── khrplatform.h
    │   └── src/
    │       ├── main.cpp
    │       ├── shader.cpp
    │       ├── stb_image.cpp
    │       └── shaders/
    │           ├── frag-shader.glsl
    │           └── vertex-shader.glsl
    └── 05-transformations/
        ├── README.md
        ├── CMakeLists.txt
        ├── include/
        │   ├── shader.h
        │   └── KHR/
        │       └── khrplatform.h
        └── src/
            ├── main.cpp
            ├── shader.cpp
            ├── stb_image.cpp
            └── shaders/
                ├── frag-shader.glsl
                └── vertex-shader.glsl
```
