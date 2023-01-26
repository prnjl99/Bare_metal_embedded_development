#!/bin/bash
# Compile target application

# Fetch ROOT directory path
ROOT_FOLDER="$(cygpath --mixed "$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)")"

if [[ $1 == build ]];then
    make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER all
elif [[ $1 == clean ]];then
    find . -name '*.o' -exec rm -r {} \;
fi
