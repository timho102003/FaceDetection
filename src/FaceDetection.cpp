#include <iostream>
#include <opencv2/opencv.hpp>
#include "Detector.h"
#include <time.h>
#include <memory>
#include <queue>
#include <thread>
#include <mutex>
#include <stdexcept>
using namespace std;

std::mutex mutex1, mutex2, mutex3;
std::condition_variable _cond;

int main(int argc, char **argv)
{
    cv::CommandLineParser parser(argc, argv,
                                 "{help  h           |            | Print this message.}"
                                 "{input v           |            | Path to the input video. Omit for detecting on default camera.}"
                                 "{backend_id        | 0          | Backend to run on. 0: default, 1: Halide, 2: Intel's Inference Engine, 3: OpenCV, 4: VKCOM, 5: CUDA}"
                                 "{target_id         | 0          | Target to run on. 0: CPU, 1: OpenCL, 2: OpenCL FP16, 3: Myriad, 4: Vulkan, 5: FPGA, 6: CUDA, 7: CUDA FP16, 8: HDDL}"
                                 "{model m           | yunet.onnx | Path to the model. Download yunet.onnx in https://github.com/ShiqiYu/libfacedetection.train/tree/master/tasks/task1/onnx.}"
                                 "{score_threshold   | 0.9        | Filter out faces of score < score_threshold.}"
                                 "{nms_threshold     | 0.3        | Suppress bounding boxes of iou >= nms_threshold.}"
                                 "{top_k             | 5000       | Keep top_k bounding boxes before NMS.}"
                                 "{save  s           | false      | Set true to save results. This flag is invalid when using camera.}"
                                 "{vis   v           | true       | Set true to open a window for result visualization. This flag is invalid when using camera.}");
    if (argc == 1 || parser.has("help"))
    {
        parser.printMessage();
        return -1;
    }
    cout << "########### Face Detection C++ ###########" << endl;
    cv::String modelPath = parser.get<cv::String>("model");
    int backendId = parser.get<int>("backend_id");
    int targetId = parser.get<int>("target_id");
    float scoreThreshold = parser.get<float>("score_threshold");
    float nmsThreshold = parser.get<float>("nms_threshold");
    int topK = parser.get<int>("top_k");
    bool save = parser.get<bool>("save");
    bool vis = parser.get<bool>("vis");

    cout << "########### Args Setting  ###########" << endl;
    cout << "ModelPath: " << modelPath << endl;
    cout << "backendId: " << backendId << endl;
    cout << "targetId: " << targetId << endl;
    cout << "scoreThreshold: " << scoreThreshold << endl;
    cout << "nmsThreshold: " << nmsThreshold << endl;
    cout << "topK: " << topK << endl;
    cout << "save: " << save << endl;
    cout << "vis: " << vis << endl;

    cv::VideoCapture capture;

    // Setting Detector Model:
    Detector detector;
    detector.setConfig(
        modelPath,
        "",
        cv::Size(320, 320),
        scoreThreshold,
        nmsThreshold,
        topK,
        backendId,
        targetId);
    detector.build(); // build model

    if (parser.has("input"))
    {
        std::string source = parser.get<std::string>("input");
        capture.open(source);
        if (!capture.isOpened())
        {
            cout << "Could not open the input video: " << source << endl;
            return -1;
        }
        cout << "Video File has been started ..." << endl;
    }
    else
    {
        std::cout << "Please provide video clips" << std::endl;
        return -1;
    }

    int frameWidth = int(capture.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = int(capture.get(cv::CAP_PROP_FRAME_HEIGHT));
    detector.model->setInputSize(cv::Size(frameWidth, frameHeight));

    cv::Mat frame;
    cv::TickMeter tm;
    clock_t start, finish;
    std::queue<cv::Mat> video_input_queue;
    std::queue<cv::Mat> video_show_queue;

    std::cout << "Start Initializing Video..." << std::endl; 
    int preload_cnt = 0;
    while(preload_cnt<60){
        capture >> frame;
            if (frame.empty()){
            if (video_input_queue.size()==0){
                std::cout << "Error: video is empty";
                return -1;
            }else{
                break;
            }
        }
        video_input_queue.push(frame);
        preload_cnt++;
    }
    std::cout << "Video Frame " << video_input_queue.size() << " are preloaded into queue." << std::endl;
    std::cout << "Finish Initializing Video..." << std::endl; 

    bool is_video_end = false;
    bool is_input_queue_end = false;

    for(;;)
    {
        // start = clock();
        capture >> frame;
        cv::Mat current_frame;
        if (!frame.empty())
            video_input_queue.push(frame);
        if (!video_input_queue.empty()){
            current_frame = video_input_queue.front();
            video_input_queue.pop();
        }
        cv::Mat faces;
        auto f0 = [&detector, &current_frame, &video_show_queue]() {
            detector.forward(current_frame);
            std::shared_ptr<cv::Mat> show_frame = std::make_shared<cv::Mat>(current_frame.clone());
            detector.simulate(show_frame);
            std::lock_guard<std::mutex> lock1(mutex1);
            video_show_queue.push(*show_frame.get());
        };
        std::thread t1 = std::thread(f0);
        if (!video_show_queue.empty()){
            std::lock_guard<std::mutex> lock2(mutex2);
            cv::Mat current_show = video_show_queue.front();
            video_show_queue.pop();
            cv::imshow("face detection", current_show);
        }
        t1.join();
        char c = (char)cv::waitKey(10);
        if (c == 27 || c == 'q' || c == 'Q')
            break;
    }
    std::cout << "Finish Face Detection!!" << std::endl;
    return 0;
}
