import serial
ser = serial.Serial()
i=0
def serialOpen():
    ser.baudrate = 9600;
    ser.port = "COM3"
    #ser.timeout = 0.020
    ser.open()
    return ser.is_open

def serialReadLine():
    #ser.open()
    ser.flush()
    str = ser.readline().rstrip()
    if(str=="") :
        print ("null")
        return ("error")
    else :
        print(str)
        return str
    

def serialClose():
    if(ser.is_open):
        ser.close()

def serialIsOpen() :
    print ser.is_open
    if(ser.is_open) :
        print "1"
        return 1
    else :
        print "2"
        return 2

def testFunc():
    print("python OK")
    return ("python return")

#serialOpen()
#while(1) :
    #serialReadLine()
