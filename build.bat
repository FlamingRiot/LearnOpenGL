
if not exist "build" (
    mkdir build
)

cd build

:: Compile project files
cmake -S ../ -B . -G Ninja

:: Build from makeFile
cmake --build . 