SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd $SCRIPTPATH/../
GTESTPATH=$SCRIPTPATH/../out/build/lib/$1/
SPDLOGPATH=$SCRIPTPATH/../out/build/_deps/spdlog-build/$1/
SFMLPATH=$SCRIPTPATH/../out/build/_deps/sfml-build/lib/$1/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GTESTPATH:$SPDLOGPATH:$SFMLPATH
xvfb-run ./out/build/bin/Atomina_Test