import serial

with serial.Serial('COM18', 115200, timeout=1) as ser:
    while True:
        crc_data = []
        crc = 0
        str_args = ""

        cmd = int(input("cmd:  "))
        crc_data.append(cmd)

        args = input("args: ").split(' ')
        if args[0] == "":
            args = []
        args_num = len(args)

        crc_data.append(len(args))
        for arg in args:
            str_args = str_args + (chr(int(arg)))
            crc_data.append(int(arg))

        crc = 0
        for c in crc_data:
            crc ^= c

        print("crc:  " + str(crc))

        frame = '<' + chr(cmd) + chr(args_num) + str_args + chr(crc)
        print(frame)
        ser.write(frame.encode('utf-8'))