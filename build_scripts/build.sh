#!/bin/bash
# Compile target application

# Fetch ROOT directory path
ROOT_FOLDER="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

case `uname` in
    *CYGWIN*|*MINGW*|*MSYS*) ROOT_FOLDER=`cygpath -w "$ROOT_FOLDER"`;;
esac

if [[ ! -v CI ]];then
    export CI=false
fi

if [[ $1 == build ]];then
    make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI all
elif [[ $1 == clean ]];then
    find . -name '*.o' -exec rm -r {} \;
    rm -rf "$ROOT_FOLDER/test_applications/build"
fi
