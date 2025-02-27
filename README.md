# Requirements

We support linux (ubuntu) and MacOS. Windows users should use WSL2 or the Department lab machines.

We assume you're using llvm-19. Mainly we assume that your LLVM uses the new pass manager. If that means nothing to you then ignore it.

LLVM-19 binaries are avalible here: https://github.com/llvm/llvm-project/releases/tag/llvmorg-19.1.7 as well as on your favorite package manager `brew install llvm@19` or `apt install llvm-19` (after adding llvm to apt sources list: `/etc/apt/sources.list`)

If you encounter build errors on a clean pull its very likely that the include/lib folders are wrong so open an issue with your env, or make a piazza post with you env. 

# Building

This should be familiar for anyone who has used CMake before. if not then follow the instructions below.

- Clone the repo.
- CMake build files into `./build` using `cmake -S . -B ./build`
- Run make on the newly built files. `make -C ./build`

