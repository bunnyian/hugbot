# use pyserial to send data to arduino
# '''
import serial
import time


#basic test program
# ser = serial.Serial('/dev/tty.usbmodem2101', 9600) #the team arduino 
ser = serial.Serial('/dev/cu.usbmodem1101', 9600) #anoop's arduino (just for testing)
def send_data(state_index, horizontal_position):
    # Ensure the values are within the correct range
    if 0 <= state_index <= 2 and 0 <= horizontal_position <= 6:
        # Encoding: assuming value1 uses the upper 3 bits and value2 uses the lower 5 bits
        encoded_byte = (state_index << 5) | horizontal_position
        ser.write(bytes([encoded_byte]))
    else:
        print("Values out of range")

while True:
    # ser.write(b'0') # user is sad/disgusted/angry
    # time.sleep(1)
    # ser.write(b'1') # user is neutral or not found in the frame
    # time.sleep(1)
    # ser.write(b'2') # user is happy/surprised
    # time.sleep(1) 
    # print('sent')
    send_data(0, 5)
    print('sent 0,5')
    time.sleep(1)
    send_data(1, 5)
    print('sent 1,5')
    time.sleep(1)
    send_data(2, 5)
    print('sent 2,5')
    time.sleep(1) 

    



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



