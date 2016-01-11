import serial
ser = serial.Serial()
i=0
def serialOpen():
    ser.baudrate = 9600;
    ser.port = "COM3"
    ser.open()
    return ser.is_open

def serialReadLine():
    #ser.open()
    str = ser.readline().rstrip()
    #ser.close()
    #print(str)
    return str

def serialClose():
    if(ser.is_open):
        ser.close()

def testFunc():
    print("python OK")
    return ("python return")
