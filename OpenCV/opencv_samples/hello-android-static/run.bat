@ECHO OFF
adb push libs/armeabi-v7a/hello-android /data/local/tmp/hello-android || GOTO end

:: set execute permission
adb shell chmod 777 /data/local/tmp/hello-android || GOTO end

:: execute our application
adb shell /data/local/tmp/hello-android || GOTO end

:: get image result from device
adb pull /mnt/sdcard/HelloAndroid.png || GOTO end

GOTO end

:: cleanup (comment out GOTO above to enable cleanup)
adb shell rm /data/local/tmp/hello-android
adb shell rm /mnt/sdcard/HelloAndroid.png

:end
