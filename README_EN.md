# dlib facial recognition model trained for Asians    

![s-TaguchiModelsWithDlib](https://github.com/TaguchiModels/dlibModels/assets/167880914/9aaf0909-b092-42a8-99a4-56c138455bc4)

## High-quality facial recognition using deep metric learning  
dlib has an excellent facial recognition model. However, unfortunately, it is racially biased, and it is no exaggeration to say that it is completely useless when it comes to Northeast Asians, especially Japanese people. However, I think it can't be helped. This is because the face recognition dataset used for training was biased.  

So I collected a lot of datasets, mainly Japanese, and trained from scratch. This took a tremendous amount of time, but I think we have reached a standard that can withstand practical use to some extent. Even though it was trained for Japanese people, the results are similar to the dlib model when it comes to facial recognition for Westerners. Photos of Hollywood action heroes provided in the dlib example can also be classified in the same way as dlib.  

The image at the beginning is a classification of Japanese actors using my model.  
The image below is the classification result when using the dlib "dlib_face_recognition_resnet_model_v1.dat" model.  

![dlib_japannese_bald_actor](https://github.com/TaguchiModels/dlibModels/assets/167880914/29b2776c-8e9b-47e9-aeec-778f4ba8009e)

## Accuracy comparison with dlib with LFW dataset  
I tested the accuracy with LFW Deterset to present some objectivity.  
First, I tested with the dlib model "dlib_face_recognition_resnet_model_v1.dat".  
The result was 0.993833%.  

```
dlib original version
C:\Users\Taguchi\Desktop\dlib_face_recognition_resnet_model_v1_lfw_test\build>main
dist thresh: 0.6
margin: 0.04
overall lfw accuracy: 0.993833
pos lfw accuracy: 0.994667
neg lfw accuracy: 0.993
fold mean: 0.995
fold mean: 0.991667
fold mean: 0.991667
fold mean: 0.99
fold mean: 0.996667
fold mean: 0.996667
fold mean: 0.99
fold mean: 0.995
fold mean: 0.996667
fold mean: 0.995
rscv.mean(): 0.993833
rscv.stddev(): 0.00272732
ERR accuracy: 0.993
ERR thresh: 0.595778
```

I then tested it with my model "taguchi_face_recognition_resnet_model_v1.dat".  
The result was 0.9895%.  

```
Taguchi model version
C:\Users\Taguchi\dlib_face_recognition_resnet_model_v1_lfw_test\build>main
dist thresh: 0.6
margin: 0.04
overall lfw accuracy: 0.9895
pos lfw accuracy: 0.984
neg lfw accuracy: 0.995
fold mean: 0.986667
fold mean: 0.99
fold mean: 0.986667
fold mean: 0.99
fold mean: 0.988333
fold mean: 0.993333
fold mean: 0.981667
fold mean: 0.993333
fold mean: 0.991667
fold mean: 0.993333
rscv.mean(): 0.9895
rscv.stddev(): 0.00377205
ERR accuracy: 0.989
ERR thresh: 0.614296
```

As you can see, dlib and my model have a 0.004333% better accuracy than dlib.  
This difference in accuracy can be said to be within the margin of error.  
In fact, it's good news for those looking to get their hands on Northeast Asian facial recognition for free.  

## Training with 6.5 million face dataset  
In total, I used over 6.5 million faces from over 16,000 people to train my facial recognition model.  
Approximately 47% of this is facial data of Japanese people (including some Asian people other than Japanese).  
This training dataset consists of several publicly available datasets, as well as some collected from the internet.  
The biggest challenge was that some of the datasets contained duplicate people.  
It took a lot of time to remove this duplicate person.  

## Obtaining a facial recognition model  
Please obtain the dlib models 'dlib_face_recognition_resnet_model_v1.dat' and 'shape_predictor_5_face_landmarks.dat' from the link below.  
 `※ It has a '.bz2' extension, so please unzip it after downloading.`  

[dlib.net/files](http://dlib.net/files/)

Please download and unzip my model 'taguchi_face_recognition_resnet_model_v1.dat' from the link below.  

[Taguchi's face recognition model](https://drive.google.com/file/d/1uMAZbPHiKOl6sjDgAoORn8g5U4wHQisW/view?usp=sharing)

## How to compile  
Please refer to dlib.net, which describes how to compile it.  
[How to compile dlib](http://dlib.net/compile.html)

## Execution method  
Place the following in the same folder as the exe file created after compilation.  
 * Place the faces folder and place JapaneseBaldActor.jpg and bald_guys.jpg under it.  
 * Place 'dlib_face_recognition_resnet_model_v1.dat'.  
 * Place 'shape_predictor_5_face_landmarks.dat'.  
 * Place 'taguchi_face_recognition_resnet_model_v1.dat'.  

Please type the following command from the command prompt.  
 * Example of Taguchi's model  
    ```
    > dnn_face_recognition_ex faces/JapaneseBaldActor.jpg taguchi_face_recognition_resnet_model_v1.dat
    ```  
 * Example of dlib model
    ```
    > dnn_face_recognition_ex faces/JapaneseBaldActor.jpg dlib_face_recognition_resnet_model_v1.dat  
    ```
    
## Limitations  
My model lacks training data, so its accuracy may be significantly worse.  
 * A person with African roots.  
 * Persons under 18 years of age.  
 * A person wearing a mask.  

It may not be suitable for the above applications.  
Please use with caution.  

---

# dlib's gender determination model trained for Asia  

![Gender_males](https://github.com/TaguchiModels/dlibModels/assets/167880914/9db5205e-e5c9-4828-b4fd-5591d874a3c2)

## dlib's gender determination model also incorrectly identifies Japanese people.  
dlib has an excellent gender determination model. Unfortunately, however, this is also racially biased, and it is no exaggeration to say that it is completely useless when it comes to Northeast Asians, especially Japanese people. The reason is that the face recognition dataset used for training was biased, as before.  

So I collected a lot of datasets, mainly Japanese, and trained them from scratch. Even though it was trained for Japanese people, the results are comparable to the dlib model when it comes to gender determination for Westerners. However, dlib's gender determination model "dnn_gender_classifier_v1.dat" is a very lightweight model. My model is a heavy model that was trained by modifying the source code of dlib's "resnet34_1000_imagenet_classifier.dnn" to determine gender.  
The heaviest part is the beginning of loading the model and desesializing it, and the gender determination process does not take much time.  
Still, if your scope of use is limited to Westerners, it is better to use the dlib model.  

Please refer to github/dlib 'dnn_gender_classifier_v1_ex.cpp' for the source code of dlib's gender determination model, and see there directly for instructions on how to use it.  
[github dlib](https://github.com/davisking/dlib/examples)

## Training with a dataset of 500,000 faces  
In total, I used over 500,000 facial image files to train my gender determination model.  
Approximately 40% of this is facial data of Japanese people (including some Asian people other than Japanese).  
This training dataset consists of several publicly available datasets, as well as some collected from the internet.  

Please download and unzip my model 'taguchi_model_gender_classifier.dnn' from the link below.  

[Taguchi's gender model](https://drive.google.com/file/d/1TeWWBfaRkPEyudFwMVo7iNHVRNAInJQA/view?usp=sharing)

## How to compile  
The source code for my gender classification model is 'GenderModelClassifier.cpp'.  
Please refer to dlib.net, which describes how to compile it.  
[How to compile dlib](http://dlib.net/compile.html)

## Running the Taguchi model  
Place the following in the same folder as the exe file created after compilation.  
 * Place the 'gender' folder and the face image file of the young Japanese actor inside it.  
 * Place 'shape_predictor_5_face_landmarks.dat'.  
 * Place 'taguchi_model_gender_classifier.dnn'.  

Please type the following command from the command prompt.  
 * Taguchi model example  
    ```
    > GenderModelClassifier gender
    ```  

When executed, the judgment result will be displayed as 'male' and 'female' along with the accuracy as shown below.  

![GenderModelResult](https://github.com/TaguchiModels/dlibModels/assets/167880914/d09e81a1-d32a-43cc-a9d7-b004e121e618)

## Limitations  
My model lacks training data, so its accuracy may be significantly worse.  
 * A person with African roots.  
 * Persons under 18 years of age.  
 * A person wearing a mask.  

It may not be suitable for the above applications.  
Please use with caution.  

