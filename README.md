# build
cmake -DCMAKE_C_COMPILER=clang -DPLATFORM=linux -DCMAKE_BUILD_TYPE=debug -DARCH=x32 -B build && cmake --build build

# build and run
cmake -DCMAKE_C_COMPILER=clang -DPLATFORM=linux -DCMAKE_BUILD_TYPE=debug -DARCH=x32 -DARGS="" -B build && cmake --build build && cmake --build build --target run

# misc
cmake --build build
cmake --build build --target run
cmake --build build --target clean
cmake -DARGS="" -B build && cmake --build build --target run

