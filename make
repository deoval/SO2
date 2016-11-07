gcc -Wall -Werror -o ./build/$1 $1.c
if [ $? -ne 0 ]
then
    echo "Compile succeeded, but with warnings"
    exit 2
else
    exec=$1
    shift
    ./build/$exec $*
fi