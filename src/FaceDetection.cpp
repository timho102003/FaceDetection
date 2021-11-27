#include <iostream>
#include <opencv2/opencv.hpp>
#include "Detector.h"
#include <time.h>

using namespace std;

static cv::Mat visualize(cv::Mat input, cv::Mat faces, bool print_flag=false, double fps=-1, int thickness=2)
{
    cv::Mat output = input.clone();

    if (fps > 0) {
        cv::putText(output, cv::format("FPS: %.2f", fps), cv::Point2i(0, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0));
    }

    for (int i = 0; i < faces.rows; i++)
    {
        if (print_flag) {
            cout << "Face " << i
                 << ", top-left coordinates: (" << faces.at<float>(i, 0) << ", " << faces.at<float>(i, 1) << "), "
                 << "box width: " << faces.at<float>(i, 2)  << ", box height: " << faces.at<float>(i, 3) << ", "
                 << "score: " << faces.at<float>(i, 14) << "\n";
        }

        // Draw bounding box
        cv::rectangle(output, cv::Rect2i(int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1)), int(faces.at<float>(i, 2)), int(faces.at<float>(i, 3))), cv::Scalar(0, 255, 0), thickness);
        // Draw landmarks
        cv::circle(output, cv::Point2i(int(faces.at<float>(i, 4)),  int(faces.at<float>(i, 5))),  2, cv::Scalar(255,   0,   0), thickness);
        cv::circle(output, cv::Point2i(int(faces.at<float>(i, 6)),  int(faces.at<float>(i, 7))),  2, cv::Scalar(  0,   0, 255), thickness);
        cv::circle(output, cv::Point2i(int(faces.at<float>(i, 8)),  int(faces.at<float>(i, 9))),  2, cv::Scalar(  0, 255,   0), thickness);
        cv::circle(output, cv::Point2i(int(faces.at<float>(i, 10)), int(faces.at<float>(i, 11))), 2, cv::Scalar(255,   0, 255), thickness);
        cv::circle(output, cv::Point2i(int(faces.at<float>(i, 12)), int(faces.at<float>(i, 13))), 2, cv::Scalar(  0, 255, 255), thickness);
        // Put score
        cv::putText(output, cv::format("%.4f", faces.at<float>(i, 14)), cv::Point2i(int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1))+15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0));
    }
    return output;
}

int main(int argc, char ** argv) {
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
        "{vis   v           | true       | Set true to open a window for result visualization. This flag is invalid when using camera.}"
    );
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
        targetId
    );
    detector.build(); // build model

    cv::Mat frame;
    if (parser.has("input")){
        std::string source = parser.get<std::string>("input");
        capture.open(source);
        if (!capture.isOpened())
        {
            cout  << "Could not open the input video: " << source << endl;
            return -1;
        }
        cout << "Video File has been started ..." << endl;
    }else{
        int deviceId = 0;
        capture.open(deviceId, cv::CAP_ANY);
        if( capture.isOpened() )
        {
            cout << "Video capturing has been started ..." << endl;
            
        }else{
            cout << "Can't open camera!!" << endl;
        }
    }

    int frameWidth = int(capture.get(cv::CAP_PROP_FRAME_WIDTH));
    int frameHeight = int(capture.get(cv::CAP_PROP_FRAME_HEIGHT));
    detector.model->setInputSize(cv::Size(frameWidth, frameHeight));
    
    cv::TickMeter tm;
    clock_t start, finish;
    for(;;)
    {
        start = clock();
        capture >> frame;
        if( frame.empty() )
            break;
        cv::Mat faces;
        // tm.start();
        detector.model->detect(frame, faces);
        cv::Mat vis_frame = visualize(frame, faces, false);
        // tm.stop();
        finish = clock();
        double duration = (double)(finish - start) / CLOCKS_PER_SEC;
        double fps = 1 / duration;
        cv::putText(vis_frame, cv::format("FPS: %.2f", fps), cv::Point2i(0, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0));
        imshow("libfacedetection demo", vis_frame);
        // tm.reset();
        char c = (char)cv::waitKey(10);
        if( c == 27 || c == 'q' || c == 'Q' )
            break;
    }
    
    return 0;
}