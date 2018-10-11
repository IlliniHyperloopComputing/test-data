import serial 
import time
import signal

# Based on : https://petrimaki.com/2013/04/28/reading-arduino-serial-ports-in-windows-7/

ctrl_c = 0
def signal_handler(signal, frame):
   global ctrl_c
   ctrl_c = 1
   print("CTRL C\n")
signal.signal(signal.SIGINT, signal_handler)

try:
    arduino1 = serial.Serial('COM3', 115200, timeout=0)
except:
    print("Failed to access Arduino1")
    exit()

try:
    arduino2 = serial.Serial('COM4', 115200, timeout=0)
except:
    print("Failed to access Arduino2")
    exit()

output_txt_prefix = "SWOD_test_"
output_file_name = output_txt_prefix + datetime.datetime.now().isoformat('T')[:-7] #remove the last 7 characters, which are the fractions of a second
output_file = open(output_file_name, "w+")

print("Writing to file: %s" % output_file_name)
print("Begin reading (there is a slight delay)")
print("time, [RPM1], [RPM2], amps ")

writing_delay = 5.0 #when initially reading serial ports in, there are transient errors
rpm_line    = ""
amp_line    = ""

new_data = False
start = time.time()
while (ctrl_c == 0):
    sl = select.select([arduino1, arduino2], [], [], 0.0)[0]

    #read from arduino RPM
    if (arduino1 in sl): 
        rpm_line = arduino1.readline()
        rpm_line = rpm_line.decode("utf-8",errors="replace").replace('\n',' ').replace('\r','')
        new_data = True

    #read from arduino Thermo1
    if (arduino2 in sl): 
        amp_line = arduino2.readline()
        amp_line = amp.decode("utf-8",errors="replace").replace('\n',' ').replace('\r','')
        new_data = True

    #If we just read something in, print it out!
    if (new_data):
        stamp = time.time() - start
        output_string = ("%.4f, %s, %s \n" % (stamp, rpm_line, amp_line))

        #amp_normal = 906
        #amp_slope = 300.0/ 0.625 / 32768 * 6.144 / 6
        print("                                                                     ", end='\r')
        if(stamp > writing_delay):
            output_file.write(output_string)

    new_data = False

arduino1.close()
arduino2.close()
