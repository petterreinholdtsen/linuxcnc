#!/bin/sh

set -e
set -x

Xvfb :1 &
XPID=$!
export DISPLAY=:1

cleanup() {
    if [ -n "$CNCPID" ] && kill -0 "$CNCPID"; then
	kill $CNCPID
    fi
    if [ -n "$VNCPID" ] && kill -0 "$VNCPID"; then
	kill $VNCPID
    fi
    kill $XPID
}
trap cleanup EXIT

screenmovie()
(
    TMPDIR=`mktemp -d /tmp/simpletest.snapshot.XXXXXX`
    while kill -0 $XPID ; do
	scrot $TMPDIR/linuxcncrunning.jpeg || true
	sleep 1
    done
    # Avoid date --iso=m or =h, as ffmpeg get confused by : in out file name
    ffmpeg -f image2 \
	   -r 8 \
	   -i "$TMPDIR/linuxcncrunning_%03d.jpeg" \
	   "testrun-$(date --iso).mov"
    rm -rf $TMPDIR
)

wait_for_pin() {
    pin="$1"
    value="$2"
    maxwait=10 # seconds
    while [ 0 -lt $maxwait ] \
      && [ "$value" != "$(halcmd -s show pin $pin | awk '{print $4}')" ]; do
        sleep 1
        maxwait=$(($maxwait -1))
    done
    if [ 0 -eq $maxwait ] ; then
        echo "error: waiting for pin $pin timed out"
        exit 1
    fi
}

# Wait for X display to start working
while ! xhost > /dev/null 2>&1; do
    sleep 1
done

screenmovie &

# VLC is useful for debugging
if false; then
    VNCOPTS="-unixsoc /tmp/vncsock"
    x11vnc $VNCOPTS &
    VNCPID=$!
    sleep 5
fi

linuxcnc &
CNCPID=$!

#wait_for_pin motion.in-position TRUE
sleep 5

cnee --replay -f xnee.xns -v -ns
