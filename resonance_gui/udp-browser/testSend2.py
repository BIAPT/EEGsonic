import optparse,time,random
from OSC import *
from OSC import _readString, _readFloat, _readInt

c = OSCClient()
c.connect(('127.0.0.1',7400))
print c

while True:
  m = OSCMessage("/bvp")
  m += [random.randrange(200)]
  c.send(m)
  time.sleep(0.3)

c.close()
