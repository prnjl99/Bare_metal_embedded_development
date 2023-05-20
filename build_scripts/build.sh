#!/bin/bash
# Compile target application

# Fetch ROOT directory path
ROOT_FOLDER="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

case `uname` in
    *CYGWIN*|*MINGW*|*MSYS*) ROOT_FOLDER=`cygpath -m "$ROOT_FOLDER"`;;
esac

if [[ $1 == clean ]];then
    find . -name '*.o' -exec rm -r {} \;
    find . -name '*.d' -exec rm -r {} \;
    rm -rf "$ROOT_FOLDER/test_applications/build"
    echo "Cleaned"
    exit 0;
fi

if [[ -v tiva ]];then
    tiva_build=1
    build_dir="tiva"
	if [[ -v scratch ]];then
		scratch=1
	else
		echo "ERROR: Only scratch driver implementation is supported for TIVA. No library. Add scratch=1 in argument"
		exit 1;
	fi
elif [[ -v stm ]];then
	tiva_build=0
	build_dir="stm"
	if [[ -v scratch ]];then
		echo "Building using scratch driver implementation"
		scratch=1
	else
		echo "Building using STM library"
		scratch=0
	fi
else
	echo "ERROR: Provide target: tiva=1 or stm=1 in argument"
	exit 1;
fi

if [[ ! -v CI ]];then
    export CI=false
fi

# Use this to zip directories
#zip -r $ROOT_FOLDER/stm_files.zip $ROOT_FOLDER/stm_files/
#exit 1;

get_dep()
{
	if [[ ! -d $ROOT_FOLDER/stm_files ]]; then
		unzip $ROOT_FOLDER/stm_files.zip -d $ROOT_FOLDER/stm_files
		if [[ -d $ROOT_FOLDER/stm_files/C: ]]; then
			mv $ROOT_FOLDER/stm_files/"$(dirname $ROOT_FOLDER)"/STM32-Bare-metal-embedded-development/stm_files/* $ROOT_FOLDER/stm_files/
			rm -rf $ROOT_FOLDER/stm_files/C:
		fi
		rm -rf $ROOT_FOLDER/C:
	fi
}

if [[ $1 == build ]];then
	get_dep
    make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI build_dir=$build_dir tiva_build=$tiva_build scratch=$scratch all
elif [[ $1 == erase ]];then
    make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI build_dir=$build_dir tiva_build=$tiva_build scratch=$scratch erase
elif [[ $1 == flash ]];then
	get_dep
    make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI build_dir=$build_dir tiva_build=$tiva_build scratch=$scratch flash
elif [[ $1 == debug ]];then
	get_dep
	if [[ ! -f $ROOT_FOLDER/test_applications/build/$build_dir/$2/$2.elf ]]; then
		make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI build_dir=$build_dir tiva_build=$tiva_build scratch=$scratch all
	fi
	if [[ $tiva_build == 1 ]]; then
		openocd -s scripts -f $ROOT_FOLDER/build_scripts/tiva_programming_support/board/ti_ek-tm4c123gxl.cfg -c "init; reset init" &
	else
		openocd -s scripts -f $ROOT_FOLDER/build_scripts/stm_programming_support/stm.cfg -c "init; reset init" &
	fi
    sleep 1
    arm-none-eabi-gdb -ex "target extended-remote :3333" \
    -ex "monitor reset init" \
    -ex "set confirm off" \
    -ex "file $ROOT_FOLDER/test_applications/build/$build_dir/$2/$2.elf" \
    -ex "load"
#    -ex "source -v $ROOT_FOLDER/build_scripts/gdb_cmd"
elif [[ $1 == disass ]];then
	get_dep
    make --no-print-directory -C $ROOT_FOLDER/build_scripts APP=$2 ROOT_FOLDER=$ROOT_FOLDER CI=$CI FUNC=$3 build_dir=$build_dir tiva_build=$tiva_build scratch=$scratch disass
fi
