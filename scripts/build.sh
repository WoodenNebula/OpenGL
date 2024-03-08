# !/bin/sh
PRJ_NAME="OpenGL"

BuildProject () {
    vendor/premake/premake5 gmake
    make
    echo "---------------"
}


RunProject () {
    if [ -d "$PRJ_NAME/build/" ]
    then
        $PRJ_NAME/build/**/$PRJ_NAME/$PRJ_NAME
    else
        echo "Project Not Compiled"
        echo "---------------"
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
    if [ -f "Makefile" ]
    then
        echo "Running project $PRJ_NAME"
        RunProject
    else
        echo "PROJECT NOT BUILT YET"
    fi
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
fi
# echo "Usage are run, buildrun, clean, rebuild"