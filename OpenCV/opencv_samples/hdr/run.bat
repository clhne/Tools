@ECHO OFF
REM adb push house.txt /data/local/tmp/config.txt
REM adb push house.0.bmp /data/local/tmp
REM adb push house.1.bmp /data/local/tmp
REM adb push house.2.bmp /data/local/tmp
REM adb push house.3.bmp /data/local/tmp

REM adb push st.txt /data/local/tmp/config.txt
REM adb push st0.jpg /data/local/tmp
REM adb push st1.jpg /data/local/tmp
REM adb push st2.jpg /data/local/tmp

adb push lc1860.txt /data/local/tmp/config.txt
adb push lc1860_exposure_compensation_-6.jpg /data/local/tmp
adb push lc1860_exposure_compensation_-5.jpg /data/local/tmp
adb push lc1860_exposure_compensation_-4.jpg /data/local/tmp
adb push lc1860_exposure_compensation_-3.jpg /data/local/tmp
adb push lc1860_exposure_compensation_-2.jpg /data/local/tmp
adb push lc1860_exposure_compensation_-1.jpg /data/local/tmp
adb push lc1860_exposure_compensation_0.jpg /data/local/tmp
adb push lc1860_exposure_compensation_1.jpg /data/local/tmp
adb push lc1860_exposure_compensation_2.jpg /data/local/tmp
adb push lc1860_exposure_compensation_3.jpg /data/local/tmp
adb push lc1860_exposure_compensation_4.jpg /data/local/tmp
adb push lc1860_exposure_compensation_5.jpg /data/local/tmp
adb push lc1860_exposure_compensation_6.jpg /data/local/tmp

adb push libs/armeabi-v7a/hdr /data/local/tmp
adb shell chmod 777 /data/local/tmp/hdr
adb shell /data/local/tmp/hdr
adb pull /data/local/tmp/hdr.hdr .
adb pull /data/local/tmp/ldr.png .
adb pull /data/local/tmp/respose.csv .

