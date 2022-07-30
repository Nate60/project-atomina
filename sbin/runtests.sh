SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd $SCRIPTPATH/../
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$SCRIPTPATH/../ext/lib
xvfb-run ./target/release/atomina-test/Atomina_Test