# CASA0018: Deep Learning for Sensor Networks
CASA0018 Deep Learning for Sensor Networks course material

## Summary

Our environment is increasingly being connected with small computers that are aware and responsive. This introductory, hands on module will introduce students to machine learning applied to low power embedded devices. Students will learn the main concepts of deep learning, understand how to apply deep learning to data streams from cameras and other IoT sensors, and how to deploy AI onto sensor devices, such as mobile phones and microcontrollers. Students will learn about deep learning architectures for image and time series data and will apply these ideas to sensor data in order to do forecasting, image recognition, and object tracking.  A significant component of the module will be an individual project to build and deploy an intelligent sensor application. Students will practice these ideas using Python, PyTorch and TensorFlow. The programme has been developed with support from the Google TensorFlow team, uses the TinyML book as a core text and utilises the Arduino Nano as the primary prototyping platform.


## Learning Objectives

On completion, students will be able to:

Domain Knowledge
 - Understand AI / machine learning terminology
 - Understand deep learning opportunities and limitations
 - Understand different types of deep learning models

Prototyping Skills
 - Implement deep learning models in Python
 - Prepare data for model training
 - Select and train suitable models for different use cases (video & timeseries)
 - Embed AI on sensor devices, such as a mobile phone or a microcontroller.

Collaboration
 - Document and share project information to support reproducible research
 - Provide peer feedback to fellow students on project work
 - Present design decisions and prototypes to receive critical feedback


## Module Delivery

The ten week module is roughly split into 2 parts. The first half focuses on introducing the technical skills required to apply Deep Learning on embedded devices. Each lecture will be followed by a hands on, self paced lab session to build a working example of the material taught in the lecture.

The second half continues with lectures but is focused on building a student project. At mid term a project brief will be introduced and this will form the basis for the remaining lab sessions. Weeks 5-10 will include peer feedback via design crits (presentations of work in progress) and some guest lectures covering case studies from field applications.

The course references a large volume of freely available on-line learning material to support specific Machine Learning topics. An extra 5-7 hours per week of self-guided learning is recommended during the term (on top of three hours for the weekly lecture and lab session), with a subsequent 70 hours devoted to project work in the second half of term culminating in a final design presentation in week 10.

## Topics covered

  1. Intro to DL4SN - a lecture on the key concepts of Machine Learning with examples from computer vision and timeseries data. Two examples will be used to demonstrate the basic workflow and toolchain required to build and deploy an application written in Python using TensorFlow with Google Colab / Jupyter Notebook environment. The lecture will be followed by a lab session where you will set-up your lab environment using Google Colab and build a "Hello World" example application.

  2. CNN's and CV - an introduction to Convolution Neural Networks and Computer Vision using TensorFlow. Using examples from the TensorFlow learning materials basic concepts such as activations, loss functions and optimiser functions will be covered to develop an understanding how to create an image classification application. Example code walk throughs using MNIST dataset will also cover convolutions, pooling and performance measures such as a confusion matrix. In the lab session you will build an application to classify images passed into the application.

  3. Embedded AI - an introduction to deep learning on embedded devices. We will discuss why machine learning is important for the Internet of Things and why it is different to "normal" machine learning. An example workflow to design and deploy a model will be used to introduce the Arduino hardware being used in the module. In the lab session you will build a simple ML application to control an LED and deploy it onto an Arduino.

  4. TinyML - a guest lecture with Pete Warden (Google) will cover motivations for embedded AI, applications that led to the development of TinyML and wake word detection as a ubiquitous example of how little bits if intelligence are influencing our connected environment. We will also dig a little deeper into quantization, flattening and how to port a TensorFlow model to TensorFlow Lite.

  5. CV on RPi - building on earlier CV models in this lecture we will explore applications of computer vision on the Raspberry Pi. Returning to CNN's and introducing YOLO we will walk through image classification and object detection examples. We will also introduce the design brief for the project work required in the second half of this module. In the lab session you will build an object detector using a webcam or a mobile phone with camera.

  6. Timeseries data -  the problems associated with traditional time series forecasting models (such as ARIMA) are introduced and then deep learning methods such as RNN and LSTM are applied to time series data and their advantages over traditional forecasting models are discussed.

  7. Model Training - returning to Arduino and TinyML, in this lecture we will explore how sensor data such as the movement measured by accelerometers can be characterised into different classes. Using the TinyML magic wand example we will work through how to process sensor data followed by an example of how to train your own model data. In the lab session you can either work through the magic wand example or focus on your own project build.

  8. The bigger picture - in this guest lecture Kira Kempinski (EY) will give a high level view of many of the machine learning techniques not covered in this course to highlight the breadth of ongoing research and to introduce examples from her own experiences of deploying machine learning in industry. In the lab session tutors will be available to support your project build.

  9. The bat detector - in this guest lecture Oisin Mac Aodha (Edinburgh Uni) will talk about his experience of developing the Bat Detector - a deep learning tool for bat acoustic signal detection. He will describe the design choices made whilst developing the project, how the model was tested and lessons learnt in the journey from idea to field installation. In the lab session tutors will be available to support your project build.

  10. Final Crit - in the final week we will host a showcase of the projects built. Each student will get 5 minutes to present their project with 5 minutes of peer and tutor feedback.

## Outputs

- Skills development - during the first 5 weeks each lecture will be followed by a lab session with follow along technical exercises. These tutorials will help you develop the skills needed to work on your own project in the final 5 weeks.

- Project crits - in the second half of the module students will work on an individual project. Work in progress will be presented at 3 way points with the final presentation on the last week of the module. At the crits students will also learn how to give peer feedback to their fellow students.

- Project documentation - in weeks 5-10 students will update their project website on a weekly basis to document their design process, inspiration, experiments, code and product photos / videos.

## Classes

Term 2

Week 1 - 12th Jan, Tuesday 10am - 1pm
Week 2 - 19th Jan, Tuesday 10am - 1pm
Week 3 - 26th Jan, Tuesday 10am - 1pm
Week 4 - 2nd Feb, **Guest Lecture** Tuesday 5pm
Week 5 - 9th Feb, Tuesday 10am - 1pm
Reading Week
Week 6 - 23rd Feb, Tuesday 10am - 1pm
Week 7 - 2nd Mar, Tuesday 10am - 1pm
Week 8 - 9th Mar, **Guest Lecture**
Week 9 - 16th Mar, **Guest Lecture**
Week 10 - 23rd Mar, **Project Presentations** Tuesday 10am - 1pm

[all times UK]

## Tutor

Course tutors of this 15 credit module include:
- Duncan Wilson (lead)  - d.j.wilson@ucl.ac.uk
- Martin de Jode - m.dejode@ucl.ac.uk


## Software

The course will make heavy use of the following software packages

  - **Arduino** <br/>
	xxxxxx.

  - **TensorFlow**<br/>
	xxxxxxx.

## Reading List

There is a course reading list under the ReadingLists@UCL facilty which can be accessed here: (https://ucl.rl.talis.com/modules/casa0018.html)

The core text for the module is [TinyML](https://tinymlbook.com/) by Pete Warden and Daniel Situnayake  

We also reference
- [Deep Learning](https://www.deeplearningbook.org/) by Ian Goodfellow and Yoshua Bengio and Aaron Courville
- [Hands-On Machine Learning with Scikit-Learn, Keras, and TensorFlow](https://www.oreilly.com/library/view/hands-on-machine-learning/9781492032632/) by Aurélien Géron


## Assessment

(2500 word equiv)
- project build (30%),
- github page - code / docs / photos / video (30%),
- crit (40%)


