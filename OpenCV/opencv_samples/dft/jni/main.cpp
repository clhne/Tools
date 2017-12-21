#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/ocl.hpp>
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
  	cout<<"Usage:./dft [image name]"<<endl;
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
  
  // Read as grayscale image
  Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  if (!image.data) {
    cout << "Read image \"" << argv[1] << "\" failed" << endl;
    return -1;
  }
  
  // Padding image by copying border
  Mat image_padded;
  int m = getOptimalDFTSize(image.rows);  // Return size of 2^x that suite for FFT
  int n = getOptimalDFTSize(image.cols);
  printf("Padded size %dx%d\n", n, m);
  copyMakeBorder(image, image_padded, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT, Scalar::all(0));
  
  // Create planes to storage REAL part and IMAGE part, IMAGE part init are 0
  Mat planes[] = {Mat_<float>(image_padded), Mat::zeros(image_padded.size(), CV_32F) };
  Mat complexI;
  merge(planes, 2, complexI);
    
  double TEST_COSTS = 0.0;
  const int TEST_TIMES = 5;
  for (int i = 0; i < TEST_TIMES; i++) {
  	printf("loop %d: ", i);
    uint64_t now = performanceCounter();
    
    UMat complexI_umat;
    complexI.copyTo(complexI_umat);
    dft(complexI_umat, complexI_umat);
    complexI_umat.copyTo(complexI);
    
    double duration = getDurationSec(now);
    printf(" %f s\n", duration);
    if (i > 0) {
      TEST_COSTS += duration;
    }
  }
  printf("average time-cost of dft: %f s\n", TEST_COSTS / (TEST_TIMES - 1));

  // compute the magnitude and switch to logarithmic scale
  split(complexI, planes);
  magnitude(planes[0], planes[0], planes[1]);
  Mat magI = planes[0];
   
  // => log(1+sqrt(Re(DFT(I))^2+Im(DFT(I))^2))
  magI += Scalar::all(1);
  log(magI, magI);

  normalize(magI, magI, 0, 1, CV_MINMAX);
  
  imwrite(argv[2], magI * 255.0f);
  
  return 0;
}

