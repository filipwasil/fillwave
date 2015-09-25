#!/bin/sh
#push eglretrace.so to phone
adb push /path/to/apitrace/build/wrappers/egltrace.so /data
#configure
PROCNAME=com.example.native_activity
adb root
adb shell setprop wrap.$PROCNAME LD_PRELOAD=/data/egltrace.so
adb shell setprop debug.apitrace.procname $PROCNAME
#start 
echo "Tracing $PROCNAME activity ..."
adb shell am start -S $PROCNAME
