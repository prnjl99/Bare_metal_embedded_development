#!/bin/bash
# Compile target application

# Fetch ROOT directory path
ROOT_FOLDER="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

if [[ ! -v stm_build ]];then
    make_file="$ROOT_FOLDER/build_scripts/scratch.mk"
else
    make_file="$ROOT_FOLDER/build_scripts/stm_driver.mk"
fi

case `uname` in
    *CYGWIN*|*MINGW*|*MSYS*) ROOT_FOLDER=`cygpath -m "$ROOT_FOLDER"`;;
    *CYGWIN*|*MINGW*|*MSYS*) make_file=`cygpath -m "$make_file"`;;
esac

if [[ ! -v CI ]];then
    export CI=false
fi

if [[ $1 == build ]];then
    make -f $make_file --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI all
elif [[ $1 == erase ]];then
    make -f $make_file --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI erase
elif [[ $1 == flash ]];then
    make -f $make_file --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI flash
elif [[ $1 == debug ]];then
	if [[ ! -f $ROOT_FOLDER/test_applications/build/$2/$2.elf ]]; then
		make -f $make_file --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI all
	fi
    openocd -s scripts -f $ROOT_FOLDER/build_scripts/stm.cfg -c "init; reset init" &
    sleep 1
    arm-none-eabi-gdb -ex "target remote :3333" \
    -ex "monitor reset init" \
    -ex "set confirm off" \
    -ex "file $ROOT_FOLDER/test_applications/build/$2/$2.elf" \
    -ex "load"
#    -ex "source -v $ROOT_FOLDER/build_scripts/gdb_cmd"
elif [[ $1 == disass ]];then
    make -f $make_file --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI FUNC=$3 disass
elif [[ $1 == clean ]];then
    find . -name '*.o' -exec rm -r {} \;
    find . -name '*.d' -exec rm -r {} \;
    rm -rf "$ROOT_FOLDER/test_applications/build"
fi
