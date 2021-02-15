#!/usr/bin/env python3
import serial
import time
import struct
import math
import matplotlib.pyplot as plt


serialPort = "COM4"
serialBaud = 115200
dataNumBytes = 4
numData = 20
num_points = 100
rawData = bytearray(numData * dataNumBytes)
csvBuffer = []


class Quaternion(object):
    def __init__(self, q0, q1, q2, q3):
        self.q0 = q0
        self.q1 = q1
        self.q2 = q2
        self.q3 = q3

    def __repr__(self):
        return "q0:{}\tq1:{}\tq2:{}\tq3:{}".format(self.q0, self.q1, self.q2, self.q3)

    def __mul__(self, other):
        """[summary]

        :param other: [description]
        :type other: Quaternion
        """
        q0 = (
            self.q0 * other.q0
            - self.q1 * other.q1
            - self.q2 * other.q2
            - self.q3 * other.q3
        )
        q1 = (
            self.q0 * other.q1
            + self.q1 * other.q0
            + self.q2 * other.q3
            - self.q3 * other.q2
        )
        q2 = (
            self.q0 * other.q2
            - self.q1 * other.q3
            - self.q2 * other.q0
            + self.q3 * other.q1
        )
        q3 = (
            self.q0 * other.q3
            + self.q1 * other.q2
            - self.q2 * other.q1
            + self.q3 * other.q0
        )

        return Quaternion(q0, q1, q2, q3)


class EulerAngle(object):
    def __init__(self, pitch, row, yaw):
        self.pitch = pitch
        self.row = row
        self.yaw = yaw

    def __repr__(self):
        scale_val = 180 / 3.14
        return "pitch:{}\troll:{}\tyaw:{}".format(
            self.pitch * scale_val, self.row * scale_val, self.yaw * scale_val
        )


class ADCData(object):
    def __init__(self, x, y, z):

        mag = math.sqrt(x ** 2 + y ** 2 + z ** 2)
        self.x = x / mag
        self.y = y / mag
        self.z = z / mag

    def __repr__(self):
        return "ax:{}\tay:{}\taz:{}".format(self.x, self.y, self.x)

    def quaternion(self):
        """[summary]

        :param adc_data: [description]
        :type adc_data: ADCData
        
        :rtype: Quaternion
        """
        if self.z >= 0:
            denominator = math.sqrt(2 * (self.z + 1))
            q0 = math.sqrt((self.z + 1) / 2)
            q1 = self.y / denominator
            q2 = self.x / denominator
            q3 = 0
        else:
            denominator = math.sqrt(2 * (1 - self.z))
            q0 = -self.y / denominator
            q1 = math.sqrt((1 - self.z) / 2)
            q2 = 0
            q3 = self.x / denominator

        return Quaternion(q0, q1, q2, q3)


class GyroData(object):
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def __repr__(self):
        return "gx:{}\tgy:{}\tgz:{}".format(self.x, self.y, self.x)


class MagData(object):
    def __init__(self, x, y, z):
        mag = math.sqrt(x ** 2 + y ** 2 + z ** 2)
        self.x = x / mag
        self.y = y / mag
        self.z = z / mag

    def __repr__(self):
        return "cx:{}\tcy:{}\tcz:{}".format(self.x, self.y, self.x)

    def quaternion(self):
        """[summary]

        :param adc_data: [description]
        :type adc_data: ADCData
        
        :rtype: Quaternion
        """

        gamma = self.x * self.x + self.y * self.y
        sqt_gamma = math.sqrt(gamma)
        if self.x >= 0:

            q0 = math.sqrt(gamma + self.x * sqt_gamma) / math.sqrt(2 * gamma)
            q1 = 0
            q2 = 0
            q3 = self.y / (math.sqrt(2) * math.sqrt(gamma + self.x * sqt_gamma))
        else:
            q0 = self.y / (math.sqrt(2) * math.sqrt(gamma - self.x * sqt_gamma))
            q1 = 0
            q2 = 0
            q3 = math.sqrt(gamma - self.x * sqt_gamma) / math.sqrt(2 * gamma)

        return Quaternion(q0, q1, q2, q3)


def quaterian_to_euler(q):
    """[summary]

    :param q: [description]
    :type q: Quaternion
    """

    roll = math.atan2(
        2 * (q.q0 * q.q1 + q.q2 * q.q3), q.q0 ** 2 + q.q1 ** 2 - q.q2 ** 2 - q.q3 ** 2
    )
    # roll = math.atan(
    #     2 * (q.q0 * q.q1 + q.q2 * q.q3) / q.q0 ** 2 + q.q1 ** 2 - q.q2 ** 2 - q.q3 ** 2
    # )
    pitch = -math.asin(2 * (q.q1 * q.q3 + q.q0 * q.q2))

    yaw = math.atan2(
        2 * (q.q0 * q.q3 + q.q0 * q.q3), q.q0 ** 2 + q.q1 ** 2 - q.q2 ** 2 - q.q3 ** 2
    )

    return EulerAngle(pitch, roll, yaw)


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
acc_data = []
gyro_data = []
mag_data = []

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
    for ele in data:
        tmp = [i.split(":") for i in ele.split(",")]
        split_data = [int(ele[1]) for ele in tmp]

        ax, ay, az, gx, gy, gz, cx, cy, cz = split_data

        acc_data.append(ADCData(ax, ay, az))
        gyro_data.append(GyroData(gx, gy, gz))
        mag_data.append(MagData(cx, cy, cz))

    acc_data = acc_data[-100:]
    gyro_data = gyro_data[-100:]
    mag_data = mag_data[-100:]

    q_acc = acc_data[-1].quaternion()
    q_mag = mag_data[-1].quaternion()
    q = q_acc * q_mag
    print(q)
    # print(quaterian_to_euler(q))
    # print(acc_data[-1])
    # print(gyro_data[-1])
