set -eu

sh examples/clean.sh

cd examples

cp -pr ../NeoC* .

gcc Exception.c NeoC.a -o Exception -g
gcc ExceptionNested.c NeoC.a -o ExceptionNested -g
gcc String.c NeoC.a -o String -g
gcc Theme.c NeoC.a -o Theme -g
gcc SampleCode.c NeoC.a -o SampleCode -g

cd ../
