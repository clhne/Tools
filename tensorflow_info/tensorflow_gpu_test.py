import tensorflow as tf
# Return True if a gpu devices of the requests(whether TensorFlow can access a GPU)kind is available
print(tf.test.is_gpu_available(cuda_only=False, min_cuda_compute_capability=None))
