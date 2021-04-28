# IS THIS MY DOG? 
## How to create a dog face recognition tool with Edge Impulse

Simone Rossi

## Introduction
Reported dog thefts have increased over the last few years with only 17% of animals re-united with their families (Direct Line Group, 2019); situation has got worse since the beginning of the pandemic due a growth in demand for pets (Al Jazeera, 2021). Considering the rate at which dogs are found, the strategy of flier posting and of appeals on social media adopted by dog owners is ineffective. 

![image](https://user-images.githubusercontent.com/43931397/116381616-fb0ded80-a80c-11eb-8a34-9682e7a2c3be.png)

*Reported dog thefts in Endgland, Wales and Northern Ireland - source BBC News*

This project aims at using deep learning to identify dog faces from their pictures to help increasing the rate of found dogs. While there have been considerable advancements on the use of machine learning to recognise human faces, most projects aimed at the fauna have been focused on breed identification and on counting animals; nonetheless some studies on how to use machine learning for pet face recognition were published over the last five years. Inspiration for the proposed tool was taken from similar projects based on convolutional neural networks developed in 2016 (Moreira et al, 2016) and in 2019 (Mougeout et al, 2019), with more attention paid to the latter, which showed better accuracy. A project of the same scale as these two would be out of the scope of this module, therefore the aim is using Edge Impulse to create a simplified version of Mougeot’s tool.

## Research Question
Considering an increase in reported stolen dogs with a small fraction being retrieve, the project aims at improving on previous deep learning models for dog facial recognition; this might help owners and authorities in their efforts of finding lost or stolen dogs.
There are already some examples of similar deep learning tools, the scope of this project is creating a simpler and lighter version for mobile devices using Edge Impulse.

## Application Overview
The project adopts the principles of transfer learning and it entails building a deep convolutional neural network model for face recognition; the model is meant to be deployed on a portable device which may capture images through a built-in camera and extract biometric features from them before running the model. Once launched the model shall confirm whether the subjects of the pictures match any image from the dataset; a short text message should appear on the device display confirming if the dog is found on records. 
The tool was initially meant to be deployed on Arduino fitted with an Arducam, making it a prototype for a pocket device; limitations were considered and this solution was discarded:
The resolution of the Arducam is inadequate for the scope of the project.
The output would be in the form of colour coded lights, without the ability to assign a name to the pet matching found in the database.
Edge Impulse was chosen as the platform to develop the tool which allow an easy deployment on the mobile phone I have access to; this is fitted with a camera with higher resolution than the Arducam and provide access to the toll to a wider audience.

![image](https://user-images.githubusercontent.com/43931397/116381860-327c9a00-a80d-11eb-9b00-8b94f2ddd313.png)

## Data
Images were initially acquired from PetFinder.my and from Guillaume Mougeot’s Github repository (2019). Pictures of my two dogs were add for the experimental phase. 
Face identification relies on biometric data of dogs, i.e. eyes and muzzle (Mougeot et, 2019) hence images where these facial features were not easily identifiable because of the presence of objects in front of the pet were discarded. This is likely to exclude dogs from breeds which features include long facial air; nonetheless this could be an acceptable compromise for a first step into building a reliable face recognition tool which may be refined and improved to ensure all breeds are incorporated at a later stage. 
To improve the accuracy of the model in detecting the main biometric data, images have to be cropped and rotated to keep the three key features within the same sections of the pictures across the dataset. This activity was initially recommended by Kumar and Singh (2018) and later adopted by Mougeot (2019) with satisfactory results. Since pre-processing should be carried out by hand on a large quantity of images, those from the Github repository were used for training and testing with the added value that this database also contains several images of the same dog unlike others, which should facilitate the learning process.

Data is stored in this folder under the Github repository
https://github.com/SimoneUCL/casa0018/tree/main/Assessment/Projects/Final%20Project/Database

## Model
The proposed architecture is based on convolutional neural networks as developed by He et al (2016) and as improved by Mougeot et al (2019) with the addition of dropout layers. The challenge of this project consists in simplifying the model while keeping accuracy as high as possible. 
Solutions based on Neural Network and Transfer Learning blocks in Edge Impulse were considered when developing the model. Although the platform recommends the use of Neural Network for categorizing movement or recognizing audio, this block seemed the preferred as its GUI allows more flexibility in terms of the number of layers and neurons and it offer the possibility of adding as many dropout layers as necessary to minimise overfitting. After a few attempts when the model overfitted and produced unsatisfactory results from the point of view of accuracy and loss, the focus was shifted on the Transfer Learning block with v2 0.35 appearing to be the one with the most acceptable results. The architecture of this model is much simpler than the target model (Mougeout et al, 2019) which contains model contains 92 layers for a total of 5.8 million of parameters, on the other hand the model was overfitting for which it is generally advised to remove layers and reduce the number of neurons.

![image](https://user-images.githubusercontent.com/43931397/116381548-e893b400-a80c-11eb-93f6-a139c9762409.png) 

## Experiments
The initial image acquisition entailed 315 images from DogFaceNet repository pre-processed to ensure the three biometric parameters were in the required part of the pictures (Mougeout et al, 2019); 251 of these images were used for training and 64 images for testing. Their size was 224 x224 as per the literature review (He et al, 2016) and they were squashed to ensure the pre-set alignment of biometrics would be kept. Parameters were changed to grayscale to reduce the size of the model. 

Experiments with both Neural Network and Transfer Learning were undertaken with 100 epochs, 0.01 learning rate and 0.75 a minimum confidence rate; models overfitted with first signs appearing within the first two dozen epochs. The NN model gave no accuracy and 4.43 loss, while the TL one had 26.5% accuracy and 9.58 loss.

![image](https://user-images.githubusercontent.com/43931397/116387871-2a275d80-a813-11eb-9814-9906700a9842.png)

*Output of the initial model based on Neural Network* 

![image](https://user-images.githubusercontent.com/43931397/116387894-30b5d500-a813-11eb-8651-7d88eff06029.png)

*Output of the initial model based on Transfer Learning*

More experiments were carried out to reduce overfitting and improve performance. The sample was gradually increased up to a total of 602 pictures, the learning rate was progressively reduced to 0.0002; dropout layers were also added to the NN model to minimise overfitting. There were improvements from the point of view of validation accuracy and loss, nonetheless the models kept overfitting it took longer for overfitting to appear and the gap between testing and validation was smaller. Epochs were reduced to 50 as after this point accuracy and loss plateaued; this was also required to prevent the model from exiting the loop before producing results.

![image](https://user-images.githubusercontent.com/43931397/116390306-ce120880-a815-11eb-8080-bd297be6c61c.png)

*Output of the Neural Network model with more dropout layers and run on 602 files*

The final model was based on Transfer Learning model with 50 epochs, 0.002 learning rate, data augmentation and 0.75 confidence rating. Its accuracy was 45.8% and its loss 8.70, which were among the best achieved during experimentation. The model was deployed on an iPhone 7 Plus; the camera was aimed at two real life dogs as well as at some pictures of dogs from the databased used during training; none of the images were associated to the correct label.

![image](https://user-images.githubusercontent.com/43931397/116407898-23581500-a82a-11eb-9be3-181c9de63397.png)

*Training performance of the most recent experiment with TL*

![image](https://user-images.githubusercontent.com/43931397/116408067-4f739600-a82a-11eb-85c3-14176fdc86e9.png)

*On device performance of the most recent experiment with TL*

![image](https://user-images.githubusercontent.com/43931397/116408535-d1fc5580-a82a-11eb-9e16-75d210a59730.png)

*Validation accuracy and confusion martrix of the most recent experiment with TL*

Images and results from classifications are stored at the following link:

https://github.com/SimoneUCL/casa0018/tree/main/Assessment/Projects/Final%20Project/Dog%20Face%20Classification

## Results and Observations
Considering the complexity of face recognition models (Mougeot et al, 2019; Moreira et al, 2016), Edge Impulse seems inappropriate unless custom blocks are heavily introduced. Transfer Learning doesn’t allow much flexibility in terms of model architecture, Neural Network enables the addition and removal of layers as well as changes to the quantity of neurons and of layers; nonetheless the latter is best suited for movement and audio recognition as the poor results from its application to face recognition seems to confirm.

The resolution of the GUI seems unsuitable for a model with tens of labels: the confusion matrix and the classification results on device are extremely difficult to read and understand.

![image](https://user-images.githubusercontent.com/43931397/116387422-b5542380-a812-11eb-96d3-d89fa8d682cf.png)

*Typical Confusion Matrix*

Attempts at introducing custom blocks were made to improve image pre-processing and to get better overall results, but they failed as the machine’s firewall prevented the completion of part of the required steps. When more layers were added to match the architecture of Mougeot’s tool, training stopped before producing results. However, a model heavily relying on imported blocks would reduce the peculiarity of Edge Impulse as a simpler platform and the purpose of building a simple tool.

Apparently, more accurate validation results were achieved with images portraying puppies or dogs with features generally associated to puppy (see table below): little facial hair and large eyes compared to the size of the head. Contrast between the eye and their background colour seems to bear an impact too. Classification entailed running the model more than once for each subject; results were not consistent since some dog was recognised all times, some other was recognised with low confidence level or just two out of four times and some other was not recognised at all.

![image](https://user-images.githubusercontent.com/43931397/116387328-9eadcc80-a812-11eb-9aec-5f843ced0fad.png)
![image](https://user-images.githubusercontent.com/43931397/116387677-f0565700-a812-11eb-8bea-9dc8fa73d1ee.png)
![image](https://user-images.githubusercontent.com/43931397/116391697-665cbd00-a817-11eb-9c06-4f5a60255671.png)

*Model testing results,for dogs which face was successfully recognised*

Next steps may include adding bespoke blocks to automate and improve pre-processing; as to training, better understanding of Edge Impulse might help turning TL into a more flexible and effective block.

A public version of the latest version of the project is available at the following link:
https://studio.edgeimpulse.com/public/28887/latest

The folder on the Github repository contains some of the data exported during the experiments:
https://github.com/SimoneUCL/casa0018/tree/main/Assessment/Projects/Final%20Project

## External data

A public version of the latest version of the project is available at the following link:
https://studio.edgeimpulse.com/public/28887/latest

This folder on the Github repository contains some of the data exported during the experiments:
https://github.com/SimoneUCL/casa0018/tree/main/Assessment/Projects/Final%20Project

## Bibliography
Dog theft on the increase: five pups stolen every day.(2019). Direct Line Group. viewed 7 March 2021. https://www.directlinegroup.co.uk/en/news/brand-news/2019/090519.html 

He, K. Zhang, X. Ren, S. Sun, J. (2016). Deep Residual Learning for Image Recognition. in 2016 IEEE Conference on Computer Vision and Pattern Recognition (CVPR). Las Vegas: IEEE, pp. 770–778. doi: 10.1109/CVPR.2016.90.

Kumar, S. Singh, S. K. (2018).  Monitoring of pet animal in smart cities using animal biometrics. Future Generation Computer Systems 83. pp553–563. doi: 10.1016/j.future.2016.12.006.

Moreira, T. P. Lisboa Perez, M. de Oliveira Werneck, R. Valle, E. (2016). Where Is My Puppy? Retrieving Lost Dogs by Facial Features. Available at: http://arxiv.org/abs/1510.02781

Mougeot, G. Li, D. Jia, S. (2019). A Deep Learning Approach for Dog Face Verification and Recognition’. in Nayak, A. C. Sharma, A. (eds). PRICAI 2019: Trends in Artificial Intelligence. Cham: Springer International Publishing (Lecture Notes in Computer Science). pp418–430. doi: 10.1007/978-3-030-29894-4_34.

UK dog theft on the rise amid pandemic pet demand. (2021). Al Jazeera. viewed 7 March 2021.viewed 7 March 2021. https://www.aljazeera.com/news/2021/2/5/uk-dog-theft-on-the-rise-amid-pandemic-pet-demand

Trigueros, D. S. Meng, L. Hartnett, M. (2018). Face Recognition: From Traditional to Deep Learning Methods., arXiv:1811.00116 [cs]. Available at: http://arxiv.org/abs/1811.00116 

## Declaration of Authorship

I, Simone Rossi, confirm that the work presented in this assessment is my own. Where information has been derived from other sources, I confirm that this has been indicated in the work.

*Simone Rossi*

London, 29th April 2021
