SCRIPTPATH="$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
cd $SCRIPTPATH/../
cd vendor/spdlog
rm -rf build/*
cd ../../
cd vendor/sfml
rm -rf build/*
cd ../../
cd vendor/googletest
rm -rf build/*
cd ../../
rm -rf ext/*