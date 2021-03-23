#!/bin/sh -x

arm-none-eabi-objcopy -O binary build/base/bin/embox build/base/bin/cv.bin --only-section=.text --only-section=.rodata --only-section='.ARM.ex*' --only-section='.data'
