#!/usr/bin/env python
import serial
import time
import struct
import matplotlib.pyplot as plt


serialPort = "COM4"
serialBaud = 115200
dataNumBytes = 4
numData = 20
num_points = 100
rawData = bytearray(numData * dataNumBytes)
csvBuffer = []

# Connect to serial port
print("Trying to connect to " + str(serialPort) + " at " + str(serialBaud) + " BAUD.")
try:
    s = serial.Serial(serialPort, serialBaud, timeout=4,)
    print("Connected!")
except:
    print(
        "Failed to connect with "
        + str(serialPort)
        + " at "
        + str(serialBaud)
        + " BAUD."
    )

s.reset_input_buffer()  # flush input buffer
pre_data = ""
row_data = []
pitch_data = []

plt.show(block=False)
plt.ion()
while True:
    # time.sleep(0.2)
    # read n bytes into array
    s.readinto(rawData)
    temp = pre_data + "".join(map(chr, rawData[:]))
    data = temp.split("\r\n")
    if temp[-1] != "\n":
        pre_data = data[-1]
    else:
        pre_data = ""

    data = data[:-1]
    # temp = temp.replace("\t", "")
    for ele in data:
        split_data = [i.split(":") for i in ele.split("\t")]
        # pitch = int(split_data[0][1])
        # row = int(split_data[1][1])
        # yaw = int(split_data[2][1])
        pitch_data.append(int(split_data[0][1]))
        row_data.append(int(split_data[1][1]))

    pitch_data = pitch_data[-num_points:]
    plt.clf()
    plt.plot(pitch_data, label="Pitch")
    # plt.plot(row_data, label="Row")
    plt.legend()
    plt.pause(0.001)
    plt.show(block=False)

    # for i in range(numData):
    #     bytedata = rawData[(i * dataNumBytes) : (dataNumBytes + i * dataNumBytes)]
    #     (value,) = struct.unpack("f", bytedata)
    #     data[i] = value
    # print(data)
    # csvBuffer.append([data[0], data[1], data[2]])

# record "csvBuffer" into HDF5 file.
