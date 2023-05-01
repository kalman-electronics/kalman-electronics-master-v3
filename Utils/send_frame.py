import serial

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

        crc_data.append(len(args))
        for arg in args:
            crc_data.append(int(arg))

        crc = 0
        for c in crc_data:
            crc ^= c

        print("crc:  " + str(crc))

        frame = bytearray([ord('<'), cmd, int(args_num)])

        for arg in args:
            frame.append(int(arg))

        frame.append(crc)

        print(frame)
        ser.write(frame)