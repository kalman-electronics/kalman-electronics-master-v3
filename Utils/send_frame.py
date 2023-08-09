from ctypes import c_uint8
import serial
from typing import List, Deque

with serial.Serial('COM8', 115200, timeout=1) as ser:
    while True:
        crc_data = []
        crc = 0

        cmd = c_uint8(int(input("cmd:  ")))
        crc_data.append(cmd)

        args = input("args: ").split(' ')
        if args[0] == "":
            args = []

        args_num = c_uint8(len(args))
        args_uint8 = []

        for arg in args:
            args_uint8.append(c_uint8(int(arg)))

        crc = c_uint8(cmd.value ^ args_num.value)
        for arg in args_uint8:
            crc = c_uint8(crc.value ^ arg.value)

        urc = c_uint8(0)
        for arg in args_uint8:
            urc = c_uint8((urc.value + arg.value) * ((arg.value & 0b11) + 1))

        frame = [
            ord('<'),
            cmd.value,
            args_num.value,
            c_uint8(cmd.value + args_num.value).value
        ]

        for arg in args_uint8:
            frame.append(arg.value)

        frame.append(crc.value)
        frame.append(urc.value)

        print(frame)
        ser.write(frame)


