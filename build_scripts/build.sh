#!/bin/bash
# Compile target application

# Fetch ROOT directory path
ROOT_FOLDER="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

if [[ -v stm_build ]];then
    stm_build=1
else
    stm_build=0
fi

case `uname` in
    *CYGWIN*|*MINGW*|*MSYS*) ROOT_FOLDER=`cygpath -m "$ROOT_FOLDER"`;;
esac

if [[ ! -v CI ]];then
    export CI=false
fi

# Use this to zip directories
#zip -r $ROOT_FOLDER/stm_files.zip $ROOT_FOLDER/stm_files/
#exit 1;

get_dep()
{
	if [[ ! -d $ROOT_FOLDER/stm_files ]]; then
		unzip $ROOT_FOLDER/stm_files.zip
		rm -rf $ROOT_FOLDER/C:
	fi
}

if [[ $1 == build ]];then
	get_dep
    make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI stm_build=$stm_build all
elif [[ $1 == erase ]];then
    make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI stm_build=$stm_build erase
elif [[ $1 == flash ]];then
	get_dep
    make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI stm_build=$stm_build flash
elif [[ $1 == debug ]];then
	get_dep
	if [[ ! -f $ROOT_FOLDER/test_applications/build/$2/$2.elf ]]; then
		make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI stm_build=$stm_build all
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
	get_dep
    make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI FUNC=$3 stm_build=$stm_build disass
elif [[ $1 == clean ]];then
    find . -name '*.o' -exec rm -r {} \;
    find . -name '*.d' -exec rm -r {} \;
    rm -rf "$ROOT_FOLDER/test_applications/build"
fi
