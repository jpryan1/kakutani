FLAGS = -I/usr/local/Cellar/opencv/2.4.12_2/include/opencv -I/usr/local/Cellar/opencv/2.4.12_2/include -L/usr/local/Cellar/opencv/2.4.12_2/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy  -lopencv_photo 

default:
	g++ $(FLAGS) kakutani.cpp boundary.cpp -o kakutani


random:
	g++ $(FLAGS) random.cpp -o ran
