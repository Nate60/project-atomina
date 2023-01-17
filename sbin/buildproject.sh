SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd $SCRIPTPATH/../
mkdir -p out/build && cd out/build
cmake ../../ -DCMAKE_CXX_FLAGS="-fpic" -DCMAKE_EXPORT_COMPILE_COMMANDS=True -DCMAKE_BUILD_TYPE=$1 -DCMAKE_CONFIGURATION_TYPES=$1 ${@:2} && cmake --build . --config $1
cp $SCRIPTPATH/../out/build/compile_commands.json $SCRIPTPATH/../

