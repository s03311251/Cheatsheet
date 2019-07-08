/*----------Installation----------*/
/* http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html

1. $ cd ~/opencv-3.3.0
2. $ mkdir release && cd release
3. $ cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
4. $ mkdir ../cmake_binary_dir && cd ../cmake_binary_dir
5. $ make

	Error: fatal error: Eigen/Eigenvalues: No such file or directory 

	5.1 $ sudo apt-get install libeigen3-dev
	5.2 $ whereis eigen3 (eigen3: /usr/include/eigen3)
	5.3 $ cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D EIGEN_INCLUDE_PATH=/usr/include/eigen3 ..
	5.4 $ make

6. $ sudo make install
*/



/*----------Eclipse Configuration----------*/
/* http://docs.opencv.org/master/d7/d16/tutorial_linux_eclipse.html

1. make a new project
2. Tell OpenCV where the OpenCV headers and libraries are
	2.1 $ pkg-config --cflags opencv
	    (-I/usr/local/include/opencv -I/usr/local/include)

	2.2 Go to Project -> Properties
	2.3 In C/C++ Build, click on Settings. At the right, choose the Tool Settings Tab. Here we will enter the headers and libraries info:
	2.4 In GCC C++ Compiler, go to Includes. In Include paths(-l) you should include the path of the folder where opencv was installed. In our example, this is /usr/local/include/opencv.

3. 
	3.1 $ pkg-config --libs opencv
	    (-L/usr/local/lib -lopencv_dnn -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core)
	3.2 Now go to GCC C++ Linker,there you have to fill two spaces:
	3.3 First in Library search path (-L) you have to write the path to where the opencv libraries reside, in my case the path is: /usr/local/lib
	3.4 In Libraries(-l), the OpenCV libraries that you may need: (usually opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui are enough) (or add all list above)
	3.5 APPLY!!!!!

4. You may build now
5. execute the program

	error while loading shared libraries: libopencv_highgui.so.3.3: cannot open shared object file: No such file or directory

	https://stackoverflow.com/questions/27907343/error-while-loading-shared-libraries-libopencv-core-so-3-0
	5.1a $ export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib
	5.2a Run again

	5.1b Run As -> Run Configurations
	5.2b Click Environment tab
	5.3b New.. -> Name: LD_LIBRARY_PATH, Value: $LD_LIBRARY_PATH:/usr/local/lib
	5.4b APPLY!!!!!

*/



/*----------Display image----------*/
#include <opencv2/opencv.hpp>
using namespace cv;
int main( int argc, char** argv ) {
	Mat image;
	image = imread( argv[1], IMREAD_COLOR ); // read file
	// IMREAD_UNCHANGED (<0) loads the image as is (including the alpha channel if present)
    // IMREAD_GRAYSCALE (0) loads the image as an intensity one
    // IMREAD_COLOR (>0) loads the image in the BGR format

	if( argc != 2 || !image.data ) // image.empty() == !image.data
		{
			printf( "No image data \n" );
			return -1;
		}
	namedWindow( "Display Image", WINDOW_AUTOSIZE ); // create a window
	// WINDOW_NORMAL enables you to resize the window
	// can use WINDOW_AUTOSIZE | WINDOW_KEEPRATIO | WINDOW_GUI_EXPANDED

	imshow( "Display Image", image ); // show window
	waitKey(0); // wait for a keystroke in the window
	return 0;
}



/*----------Covert colour----------*/
	Mat grey_image;
	cvtColor(image, grey_image, COLOR_BGR2GRAY);



/*----------Save file----------*/
	imwrite("grey.jpg", grey_image);



/*----------Mat----------*/
// Mat object has its own header, but matrix may be shared 
// copy operators will only copy the headers and the pointer to the large matrix, not the data itself.

// clone
// clone the matrix
	Mat F = A.clone();
	Mat G;
	A.copyTo(G);








