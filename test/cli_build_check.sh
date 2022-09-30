
# Script to locally build check examples against supported boards.
# Arduino CLI and the XMC-for-Arduino package must be installed.

EXAMPLES_PATH=../examples

EXAMPLES=$(find "${EXAMPLES_PATH}" -name '*.ino')

BOARDS=(Infineon:arm:XMC1100_Boot_Kit \
        arduino:avr:uno)

for BOARD in ${BOARDS[@]}; do
    for EXAMPLE in ${EXAMPLES[@]}; do \
        echo "Building example ${EXAMPLE} for board ${BOARD}..."
        arduino-cli compile --fqbn $BOARD $EXAMPLE
    done \
done