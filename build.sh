mkdir build
cmake -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++ -S . -B build
cd build
make
cd ..
./Game.exe