#!/usr/bin/env bash

EXECPATH=$(pwd)
SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

while :; do
    case $1 in
        -a) #app-type [Server|OpenGL]
            if [ -n "$2" ]; then
                case $2 in
                    Server)
                        ;;
                    OpenGL)
                        ;;
                    *)
                        printf "$2 is not a valid app type\n"
                        exit 1
                esac
                apptype=$2
                shift
            else
                printf "app type parameter must have app type argument [Server|OpenGL]\n"
                exit 1
            fi
            ;;
        -b) #build-type [Release|Debug]
            if [ -n "$2" ]; then
                case $2 in
                    Debug)
                        ;;
                    Release)
                        ;;
                    *)
                        printf "$2 is not a valid build type\n"
                        exit 1
                esac
                buildtype=$2
                shift
            else
                printf "build type parameter must have build type argument [Release|Debug]\n"
                exit 1
            fi
            ;;
        -?) #unknown arg
            printf "unknown argument $1\n"
            ;;
        *)
            break
    esac
    shift
done

cd $DIR/../
mkdir -p out/build/$buildtype/$apptype
cd out/build/$buildtype/$apptype
cmake $DIR/../ -DCMAKE_CONFIGURATION_TYPES=$buildtype -DATMA_APP_TYPE:STRING=$apptype -DCMAKE_CXX_FLAGS="-fpic" -DCMAKE_BUILD_TYPE=$buildtype -DCMAKE_TOOLCHAIN_FILE="$DIR/../deps/vcpkg/scripts/buildsystems/vcpkg.cmake" -G "Ninja"
cd $EXECPATH
