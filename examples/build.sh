set -eu

cd examples

cp -pr ../NeoCEnvLib* .
gcc Exception.c NeoCEnvLib.a -o Exception -g
gcc String.c NeoCEnvLib.a -o String -g

cd ../
