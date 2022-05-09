SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd $SCRIPTPATH/../
export PATH=$PATH:$SCRIPTPATH/../ext/
mkdir -p target/release && cd target/release
cmake ../../ -DCMAKE_EXPORT_COMPILE_COMMANDS=True $@ && cmake --build .
cp $SCRIPTPATH/../target/release/compile_commands.json $SCRIPTPATH/../

