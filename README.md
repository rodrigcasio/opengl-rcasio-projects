# opengl-rcasio-projects

### Quick workflow

- run within project directory (e.g '01-creating-a-window') to scan systems config and create build tracks.
`cmake -S . -B build`

- The auto-complete bridge, (run once per machine) (LazyVim can provide code completions)
`ln -sf build/compile_commands.json .`

- Run every time code is edited within `src/main.cpp` (compilation loop)
`cmake --build build` preparing changes into a binary executable
`./build/opengl-exe` launching OpenGL application
