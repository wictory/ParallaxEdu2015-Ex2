#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <iostream>
#include <memory>
#include <atomic>
#include <stdio.h>

#include "Queue.h"

using namespace std;
using namespace cv;

class MyFrame {
    
    shared_ptr<Mat> self;

public:

    MyFrame(Mat& m) {
	self = make_shared<Mat>(m);
    }

    MyFrame(MyFrame&& f) {
	self = f.self;
	f.self = nullptr;
    }

    ~MyFrame() {
	// if (self != nullptr) {
	//     cout << "destroyed something" << endl;
	// } else {
	//     cout << "destroy" << endl;
	// }
	self = nullptr;
    }

    void pr(function<void(Mat &m)> f) {
    	f(*self);
    }

    const Mat get() const {
	return *self;
    }

};

int main( int argc, const char** argv )
{
    atomic<bool> still_running(true);
    bool have_camera = true;

    // VideoCapture capture("./big_buck_bunny.ogv");
    VideoCapture capture(0);
    if (!capture.isOpened()) {
	cout << "No camera detected" << endl;
	have_camera = false;
	capture = VideoCapture("./big_buck_bunny.ogv");
    }

    Queue<MyFrame> q1;
    Queue<MyFrame> q2;
    Queue<MyFrame> q3;

    if( capture.isOpened() )
    {
        cout << "In capture ..." << endl;
	vector<thread> threads;

	threads.push_back(std::thread([&]() {
		while (still_running) {
		    Mat f;
		    capture.read(f);
		    // capture >> f;
		    MyFrame frame(f);

		    cout << "s1" << endl;
		    if (frame.get().empty()) {
			still_running = false;
			break;
		    }
		    q1.push(std::move(frame));
		}
		cout << "Stopping s1" << endl;
		capture.release();
	    }));

	threads.push_back(std::thread([&]() {
		while (still_running) {
		    // auto f = q1.pop();
		    // f.process();
		    auto&& frame = q1.pop();
		    cout << "s2" << endl;
		    // frame.process();
		    frame.pr([](Mat &m) {
			    cvtColor(m, m, CV_RGB2GRAY);
			    // Canny(m, m, 20, 20, 3);
			});
		    q2.push(std::move(frame));
		}
		cout << "Stopping s2" << endl;
	    }));

	threads.push_back(std::thread([&]() {
		    while(still_running) {
			auto&& frame = q2.pop();
			cout << "s3" << endl;
			frame.pr([](Mat &m) {
				Canny(m, m, 20, 20, 3);
			    });
			q3.push(std::move(frame));
		    }
		    cout << "Stopping s3" << endl;
		}));

	if (have_camera) {
	    threads.push_back(std::thread([&]() {
			namedWindow("result");
			while (still_running) {
			    // auto&& frame = q2.pop();
			    // auto&& mat = frame.get();
			    auto frame = q3.pop().get();
			    cout << "s4" << endl;
			    // cvShowImage("result", &frame);
			    imshow("result", frame);
			    if (waitKey(10) >= 0) {
				still_running = false;
				break;
			    }
			}
			cout << "Stopping s4" << endl;
		    }));
	} else {
	    threads.push_back(std::thread([&]() {
			while (still_running) {
			    auto frame = q3.pop().get();
			    cout << "s4" << endl;
			}
		    }));
	}

	for (auto&& t : threads) {
	    t.join();
	}

        waitKey(0);
	
	if (have_camera) {
	    cvDestroyWindow("result");
	}

	return 0;
    }
}
