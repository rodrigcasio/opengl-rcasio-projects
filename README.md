# opengl-rcasio-projects

### Quick workflow

- run within project directory (e.g '01-creating-a-window') to scan systems config and create build tracks.
`cmake -S . -G Ninja -B build`

- The auto-complete bridge, (run once per machine) (LazyVim can provide code completions)
`ln -sf build/compile_commands.json .`

- Run every time code is edited within `src/main.cpp` (compilation loop)
`cmake --build build` preparing changes into a binary executable
`./build/opengl-exe` launching OpenGL application


### Directory Structure


Directory structure:
└── rodrigcasio-nvchad-rodrig-config/
    ├── README.md
    ├── arch-checkups-cmds.md
    ├── init.lua
    ├── lazy-lock.json
    ├── LICENSE
    ├── .stylua.toml
    ├── archWSL-tmux-alacritty-settings/
    │   ├── alacritty.toml
    │   ├── aur_packages.txt
    │   ├── installed-packages.txt
    │   ├── pacman_packages.txt
    │   ├── .tmux.conf
    │   └── .vimrc
    ├── bashrc-file-arch/
    │   └── .bashrc
    ├── kali-linux-alacritty-zshrc-config/
    │   └── .zshrc
    ├── linux-tmux-alacritty-vim-conf/
    │   ├── alacritty.toml
    │   ├── .tmux.conf
    │   ├── .vimrc
    │   └── minimal-tmux-config/
    │       ├── README.md
    │       └── .tmux.conf
    ├── lua/
    │   ├── autocmds.lua
    │   ├── chadrc.lua
    │   ├── mappings.lua
    │   ├── options.lua
    │   ├── configs/
    │   │   ├── conform.lua
    │   │   ├── lazy.lua
    │   │   └── lspconfig.lua
    │   └── plugins/
    │       └── init.lua
    ├── macOS-tmux-vim-conf/
    │   ├── .tmux.conf
    │   ├── .vimrc
    │   └── minimal-tmux-config/
    │       └── .tmux.conf
    ├── packages_installed_arch/
    │   ├── full_system_snapshot_april-2026.txt
    │   ├── how-to-install-everything.txt
    │   ├── pacman_packages_2026.txt
    │   └── yay_packages_2026.txt
    ├── packgs-installed-Arch/
    │   ├── aur-list.txt
    │   ├── master-backup.txt
    │   └── pacman-list.txt
    └── zshrc-file-mac/
        └── .zshrc
