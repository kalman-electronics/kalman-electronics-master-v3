import os
import re
from ctypes import c_uint8
import serial
import serial.tools.list_ports

def list_available_ports():
    if os.name == "nt":  # Windows
        pattern = r"COM[0-9]+"
    elif os.name == "posix":  # Linux
        pattern = r"/dev/ttyACM[0-9]+|/dev/ttyUSB[0-9]+"
    else:
        pattern = ""

    return [
        port for port in serial.tools.list_ports.comports() if re.match(pattern, port.device)
    ]

def select_serial_port(ports):
    print("Choose a serial port:")
    for i, port in enumerate(ports):
        print(f"\t{i}: {port.device} - {port.description}")
    while True:
        try:
            port_index = int(input("Index: "))
            if 0 <= port_index < len(ports):
                return ports[port_index]
            else:
                print("Invalid index. Please try again.")
        except ValueError:
            print("Invalid input. Please enter a valid index.")

def calculate_crc_and_urc(cmd, args_uint8):
    crc = c_uint8(cmd.value)
    urc = c_uint8(0)
    for arg in args_uint8:
        crc = c_uint8(crc.value ^ arg.value)
        urc = c_uint8((urc.value + arg.value) * ((arg.value & 0b11) + 1))
    return crc, urc
    
def main():
    ports = list_available_ports()

    if not ports:
        print("No appropriate serial port found.")
        exit(1)

    port = select_serial_port(ports)
    print(f"Chosen port: {port.device}")

    try:
        with serial.Serial(port.device, 115200, timeout=1) as ser:
            while True:
                try:
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
                except ValueError:
                    print("Invalid command or arguments. Please enter integers only.")
                except serial.SerialException as e:
                    print(f"Serial communication error: {e}")
                    break
    except serial.SerialException as e:
        print(f"Failed to open serial port: {e}")

if __name__ == "__main__":
    main()