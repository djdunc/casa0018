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



*probably ~200 words and a diagram is usually good to convey your design!*

## Data
Data sets of mask recognition cases from several GitHub and some pictures of me and my family have been used to get the pictures of wearing masks and no masks. In general, a total of more than 2000 masks have been collected, including more than 1000 masks worn and unworn respectively. The original data sets have been cleaned, sorted, and stored in two categories respectively, and the pictures have been renamed with serial numbers.The dataset used is shown in the figure show below.

![image](https://user-images.githubusercontent.com/72681393/109654824-9da74880-7b9d-11eb-978e-268413a3e475.png)

![image](https://user-images.githubusercontent.com/72681393/109654835-a435c000-7b9d-11eb-96ec-9f1e51f91cda.png)


*probably ~200 words and images of what the data 'looks like' are good!*

## Model
In combination with what I have learned from books and classes, I analyze that the essence of mask recognition is binary classification of image recognition. Therefore, I select CNN model, a convolutional neural network commonly(CNN) used in image recognition in this project, and take the model code of the case of cat and dog fight as a reference. 

This is a Deep Learning project! What model architecture did you use? Did you try different ones? Why did you choose the ones you did?

*probably ~200 words and a diagram is usually good to describe your model!*

At present, the experiment realizes the data set uploading, data set cleaning, and the data set is divided into training set and test set according to the ratio of 0.8:0.2

## Experiments
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
