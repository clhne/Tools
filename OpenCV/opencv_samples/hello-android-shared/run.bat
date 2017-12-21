@ECHO OFF
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_calib3d.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_contrib.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_core.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_features2d.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_flann.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_gpu.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_highgui.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_imgproc.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_info.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_legacy.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_ml.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_nonfree.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_objdetect.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_ocl.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_photo.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_stitching.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_superres.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_video.so /data/local/tmp || GOTO end
adb push ../../opencv-2.4.13/platforms/android/build_android_shared_with_opencl/install/sdk/native/libs/armeabi-v7a/libopencv_videostab.so /data/local/tmp || GOTO end
adb push libs/armeabi-v7a/hello-android /data/local/tmp/hello-android || GOTO end

:: set execute permission
adb shell chmod 777 /data/local/tmp/hello-android || GOTO end

:: execute our application
adb shell LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/data/local/tmp /data/local/tmp/hello-android || GOTO end

:: get image result from device
adb pull /mnt/sdcard/HelloAndroid.png || GOTO end

GOTO end

:: cleanup (comment out GOTO above to enable cleanup)
adb shell rm /data/local/tmp/hello-android
adb shell rm /mnt/sdcard/HelloAndroid.png

:end
