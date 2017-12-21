#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/photo/photo.hpp>
#include <fstream>
#include <iostream>

using namespace cv;
using namespace std;

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#include <unistd.h>
#endif
#ifdef _WIN32
#define uint64_t unsigned __int64
uint64_t performanceCounter() {
  LARGE_INTEGER result;
  QueryPerformanceCounter(&result);
  return result.QuadPart;
}

uint64_t performanceFrequency() {
  LARGE_INTEGER result;
  QueryPerformanceFrequency(&result);
  return result.QuadPart;
}
#else // _WIN32
uint64_t performanceCounter() {
  uint64_t result = 0;
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  result = (uint64_t)ts.tv_sec * 1000000000LL + (uint64_t)ts.tv_nsec;
  return result;
}

uint64_t performanceFrequency() {
  uint64_t result = 1;
  result = 1000000000LL;
  return result;
}
#endif // _WIN32
double getDurationSec(uint64_t prev) {
  return (double)(performanceCounter() - prev)/performanceFrequency();
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
  	cout<<"Usage:./MTB [image name]"<<endl;
  	return -1;
  }
 
  if (ocl::haveOpenCL()) {
    std::vector<ocl::PlatformInfo> platforms;
    ocl::getPlatfomsInfo(platforms);
    const ocl::PlatformInfo* platform = &platforms[0];
    printf("Platform Name: %s\n", platform->name().c_str());
    ocl::Device device;
    platform->getDevice(device, 0);
    printf("Device Name: %s\n" , device.name().c_str());
    device.set(0);
    ocl::setUseOpenCL(true);
    printf("Use OpenCL: %s\n" , ocl::useOpenCL() ? "YES" : "NO");
  }
  
  int N = argc - 1;
  vector<Mat> images;
  vector<Mat> aligned_images;
  for (int i = 0; i < N; i++) {
    Mat img = imread(argv[i + 1]);
    if (!img.data) {
      cout << "Read image \"" << argv[i + 1] << "\" failed" << endl;
      return -1;
    }
    images.push_back(img);
  }

  int max_bits = 5;
  int max_shift = 32;
  Ptr<AlignMTB> mtb = createAlignMTB(max_bits);
  double TEST_COSTS = 0.0;
  const int TEST_TIMES = 5;
  for (int i = 0; i < TEST_TIMES; i++) {
  	printf("loop %d: ", i);
    uint64_t now = performanceCounter();
    
    mtb->process(images, aligned_images);
    
    double duration = getDurationSec(now);
    printf(" %f s\n", duration);
    if (i > 0) {
      TEST_COSTS += duration;
    }
  }
  printf("average time-cost of dft: %f s\n", TEST_COSTS / (TEST_TIMES - 1));
  
  for (int i = 0; i < N; i++) {
    imwrite(string(argv[i + 1]).append(".aligned.jpg"), aligned_images[i]);
  }
  
  return 0;
}

