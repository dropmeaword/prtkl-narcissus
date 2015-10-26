import os, sys
import time
import traceback
import bitalino
from OSC import OSCClient, OSCServer, OSCMessage

send_address = ('192.168.1.77', 55551) #('127.0.0.1', 55551)
bitadev = None
osctx = None

def osc_init():
    global osctx
    osctx = OSCClient()
    osctx.connect(send_address)

def bitalino_init():
    global bitadev
    port = '/dev/tty.bitalino-DevB' #"98:D3:31:B1:84:2C"

    batteryThreshold = 30
    acqChannels = [0,3]
    samplingRate = 1000
    #nSamples = 10
    digitalOutput = [0,0,1,1]

    try:
        bitadev = bitalino.BITalino(port)
        #print bitadev.battery(batteryThreshold)

        print "Bitalino version", bitadev.version()
        bitadev.start(samplingRate, acqChannels)
    except OSError as e:
        traceback.print_exc()
        print
        print "(!!!) Seems like the BITalino isn't online, pair your BITalino before trying again."
        print
        sys.exit(2)

def main():
    global bitadev, osctx
    osc_init()

    # while True:
    #     msg = OSCMessage()
    #     msg.setAddress("/init")
    #     msg.append([1, 2, 3, 4, 5, 6, 7, 8])
    #     print msg
    #     osctx.send( msg )
    #     time.sleep(2)

    bitalino_init()
    try:
        print "Entering reading loop..."
        while True:
            samples = bitadev.read(10)
            #bitadev.trigger(digitalOutput)
            for s in samples:
                msg = OSCMessage()
                msg.setAddress("/biosample")
                out = []

                for sval in s:
                    out.append(sval / 1024)

                msg.append(out)
                print msg
                osctx.send( msg )
    except KeyboardInterrupt as e:
        print "Looks like you wanna leave. Good bye!"
    finally:
        bitadev.stop()
        bitadev.close()

if __name__ == '__main__':
    print "Bitalino to OSC broker."
    print "(cc) 2015 Luis Rodil-Fernandez <zilog@protokol.cc>"
    print
    main()
