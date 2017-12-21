@ECHO OFF
adb push lena_151_151.jpg /data/local/tmp
adb push lena_512_512.jpg /data/local/tmp
adb push lena_1280_720.jpg /data/local/tmp
adb push lena_1920_1080.jpg /data/local/tmp
adb push libs/armeabi-v7a/dft /data/local/tmp
adb shell chmod 777 /data/local/tmp/dft
ECHO lena_151_151
adb shell /data/local/tmp/dft /data/local/tmp/lena_151_151.jpg /data/local/tmp/lena_151_151_result.jpg
adb pull /data/local/tmp/lena_151_151_result.jpg .
ECHO lena_512_512
adb shell /data/local/tmp/dft /data/local/tmp/lena_512_512.jpg /data/local/tmp/lena_512_512_result.jpg
adb pull /data/local/tmp/lena_512_512_result.jpg .
ECHO lena_1280_720
adb shell /data/local/tmp/dft /data/local/tmp/lena_1280_720.jpg /data/local/tmp/lena_1280_720_result.jpg
adb pull /data/local/tmp/lena_1280_720_result.jpg .
ECHO lena_1920_1080
adb shell /data/local/tmp/dft /data/local/tmp/lena_1920_1080.jpg /data/local/tmp/lena_1920_1080_result.jpg
adb pull /data/local/tmp/lena_1920_1080_result.jpg .

