# !/bin/sh
PRJ_NAME="OpenGL"
parent_path=$( cd -P -- "$(dirname -- "$(command -v -- "$0")")" && pwd -P )
cd $parent_path
cd ".."

BuildProject () {
    vendor/premake/premake5 gmake
    cd "$PRJ_NAME/" && make
    echo "---------------"
}


RunProject () {
    exedir=$(find -name "$PRJ_NAME.out")
    if [ -z "$exedir" ]
    then
        echo "$PRJ_NAME.out not found"
        echo "Project Not Compiled"
        echo "---------------"
    else
        clear -x
        echo "Running $exedir"
        $exedir
    fi
}


CleanProject () {
    vendor/premake/premake5 clean
    echo "---------------"
}


if [ $# = 0 ]
then
    echo "Building clean project..."
    CleanProject
    BuildProject
    RunProject
    exit
elif [ "$1" = "run" ]
then
    cd "$PRJ_NAME/"
    RunProject
    exit
elif [ "$1" = "build" ]
then
    echo "Compiling and running $PRJ_NAME"
    BuildProject
    RunProject
    exit
elif [ "$1" = "clean" ]
then
    CleanProject
    exit
else "Bad args"
fi