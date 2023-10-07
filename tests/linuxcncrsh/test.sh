#!/bin/bash

rm -f gcode-output

if nc -z localhost 5007; then
    echo "Process already listening on port 5007. Exiting"
    exit 1
fi

linuxcnc -r linuxcncrsh-test.ini &


# let linuxcnc come up
TOGO=80
while [  $TOGO -gt 0 ]; do
    echo trying to connect to linuxcncrsh TOGO=$TOGO
    if nc -z localhost 5007; then
        break
    fi
    sleep 0.25
    TOGO=$(($TOGO - 1))
done
if [  $TOGO -eq 0 ]; then
    echo connection to linuxcncrsh timed out
    exit 1
fi


(
    echo hello EMC mt 1.0
    echo set enable EMCTOO
    echo get enable
    
    # ask linuxcncrsh to not read the next command until it's done running
    # the current one
    echo set set_wait done
    echo get set_wait

    echo set mode manual
    echo get mode

    echo set estop off
    echo get estop

    echo set machine on
    echo get machine

    # test spindle command
    echo set spindle forward -1    # turn on all spindles
    echo get spindle -1
    echo set spindle off            # turn off all spindles
    echo get spindle

    # prepare g-code sending
    echo set mode mdi
    echo get mode

    echo set mdi m100 p-1 q-2
    sleep 1

    # here comes a big blob
    dd bs=4096 if=lots-of-gcode

    echo set mdi m100 p-3 q-4

    echo shutdown
) | nc -v localhost 5007 > telnet-output


# wait for linuxcnc to finish
wait

exit 0
