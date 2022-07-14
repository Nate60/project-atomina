SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd $SCRIPTPATH/atomina-test
mkdir -p cmake
rm -r cmake/**
cd cmake
cmake ../
cmake --build .
./Atomina_Test
