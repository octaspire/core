sudo pacman -S git gcc make
git clone https://github.com/octaspire/core.git
cd core
make submodules-init
make
