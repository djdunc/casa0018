Lab activity for this week entails changing the model provided during the lecture to increase the pace of LED flickering and swapping the fuction in the model.

The original model applied the sine function to 1000 values in  the  0 - 2π range. The training and validation losses were in the range of 15% before re-training the model. once the model was changed to increase the frequency of the curve the losses raised thre fold. The same happened when keeping the function as per the original model while making the range of data bigger.

#### **COSINE MODEL**

On the other hand by switching the function to cosine the loss for both training and the validation drop to close to zero (1.2%); unlike the model with sine as the function to generate data, the loss drops in two statges, with a plateau around 55% between 10 and 100 epochs and a sharper drop following the 100th epoch.

![alt text](https://github.com/SimoneUCL/casa0018/blob/main/Week3/myWeek3/Cos_loss.png)

