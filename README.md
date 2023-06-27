# Real-Time-Filtering-Cpp
The provided code is a C++ program that implements real-time filtering on video input using OpenCV library. It includes various image processing functions such as grayscale conversion, blurring, edge detection, quantization, and more.

Here is a brief explanation of the functions defined in the code:

`greyscale`: This function converts an input color image to grayscale by calculating the average value of each pixel's RGB channels and assigning it to all three channels of the corresponding pixel in the destination image. 'g' key press for greyscale image in opencv window.
![image](https://github.com/josejosepht/Real-Time-Filtering-Cpp/assets/97187460/09e5a4ae-ecdd-492f-9c97-097d3b6ecdee)

`blur5x5`: This function applies a 5x5 blur filter to an input image. It performs horizontal and vertical blurring using a predefined kernel.'b' key press for blurred image in opencv window.
![image](https://github.com/josejosepht/Real-Time-Filtering-Cpp/assets/97187460/58e0cd68-96cc-4587-99e1-515f3cc8a3c1)


`sobelX3x3`: This function applies a 3x3 Sobel filter in the X-direction to detect horizontal edges in an input image.'x' key press for SobelX image in opencv window.
![image](https://github.com/josejosepht/Real-Time-Filtering-Cpp/assets/97187460/61331fe5-9380-41a1-b90d-0f87c75ab2db)


`sobelY3x3`: This function applies a 3x3 Sobel filter in the Y-direction to detect vertical edges in an input image.'y' key press for SobelY image in opencv window.

![image](https://github.com/josejosepht/Real-Time-Filtering-Cpp/assets/97187460/a41246cf-374c-4a8b-9a4e-8f15a1935f8c)


`magnitude`: This function computes the magnitude of gradient vectors at each pixel by combining the results from sobelX3x3 and sobelY3x3.'m' key press for magnitude image in opencv window.
![image](https://github.com/josejosepht/Real-Time-Filtering-Cpp/assets/97187460/064019fb-52d6-44b2-ba87-04f115a614b9)


`blurQuantize`: This function applies blurring using blur5x5 and then quantizes the colors of the image by dividing pixel values by a specified bucket size.'l' key press for blurred quantized image in opencv window.
![image](https://github.com/josejosepht/Real-Time-Filtering-Cpp/assets/97187460/d8805833-24e3-4615-ab19-0d451509a812)


`cartoon`: This function generates a cartoon-like effect on an input image by applying blurring and quantization with additional parameters for color levels and magnitude threshold.'g' key press for greyscale image in opencv window.'c' key press for cartoonized image in opencv window.
![image](https://github.com/josejosepht/Real-Time-Filtering-Cpp/assets/97187460/1a68c48e-2a42-4643-8a93-d38ab14e9d2f)


`negative`: This function creates the negative of an input image by subtracting each channel's pixel value from the maximum intensity value.'n' key press for negative image in opencv window.
![image](https://github.com/josejosepht/Real-Time-Filtering-Cpp/assets/97187460/0ebf3028-1c6b-4313-8c6a-d5b960a5f7b3)


The main function sets up the video capture from a camera device and handles keyboard input to select different filtering operations based on the pressed keys. It continuously captures frames, applies the selected filter, and displays the processed video stream.

Note that the code assumes the availability of the OpenCV library and related dependencies.
* filter.cpp and vidDisplay.cpp are to be placed in the Visual Studio project solution

* The implemented code for the filters on live video frames does not include a filter.h file as the filters are defined in filter.cpp inside the same Visual Studio 
project solution. The function prototypes declared at the top of vidDisplay.cpp call the required functions from filter.cpp

* When the user presses 's' key after running the program, the savedImage.jpg file is saved to the current directory
