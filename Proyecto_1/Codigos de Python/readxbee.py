import time
from digi.xbee.devices import XBeeDevice
local_xbee = XBeeDevice("COM21", 9600)
local_xbee.open(force_settings=True)
# Read data sent by the remote device)
#local_xbee.open()
local_xbee.send_data_broadcast("Hello XBee World!")

xnet = local_xbee.get_network()

# Start the discovery process and wait for it to be over. 
xnet.start_discovery_process() 
#remote_device = RemoteXBeeDevice(local_xbee,XBee64BitAddress.from_hex_string("0013A200417D1E6E"))

while xnet.is_discovery_running(): 

    time.sleep(0.5)
    #remote_device = RemoteXBeeDevice(local_xbee,XBee64BitAddress.from_hex_string("0013A200417D1E6E"))
    xbee.read_data(remote_device)
    remote_list = xnet.discover_devices(["XBG2", "XBG3"])
    print(xbee_message)
# Get a list of the devices added to the network
#devices = xnet.get_devices()

local_xbee.close()
