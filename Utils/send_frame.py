from pickletools import uint8
import serial
from typing import List, Deque

def _calc_urc(data: List[uint8]) -> uint8:
    crc = 0x00
    for i, arg in enumerate(data[2:]):
        crc += (((arg + i) * ((i % 4) + 1)))
        crc %= 256
        # rospy.logerr("> i " + str(i))
        # rospy.logerr("crc " + str(crc))
        # rospy.logerr("val " + str((((arg + i) * ((i % 4) + 1)))))
    return crc % 256

with serial.Serial('COM8', 115200, timeout=1) as ser:
    while True:
        crc_data = []
        crc = 0

        cmd = int(input("cmd:  "))
        crc_data.append(cmd)

        args = input("args: ").split(' ')
        if args[0] == "":
            args = []
        args_num = len(args)

        crc = cmd ^ args_num
        for arg in args:
            crc ^= bytes(arg, "utf-8")[0]

        urc = 0
        for i in range(0, args_num):
            urc += (bytes(args[i], "utf-8")[0] + i.to_bytes()[0]) * ((i.to_bytes()[0] & 0b11) + 1)

        print("crc:  " + str(crc))

        frame = bytearray([ord('<'),
                           cmd,
                           int(args_num),
                           int(args_num) + cmd])

        for arg in args:
            frame.append(int(arg))

        frame.append(crc)
        frame.append(urc)

        print(frame)
        ser.write(frame)