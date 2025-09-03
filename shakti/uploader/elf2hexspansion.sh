#!/bin/bash
echo "Converting elf to hex "
mkdir -p $3/output
mkdir -p $3/output/genlib

sysc="$4/../cores/arduino/shakti-sdk/bsp/include"
syscc="$4/utils/syscalls.c"
BSP="$5/cores/arduino/shakti-sdk/bsp"
bspboard="$5/cores/arduino/shakti-sdk/bsp/third_party/$6"
bspdri="$5/cores/arduino/shakti-sdk/bsp/drivers"
bspinc="$BSP/include"
bsplib="$BSP/libs"
bspcore="$BSP/core"
GENLIB="$3/output/genlib"
#Compiling .c files 
$1/riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -D__ASSEMBLY__=1 -c "$bspcore"/start.S -o "$GENLIB"/start.o -I"$bspinc" -I"$bspboard"
$1/riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf -D__ASSEMBLY__=1 -c "$bspcore"/trap.S -o "$GENLIB"/trap.o -I"$bspinc" -I"$bspboard"
$1/riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bspcore"/traps.c -o "$GENLIB"/traps.o -I"$bspinc" -I"$bspboard"
$1/riscv32-unknown-elf-gcc -w -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bspcore"/init.c -o "$GENLIB"/init.o -I"$bspinc" -I"$bspboard" -I"$bspdri"/plic
$1/riscv32-unknown-elf-gcc -w -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bsplib"/printf.c -o "$GENLIB"/printf.shakti -I"$bspinc" -I"$bspboard" -lm -lgcc
$1/riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bsplib"/log.c -o "$GENLIB"/log.o -I"$bspinc" -I"$bspboard"
$1/riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bsplib"/util.c -o "$GENLIB"/util.o -I"$bspinc" -I"$bspboard"
$1/riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bspdri"/uart/uart.c -o "$GENLIB"/uart.o -I"$bspinc" -I"$bspboard"
$1/riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bspdri"/i2c/i2c_driver.c -o "$GENLIB"/i2c_driver.o -I"$bspinc" -I"$bspboard"
$1/riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bspdri"/plic/plic_driver.c -o "$GENLIB"/plic_driver.o -I"$bspinc" -I"$bspboard" -I"$bspdri"/plic
$1/riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bspdri"/spi/spi_spansion.c -o "$GENLIB"/spi_spansion.o -I"$bspinc" -I"$bspboard"
$1/riscv32-unknown-elf-gcc -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bspdri"/clint/clint_driver.c -o "$GENLIB"/clint_driver.o -I"$bspinc" -I"$bspboard"
$1/riscv32-unknown-elf-gcc -w -march=rv32imac -mabi=ilp32  -mcmodel=medany -static -std=gnu99 -fno-common -fno-builtin-printf  -c "$bspdri"/pwm/pwm_driver.c -o "$GENLIB"/pwm_driver.o -I"$bspinc" -I"$bspboard"
#Linking the .o files
$1/riscv32-unknown-elf-ar rcs "$GENLIB"/libshakti32.a "$GENLIB"/start.o "$GENLIB"/trap.o "$GENLIB"/util.o "$GENLIB"/traps.o "$GENLIB"/log.o "$GENLIB"/printf.shakti "$GENLIB"/spi_spansion.o "$GENLIB"/uart.o "$GENLIB"/i2c_driver.o "$GENLIB"/clint_driver.o "$GENLIB"/plic_driver.o "$GENLIB"/init.o  "$GENLIB"/pwm_driver.o 

filesize=$(stat -c%s "$2")
maxsize=191140   #This value is set based on manual testing, exact value to be calculated.

# Converting from elf to hex 
if (( filesize > maxsize )); then
    $1/elf2hex  4 16384 $2 2147483648 > $3/output/code.mem
    echo "Note:Upload to Flash would take little longer since size of $2 is $filesize exceeds 132680 bytes"
else
    $1/elf2hex  4 8192 $2 2147483648 > $3/output/code.mem
    echo "File size of file $filesize"
fi
#$1/elf2hex  4 8192 $2 2147483648 > $3/output/code.mem

echo "Converting mem to C "
gcc -g -w -DFILEPATH=\"$3\" $4/utils/uploader/elf_to_header.c -o $3/elf_to_header 

$3/elf_to_header

##Generating final elf using shakti-sdk
$1/riscv32-unknown-elf-gcc -w  -mcmodel=medany -static -std=gnu99 -nostartfiles -fno-builtin-printf  -I"$bspinc"  -I"$GENLIB" -I"$bspboard" -I$3/output/ -c $4/utils/uploader/spansion/deploy.c  -o $3/output/deploy.o -march=rv32imac -mabi=ilp32 -lm -lgcc 
$1/riscv32-unknown-elf-gcc -T "$bspboard"/link.ld  $3/output/deploy.o  "$GENLIB"/libshakti32.a   -o "$GENLIB"/deploy.shakti  -static -nostartfiles -lm -lgcc

echo "Generated the final .elf file for upload" 