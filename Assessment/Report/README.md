# Mask detect on Arduino Nano 33 BLE

ChenYifan

## Introduction
As the COVID-19 epidemic gets worse, more and more people are aware of the importance of wearing masks outside. While existing vaccines, go out with mask is still necessary, but not all the people wear masks, therefore the aim of this project is to realize mask wearing recognition on Arduino Nano 33 BLE. The project goal is on the Arduino platform achieved the identification of whether wearing masks and make a mask recognition machine and be able to use it anytime and anywhere by cameras. This project first wrote code in Colab Notebook for model training, and then adopted Edge Impulse platform for model training. 

## Research Question
How to build and train a Convolutional Neural Network (CNN) image recognition classification model to realize mask recognition based on Arduino 33 BLE platform and Arducam.

## Application Overview
The overall structure of the project is shown below. The Saved Model is taken as the boundary to divide the project work into two parts: Model training and Model running.

![image](https://user-images.githubusercontent.com/72681393/115410196-036e9300-a225-11eb-913a-ed01c347db38.png)

The model training was carried out on the Google platform and Edge Impulse platform. The required data sets were collected according to the analysis of the project objectives, and the appropriate neural network architecture was selected for model training and model transformation.The model is implemented at the Arduino end. The Arducam module is responsible for sensing the outside world and sending images to the Arduino Nano 33 BLE Sense as the model input. The input data is recognized in real time and the output results are obtained.The Arduino program frame is shown below.

![image](https://user-images.githubusercontent.com/72681393/115411200-db336400-a225-11eb-8325-4f346ade0284.png)

Arduino can recognize whether people are wearing masks in real time according to the images sent back by the camera, and output the results through the serial port. At the same time, the color of the on-board RGB light can be changed according to the results.



## Data
Data sets of mask recognition cases from several GitHub and some pictures of me and my family have been used to get the pictures of wearing masks and no masks. In general, a total of more than 2000 masks have been collected, including more than 1000 masks worn and unworn respectively. The original data sets have been cleaned, classified, and stored in two categories respectively, and the pictures have been renamed with serial numbers. The dataset used is shown below.

![image](https://user-images.githubusercontent.com/72681393/109654824-9da74880-7b9d-11eb-978e-268413a3e475.png)

![image](https://user-images.githubusercontent.com/72681393/109654835-a435c000-7b9d-11eb-96ec-9f1e51f91cda.png)

The model receives grayscale images with a size of 96*96 as input, so it is necessary to preprocess the images of the data set.
The Edge Impulse platform is convenient for batch processing of images. Before that, the code for image processing in the Colab Notebook is shown below, which can scale and gray scale images in batches.

![image](https://user-images.githubusercontent.com/72681393/115412134-a70c7300-a226-11eb-94b5-89dff2b8b7b2.png)


*probably ~200 words and images of what the data 'looks like' are good!*

## Model
Considering that the essence of mask recognition is image binary classification of image recognition. Therefore, the convolutional neural network CNN model, which is commonly used in image recognition was selected in this project. And the cat and dog fight case were taken as a reference.
The CNN model architecture used is shown below, including two maxpooling layers and two convolution layers, one Flatten layer, and two Dense layer. The last Dense layer outputs the probabilities of whether wearing a mask with Softmax as the activation function.


![image](https://user-images.githubusercontent.com/72681393/115414536-b2f93480-a228-11eb-9a9b-9242f625a731.png)

ReLU activation function is adopted in the convolutional layer to reduce the amount of calculation. Compared with Sigmoid's exponential calculation, the convolutional layer is much simpler and there is no saturation problem.

![image](https://user-images.githubusercontent.com/72681393/115415735-bc36d100-a229-11eb-822c-de7c9672d2d6.png)

SoftMax is adopted as the activation function of the last layer, the Dense layer. Sigmoid is an exponential function whose output is between 0 and 1, and it is suitable for using in binary classification problems and represents the output result with probability. More importantly, SoftMax is not only applicable to binary classification problems, but also to multiple classification problems. It can output all kinds of probabilities respectively, which is convenient for subsequent expansion of classification.

## Experiments
The selection of model architecture is mainly based on two cases: cat fighting and dog fighting and Magic_Wand.The model architecture and operation results of Edge Impulse platform are shown below. The learning rate and the number of training rounds are set as 0.0005 and 35 respectively. The grayscale images of 96*96 size are used as input to output the probability of wearing masks and not wearing masks respectively.

![image](https://user-images.githubusercontent.com/72681393/115416878-b988ab80-a22a-11eb-9c94-104ae3f34e7c.png)

It can be seen that the accuracy of model training is higher than the validation rate, so the author added the Dropout layer in the subsequent improvement to reduce the possibility of model overfitting to a certain extent.
Finally, the training results after adjusting the model parameters are shown in the figure. It can be known from the confusion matrix that the accuracy of the model is about 80%. This is due to the limited memory of Arduino, which inevitably gives up part of the model performance and reduces the model size.
The online test results of the model are shown in the figure, and the accuracy can be seen…..


## Results and Observations
The operation of the Arduino terminal is shown in the figure1. The figure2 shows the mask identification output and the identification output without wearing the mask. It can be seen that the program can be successfully identified.
Behind this result several questions that have been solved one by one:
1.Model dimension. Arduino operation model requires input grayscale image with the size of 96*96, and the input and output data type of the model must be INT8, otherwise the operation fails. For this reason, the author wrote a script as shown in the figure to verify whether the relevant parameters of the quantized model are consistent.
 
 ![image](https://user-images.githubusercontent.com/72681393/115588543-73524b80-a301-11eb-8561-96d9f3cabbc0.png)


2.Micro_op_resolver.Simply copying the transformed array directly into the Arduino program will not run successfully because the micro_op_resolver required by the model is not loaded.Referred to the model training of Magic_Wand in the official example of TensorFlow and the Arduino program, the corresponding relationship of this part can be found. After correction, it is successfully solved, as shown in the figure.
 
 ![image](https://user-images.githubusercontent.com/72681393/115588573-7b11f000-a301-11eb-87ac-2eace02692d7.png)


3.Memory issues. The memory here refers to two parts. The first part is the memory required by the model array, and the second part is the memory required by the model operation. The experimental results show that the model array length is not more than 80W and the model running memory KtensorArenaSize is not more than 180*1024.only If these two conditions are satisfied，it can meet the needs of the normal operation of this project.

## Limittion
For the future improvement if time permits. This project would try to solve these two limitation. 
1. Multi-classification problem: the third kind of Unknown data set would added on the basis of the current data set, which mainly includes some images of daily life without people.
2. Add buttons and buzzer components. Users can take photos and identify them by pressing a button, and a buzzer will remind them to wear a mask.


## Bibliography
*If you added any references then add them in here using this format:*

1. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

2. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

----

## Declaration of Authorship

I, ChenYifan, confirm that the work presented in this assessment is my own. Where information has been derived from other sources, I confirm that this has been indicated in the work.


![image](https://user-images.githubusercontent.com/72681393/115589022-f5427480-a301-11eb-82f9-8921e13cc0ea.png)

2021/4/22
