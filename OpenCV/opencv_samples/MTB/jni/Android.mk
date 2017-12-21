LOCAL_PATH := $(call my-dir)  
include $(CLEAR_VARS)  
OPENCV_LIB_TYPE := STATIC
ifeq ("$(wildcard $(OPENCV_MK_PATH))","")  
#try to load OpenCV.mk from default install location  
include ../../opencv-3.1.0/platforms/android/build_android_static_with_opencl/install/sdk/native/jni/OpenCV.mk 
else  
include $(OPENCV_MK_PATH)
endif  
LOCAL_MODULE    := MTB
LOCAL_SRC_FILES := main.cpp

LOCAL_CFLAGS += -fPIE
LOCAL_LDFLAGS += -fPIE -pie

include $(BUILD_EXECUTABLE)
