#include <opencv2/core/core.hpp>
#include <opencv2/photo/photo.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <iostream>

using namespace cv;
using namespace std;

static vector<float> DEFAULT_VECTOR;
void loadExposureSeq(String path, vector<Mat>& images, vector<float>& times = DEFAULT_VECTOR)
{
    ifstream list_file((path + "config.txt").c_str());
    assert(list_file.is_open());
    string name;
    float val;
    while(list_file >> name >> val) {
        Mat img = imread(path + name);
        assert(img.empty());
        images.push_back(img);
        times.push_back(1 / val);
    }
    list_file.close();
}

int main(int argc, char* argv[])
{
  vector<Mat> images;
  vector<float> times;
  loadExposureSeq("/data/local/tmp/", images, times);
  printf("%d, %d\n", images[0].cols, images[0].rows);
  for (int i = 0; i < times.size(); ++i) {  
     cout << times[i] << endl;  
  }
  Mat response;
  Ptr<CalibrateDebevec> calibrate = createCalibrateDebevec();
  calibrate->process(images, response, times);
  printf("%f\n", response.at<float>(0,0));
  ofstream file("/data/local/tmp/respose.csv");
  file << format(response, Formatter::FMT_CSV);
  file.close();
  
  Mat hdr;
  Ptr<MergeDebevec> merge_debevec = createMergeDebevec();
  merge_debevec->process(images, hdr, times, response);
  
  Mat ldr;
  Ptr<TonemapDurand> tonemap = createTonemapDurand(2.2f);
  tonemap->process(hdr, ldr);
  
  imwrite("/data/local/tmp/ldr.png", ldr * 255);
  imwrite("/data/local/tmp/hdr.hdr", hdr);

  return 0;
}

