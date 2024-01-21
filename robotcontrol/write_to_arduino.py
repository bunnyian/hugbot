# use pyserial to send data to arduino
# '''
import serial
import time


#basic test program
# ser = serial.Serial('/dev/tty.usbmodem2101', 9600) #team arduino
ser = serial.Serial('/dev/cu.usbmodem1101', 9600) #anoop's arduino (just for testing)

while True:
    # ser.write(b'0')
    # time.sleep(1)
    # ser.write(b'1')
    # time.sleep(1)
    ser.write(b'2')
    time.sleep(1) 
    print('sent')

    
    # yabal yabal yabal yabal 
    #yabal in korean means "i'm tired"
    #yabal in spanish means "i'm tired"
    #yabal in english means "i'm tired"
    #yabal in french means "i'm tired"
    #yabal in german means "i'm tired"
    #yabal in italian means "i'm tired"
    #yabal in russian means "i'm tired"
    #yabal in chinese means "i'm tired"
    #yabal in japanese means "i'm tired"
    #yabal in arabic means "i'm tired"
    #yabal in hindi means "i'm tired"
    #yabal in turkish means "i'm tired"
    #yabal in vietnamese means "i'm tired"
    #yabal in thai means "i'm tired"
    #yabal in dutch means "i'm tired"
    #yabal in swedish means "i'm tired"