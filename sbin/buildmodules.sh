SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd $SCRIPTPATH/../
mkdir -p vendor/spdlog/build && mkdir -p vendor/spdlog/install && cd vendor/spdlog/build
cmake ../ -DCMAKE_INSTALL_PREFIX=$SCRIPTPATH/../ext -DCMAKE_CXX_FLAGS="-fpic" && cmake --build . && cmake --install . 
cd ../../../
mkdir -p vendor/sfml/build && mkdir -p vendor/sfml/install && cd vendor/sfml/build
cmake ../ -DCMAKE_INSTALL_PREFIX=$SCRIPTPATH/../ext && cmake --build . && cmake --install . 
cd ../../../
mkdir -p vendor/googletest/build && mkdir -p vendor/googletest/install && cd vendor/googletest/build
cmake ../ -DCMAKE_INSTALL_PREFIX=$SCRIPTPATH/../ext && cmake --build . && cmake --install . 