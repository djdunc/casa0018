# Mask detect on Arduino Nano 33 BLE

ChenYifan

## Introduction
- an overview of what the project does
- your inspiration for making the project 
- examples that it is based on. 
As the COVID-19 epidemic gets worse, more and more people are aware of the importance of wearing masks outside. While existing vaccines, go out with mask is still necessary, but not all the people wear masks, therefore the aim of this project is to realize mask wearing recognition on Arduino Nano 33 BLE. The project goal is on the Arduino platform achieved the identification of whether wearing masks and make a mask recognition machine and be able to use it anytime and anywhere by cameras. This project first wrote code in Colab Notebook for model training, and then adopted Edge Impulse platform for model training.

*probably ~200 words and images are good!*

## Research Question
How to build and train a Convolutional Neural Network (CNN) image recognition classification model to realize mask recognition based on Arduino 33 BLE platform and Arducam

*probably 1 or 2 sentences*

## Application Overview
The overall structure of the project is shown below. The Saved Model is taken as the boundary to divide the project work into two parts: Model training and Model running.

![image](https://user-images.githubusercontent.com/72681393/115410196-036e9300-a225-11eb-913a-ed01c347db38.png)

The model training was carried out on the Google platform and Edge Impulse platform. The required data sets were collected according to the analysis of the project objectives, and the appropriate neural network architecture was selected for model training and model transformation.The model is implemented at the Arduino end. The Arducam module is responsible for sensing the outside world and sending images to the Arduino Nano 33 BLE Sense as the model input. The input data is recognized in real time and the output results are obtained.The Arduino program frame is shown below.

![image](https://user-images.githubusercontent.com/72681393/115411200-db336400-a225-11eb-8325-4f346ade0284.png)

Arduino can recognize whether people are wearing masks in real time according to the images sent back by the camera, and output the results through the serial port. At the same time, the color of the on-board RGB light can be changed according to the results.



## Data
Data sets of mask recognition cases from several GitHub and some pictures of me and my family have been used to get the pictures of wearing masks and no masks. In general, a total of more than 2000 masks have been collected, including more than 1000 masks worn and unworn respectively. The original data sets have been cleaned, classified, and stored in two categories respectively, and the pictures have been renamed with serial numbers.The dataset used is shown below.

![image](https://user-images.githubusercontent.com/72681393/109654824-9da74880-7b9d-11eb-978e-268413a3e475.png)

![image](https://user-images.githubusercontent.com/72681393/109654835-a435c000-7b9d-11eb-96ec-9f1e51f91cda.png)

The model receives grayscale images with a size of 96*96 as input, so it is necessary to preprocess the images of the data set.
The Edge Impulse platform is convenient for batch processing of images. Before that, the code for image processing in the Colab Notebook is shown below, which can scale and gray scale images in batches.

![image](https://user-images.githubusercontent.com/72681393/115412134-a70c7300-a226-11eb-94b5-89dff2b8b7b2.png)


*probably ~200 words and images of what the data 'looks like' are good!*

## Model
Considering that the essence of mask recognition is image binary classification of image recognition. Therefore, the convolutional neural network CNN model, which is commonly used in image recognition, was selected in this project. And the cat and dog fight case was taken as a reference. 

The CNN model architecture used is shown below, including two maxpooling layers and two convolution layers, one Flatten layer, and two Dense layer. The last Dense layer outputs the probabilities of whether wearing a mask with Softmax as the activation function.

![image](https://user-images.githubusercontent.com/72681393/115414536-b2f93480-a228-11eb-9a9b-9242f625a731.png)

ReLU activation function is adopted in the convolutional layer to reduce the amount of calculation. Compared with Sigmoid's exponential calculation, the convolutional layer is much simpler and there is no saturation problem.

![image](https://user-images.githubusercontent.com/72681393/115415735-bc36d100-a229-11eb-822c-de7c9672d2d6.png)

Softmax is adopted as he activation function of the last layer, the Dense layer.Sigmoid is an exponential function whose output is between 0 and 1, and it is suitable for useing in binary classification problems and represents the output result with probability. More importantly, Softmax is not only applicable to binary classification problems, but also to multiple classification problems. It can output all kinds of probabilities respectively, which is convenient for subsequent expansion of classification.



This is a Deep Learning project! What model architecture did you use? Did you try different ones? Why did you choose the ones you did?

*probably ~200 words and a diagram is usually good to describe your model!*

At present, the experiment realizes the data set uploading, data set cleaning, and the data set is divided into training set and test set according to the ratio of 0.8:0.2

## Experiments
The selection of model architecture is mainly based on two cases: cat fighting and dog fighting and Magic_Wand.In the early stage of model training and debugging, due to the small number of data sets, although the training accuracy rate is very high, the test accuracy rate is low, unable to correctly reflect the relationship between the model parameter changes and the change of accuracy rate. After the increase to 2000 pictures, a relatively large improvement has been made.

The model architecture and operation results of Edge Impulse platform are shown below. The learning rate and the number of training rounds are set as 0.0005 and 50 respectively. The grayscale images of 96*96 size are used as input to output the probability of wearing masks and not wearing masks respectively.

![image](https://user-images.githubusercontent.com/72681393/115416878-b988ab80-a22a-11eb-9c94-104ae3f34e7c.png)

As can be seen from the picture, the probability of correctly identifying the two categories in the confusion matrix display is about 80%, which is not accurate enough. However, due to the limitations of the model size, further optimization parameters are limited to improve the accuracy.The model architecture can be further optimized and further optimized by data set expansion to improve the accuracy.

Before using Edge Impulse platform to further optimize the model, the author mainly uses Colab Notebook to build the code for model training. The model parameters and training results are shown below.

![image](https://user-images.githubusercontent.com/72681393/115417291-15ebcb00-a22b-11eb-9903-c6458cc09b37.png)
![image](https://user-images.githubusercontent.com/72681393/115417356-20a66000-a22b-11eb-809a-bff61aef5c23.png)


What experiments did you run to test your project? What parameters did you change? How did you measure performance? Did you write any scripts to evaluate performance? Did you use any tools to evaluate performance? Do you have graphs of results? 

*probably ~300 words and graphs and tables are usually good to convey your results!*

## Results and Observations
Synthesis the main results and observations you made from building the project. Did it work perfectly? Why not? What worked and what didn't? Why? What would you do next if you had more time?  

*probably ~300 words and remember images and diagrams bring results to life!*

## Bibliography
*If you added any references then add them in here using this format:*

1. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

2. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

----

## Declaration of Authorship

I, AUTHORS NAME HERE, confirm that the work presented in this assessment is my own. Where information has been derived from other sources, I confirm that this has been indicated in the work.


*Digitally Sign by typing your name here*

ASSESSMENT DATE
