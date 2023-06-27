# Real-Time-Filtering-Cpp
The provided code is a C++ program that implements real-time filtering on video input using OpenCV library. It includes various image processing functions such as grayscale conversion, blurring, edge detection, quantization, and more.

Here is a brief explanation of the functions defined in the code:

`greyscale`: This function converts an input color image to grayscale by calculating the average value of each pixel's RGB channels and assigning it to all three channels of the corresponding pixel in the destination image.

`blur5x5`: This function applies a 5x5 blur filter to an input image. It performs horizontal and vertical blurring using a predefined kernel.

`sobelX3x3`: This function applies a 3x3 Sobel filter in the X-direction to detect horizontal edges in an input image.

`sobelY3x3`: This function applies a 3x3 Sobel filter in the Y-direction to detect vertical edges in an input image.

`magnitude`: This function computes the magnitude of gradient vectors at each pixel by combining the results from sobelX3x3 and sobelY3x3.

`blurQuantize: This function applies blurring using blur5x5 and then quantizes the colors of the image by dividing pixel values by a specified bucket size.

`cartoon`: This function generates a cartoon-like effect on an input image by applying blurring and quantization with additional parameters for color levels and magnitude threshold.

`negative`: This function creates the negative of an input image by subtracting each channel's pixel value from the maximum intensity value.

The main function sets up the video capture from a camera device and handles keyboard input to select different filtering operations based on the pressed keys. It continuously captures frames, applies the selected filter, and displays the processed video stream.

Note that the code assumes the availability of the OpenCV library and related dependencies.
