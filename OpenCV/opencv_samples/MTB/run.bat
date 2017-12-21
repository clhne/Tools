@ECHO OFF
adb push lc1860_exposure_compensation_-6.jpg /data/local/tmp
adb push lc1860_exposure_compensation_0.jpg /data/local/tmp
adb push lc1860_exposure_compensation_6.jpg /data/local/tmp
adb push libs/armeabi-v7a/MTB /data/local/tmp
adb shell chmod 777 /data/local/tmp/MTB
adb shell LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/system/lib/egl:/data/local/tmp /data/local/tmp/MTB /data/local/tmp/lc1860_exposure_compensation_-6.jpg /data/local/tmp/lc1860_exposure_compensation_0.jpg /data/local/tmp/lc1860_exposure_compensation_6.jpg
adb pull /data/local/tmp/lc1860_exposure_compensation_-6.jpg.aligned.jpg .
adb pull /data/local/tmp/lc1860_exposure_compensation_0.jpg.aligned.jpg .
adb pull /data/local/tmp/lc1860_exposure_compensation_6.jpg.aligned.jpg .
