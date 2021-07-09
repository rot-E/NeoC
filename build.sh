set -eu

sh clean.sh

mkdir -p NeoC
cp -p src/NeoC/*/*.h NeoC
cp -p src/NeoC/*/*.c NeoC

cd NeoC

gcc -c Startup.c -o Startup.o -g

gcc -c Memory.c -o Memory.o -g
gcc -c Exception.c -o Exception.o -g
gcc -c String.c -o String.o -g

rm *.c
ar -cq ../NeoC.a *.o
rm *.o
