#!/bin/bash
arm-none-eabi-gdb --early-init-command="set auto-load safe-path /" -x ./script2.gdb ./build/prom_emulation.elf
