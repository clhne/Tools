import tensorflow as tf
# Return True if TensorFlow was build with CUDA(GPU)support
# print(tf.test.is_built_with_cuda())
if tf.test.is_built_with_cuda():
    print("The installed version of TensorFlow includes GPU support.")
else:
    print("The installed version of TensorFlow does not includes GPU support.")
