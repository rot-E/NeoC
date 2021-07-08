set -eu

mkdir -p NeoCEnvLib
cp -p src/NeoCEnvLib/*/*.h NeoCEnvLib
cp -p src/NeoCEnvLib/*/*.c NeoCEnvLib

cd NeoCEnvLib
gcc -c Memory.c -o Memory.o -g
gcc -c Exception.c -o Exception.o -g
gcc -c String.c -o String.o -g
rm *.c
ar -cq ../NeoCEnvLib.a *.o
rm *.o
