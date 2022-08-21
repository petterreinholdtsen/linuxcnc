#!/usr/bin/env python3

import linuxcnc
import hal
import sys
import os

# unbuffer stdout
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w')

retval = 0

#
# set up pins
# shell out to halcmd to make nets to halui and motion
#

h = hal.component("python-ui")
h.newpin("ext-estop-button", hal.HAL_BIT, hal.HAL_OUT)
h.ready() # mark the component as 'ready'

hal.connect('python-ui.ext-estop-button', 'ext-estop')

#
# connect to LinuxCNC
#

c = linuxcnc.command()
s = linuxcnc.stat()
e = linuxcnc.error_channel

c.state(linuxcnc.STATE_ESTOP_RESET)
c.state(linuxcnc.STATE_ON)
c.wait_complete()

h['ext-estop-button'] = 1

if False != hal.get_value('estop-all-ok'):
    print("error: estop still OK aftet ext-estop-button is set")
    retval = 1

h['ext-estop-button'] = 0

if True != hal.get_value('estop-all-ok'):
    print("error: estop not OK aftet ext-estop-button is unset")
    retval = 1

    sys.exit(retval)

