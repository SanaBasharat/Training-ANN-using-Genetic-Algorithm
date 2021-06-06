# Training-ANN-using-Genetic-Algorithm
Implementing the ANN’s Feed Forward Network and training it using Genetic Algorithm in C++.

This project is based on using Genetic Algorithm to train the weights of a Neural Network. To the best of my knowledge, I generated a population of 100 ANNs (by generating 100 Weight matrices), and then used selection, crossover and mutation for a period of 100 generations in order to come up with a final Weight matrix. I then plugged this matrix into the ANN, using Back Propagation to update the weights.

Note: In order to randomize the dataset, I wrote a separate c++ code, attached in the submission folder as “RandomizeDataset.cpp”. I first converted the given .xlsx file to .txt file and then fed it into this code. This generated a randomized .txt file called “randomized dataset.txt”. I then used this file in my main c++ code (AIBonus.cpp).
The reason for doing this is that if I simply randomized the dataset in my main code, then I would not be able to produce consistent results. At each run of the code, rand() would be seeded to a different time and hence, the dataset would be randomized in a different way. In order to be able to observe and report consistent results, I used the aforementioned method of randomizing the dataset.

Moving on to the actual algorithm, the structure of the Weight matrix I used is as follows:

![image](https://user-images.githubusercontent.com/54366232/120939674-8e064580-c732-11eb-887d-f963aa6e340c.png)

This matrix is hard to understand on its own, so please refer to the image below, where the weights have been color coded to match the matrix, for better understanding.

![image](https://user-images.githubusercontent.com/54366232/120939686-96f71700-c732-11eb-8b67-b7b08f4d75dd.png)


Genetic Algorithm:

For the Genetic Algorithm, the population size was 100 and the algorithm was run over 100 generations. The fitness function I used was:
F(x) = output(1) + output(2) + output(3)
Where output(i) refers to the output of the i’th perceptron in the output layer.
For selection, I used the first 40% of the 100 samples.
For crossover, I used a 5x5 section of the Weight matrix, as highlighted below.

![image](https://user-images.githubusercontent.com/54366232/120939711-afffc800-c732-11eb-9ab4-46f83edee3ca.png)


For mutation, I used a 2x10 section of the Weight matrix, as highlighted below.

![image](https://user-images.githubusercontent.com/54366232/120939725-c3129800-c732-11eb-9b24-3a325e4f66e1.png)


Back Propagation:

This was the trickiest part of the project.
The formulae I used, were as follows.

![image](https://user-images.githubusercontent.com/54366232/120939752-e76e7480-c732-11eb-9d64-2215677d6497.png)


Testing using 2-Fold Cross Validation:

I used the first 75 samples for training and the rest for testing at first. This resulted in 27 out of 75 samples being matched. I then used the last 75 samples for training and the first 75 for testing. This resulted in 23 out of 75 samples being matched.

Results:

Adding up the correct matches, I got 50 out of 150 samples that were correctly matched. Using the technique mentioned in the assignment for calculating the accuracy, I calculated my algorithm’s accuracy to be a disappointing 33.33%.
