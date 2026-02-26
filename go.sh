#!/bin/bash
arm-none-eabi-objdump -h ./build/prom_emulation.elf
arm-none-eabi-objdump -D ./build/prom_emulation.elf
arm-none-eabi-objdump -d ./build/prom_emulation.elf

vim ./build/prom_emulation.map