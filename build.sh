set -eu

sh clean.sh

mkdir -p NeoC
cp -p src/NeoC/*/*.h NeoC
cp -p src/NeoC/*/*.c NeoC

cd NeoC

# 環境
gcc -c Memory.c -o Memory.o -g
gcc -c Exception.c -o Exception.o -g

# ライブラリ用環境
gcc -c Setup.c -o Setup.o -g

# 定義値
gcc -c CC.c -o CC.o -g
gcc -c CSI.c -o CSI.o -g
gcc -c SGR.c -o SGR.o -g

# 部品
gcc -c String.c -o String.o -g
#gcc -c Console.c -o Console.o -g

rm *.c
ar -cq ../NeoC.a *.o
rm *.o
