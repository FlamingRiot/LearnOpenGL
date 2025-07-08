if [ ! -d "build" ]; then
  mkdir build
fi

cd build

# Compile makefile
cmake -S ../ -B .

# Build from makefile
make