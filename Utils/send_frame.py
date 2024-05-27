from ctypes import c_uint8
import serial
from typing import List, Deque
import time
import struct

with serial.Serial('COM9', 115200, timeout=1) as ser:
    while True:
        crc_data = []
        crc = 0

        cmd = c_uint8(int(input("cmd:  ")))
        #cmd = c_uint8(69)
        crc_data.append(cmd)


        args = input("args: ").split(' ')
        #args = [0, 50]
        if args[0] == "":
            args = []

        pos_str = input("pos: ")

        args_num = c_uint8(len(args))
        args_uint8 = []

        for arg in args:
            args_uint8.append(c_uint8(int(arg)))

        if pos_str != "":
            pos = float(pos_str)
            pos_args = bytearray(struct.pack("f", pos))
            args_num = c_uint8(args_num.value + len(pos_args)) \

            for arg in pos_args:
                args_uint8.append(c_uint8(arg))

        crc = c_uint8(cmd.value ^ args_num.value)
        for arg in args_uint8:
            crc = c_uint8(crc.value ^ arg.value)

        urc = c_uint8(0)
        for i, arg in enumerate(args_uint8):
            urc = c_uint8(urc.value + (i + arg.value) * ((i & 0b11) + 1))

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

       # time.sleep(0.25)


