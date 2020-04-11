import math
import numpy as np
import random
import time

def extractData(fileName):
    # taken from https://www.tutorialspoint.com/How-to-read-text-file-into-a-list-or-array-with-Python
    f = open(fileName, 'r+')
    # taken from https://docs.scipy.org/doc/numpy/reference/generated/numpy.fromstring.html
    data = [np.fromstring(line, dtype=float, sep=' ') for line in f.readlines()]
    f.close()
    return data

def training(data):
    #calculate the mu and sigma for every class
    #divide into sub classes

    class1 = []
    class2 = []
    class3 = []
    for iter in data:
        if iter[7] == 1:
            class1.append(iter)
        elif iter[7] == 2:
            class2.append(iter)
        else:
            class3.append(iter)
    # taken from https://docs.scipy.org/doc/numpy-1.13.0/reference/generated/numpy.var.html
    # calculated mean,variances for 3 classes separtely
    mean1 = np.mean(class1, axis=0)
    mean2 = np.mean(class2, axis=0)
    mean3 = np.mean(class3, axis=0)
    var1 = np.var(class1, axis=0)
    var2 = np.var(class2, axis=0)
    var3 = np.var(class3, axis=0)
    res1 = []
    res2 = []
    res3 = []
    for i in range(7):
        tup1 = [mean1[i], var1[i]]
        tup2 = [mean2[i], var2[i]]
        tup3 = [mean3[i], var3[i]]
        res1.append(tup1)
        res2.append(tup2)
        res3.append(tup3)
    # combined all the  mean, variance of three classes
    result = [res1,res2, res3]
    return result
def GNB(val, mean, var):
    #return (1/(math.sqrt(2*math.pi*var)))*(math.exp(-((val - mean)**2/var)))
    exponent = math.exp(-((val - mean) ** 2 / 2*(var)))
    return (1 / (math.sqrt(2 * math.pi * var))) * exponent

def predict(meanVar, test):
    res = []
    for val in test:
        logSumforAllClasses = []
        for j in range(3):
            logSum = 0
            for i in range(7):
                P_XY =   GNB(val[i], meanVar[j][i][0], meanVar[j][i][1])
                logP_XY = math.log(P_XY, math.e)
                logSum += logP_XY
            logSumforAllClasses.append(logSum)
        res.append(logSumforAllClasses.index(max(logSumforAllClasses))+1)
    return res

def calculateAccuracy(predicted, data):
    count = 0
    for index, val in enumerate(data):
        if predicted[index] == val[7]:
            count += 1
    accuracy = (count/len(data)) * 100
    return accuracy
def SkLearnNB(X_train, y_train, X_test):
    from sklearn.naive_bayes import GaussianNB
    gnb = GaussianNB()
    y_pred = gnb.fit(X_train, y_train).predict(X_test)
    return y_pred

def SVM_SKLearn(X_train, y_train, X_test):
    from sklearn import svm
    classifier = svm.SVC()
    classifier.fit(X_train, y_train)
    pred = []
    for val in X_test:
        pred.append(classifier.predict([val]))
    return pred

def main():
    data = extractData('seeds_dataset.txt')
    # shuffle data and divide 80% of data for train and 20% for testing
    random.shuffle(data)
    dataTrain = data[0:168:1]
    dataTest = data[168: :1]
# taken from https://stackoverflow.com/questions/14452145/how-to-measure-time-taken-between-lines-of-code-in-python
    TrainingStartTime = time.process_time()
    meanVar = training(dataTrain)
    res_train = predict(meanVar, dataTrain)
    TrainingAccuracy = calculateAccuracy(res_train, dataTrain)
    TrainingProcessTime = time.process_time() - TrainingStartTime

    TestingStartTime = time.process_time()
    res_test = predict(meanVar, dataTest)
    TestingAccuracy = calculateAccuracy(res_test, dataTest)
    TestingProcessTime = time.process_time() - TestingStartTime


    print("My Naive Bayes: ")
    print("Training acc:    " + "%.2f" %TrainingAccuracy + "%" + "  Training time: " + "%.4f" %TrainingProcessTime + "  s")
    print("Testing acc:    " + "%.2f" %TestingAccuracy + "%" + "  Testing time: " + "%.4f" % TestingProcessTime + "  s")

    datTrain = np.array(dataTrain)
    datTest = np.array(dataTest)
#taken from https://stackoverflow.com/questions/30062429/python-how-to-get-every-first-element-in-2-dimensional-list/30062458
# taken from https://machinelearningmastery.com/index-slice-reshape-numpy-arrays-machine-learning-python/
    Dtrain = datTrain[:,:-1]
    Dtest = datTest[:,:-1]
    y_train = datTrain[:, 7]
    y_test = datTest[:, 7]

    SKLearnTrainingStartTime = time.process_time()
    trainingPred = SkLearnNB(Dtrain, y_train, Dtrain)
    SKLearnTrainAccuracy = calculateAccuracy(trainingPred, dataTrain)
    SKLearnTrainProcessTime = time.process_time() - SKLearnTrainingStartTime

    SKLearnTestingStartTime = time.process_time()
    testingPred = SkLearnNB(Dtrain, y_train, Dtest)
    SKLearnTestAccuracy = calculateAccuracy(testingPred, dataTest)
    SKLearnTestProcessTime = time.process_time() - SKLearnTestingStartTime


    print("Sklearn Naive Bayes: ")
    print(
        "Training acc:    " + "%.2f" % SKLearnTrainAccuracy + "%" + "  Training time: " + "%.4f" % SKLearnTrainProcessTime + "  s")
    print(
        "Testing acc:    " + "%.2f" % SKLearnTestAccuracy + "%" + "  Testing time: " + "%.4f" % SKLearnTestProcessTime + "  s")

#implementing SVM from sklearn
    SVMTrainingStartTime = time.process_time()
    SVMtrainingPred = SVM_SKLearn(Dtrain, y_train, Dtrain)
    SVMTrainAccuracy = calculateAccuracy(SVMtrainingPred, dataTrain)
    SVMTrainProcessTime = time.process_time() - SVMTrainingStartTime

    SVMTestingStartTime = time.process_time()
    SVMtestingPred = SVM_SKLearn(Dtrain, y_train, Dtest)
    SVMTestAccuracy = calculateAccuracy(SVMtestingPred, dataTest)
    SVMTestProcessTime = time.process_time() - SVMTestingStartTime

    print("Sklearn SVM: ")
    print(
        "Training acc:    " + "%.2f" % SVMTrainAccuracy + "%" + "  Training time: " + "%.4f" % SVMTrainProcessTime + "  s")
    print(
        "Testing acc:    " + "%.2f" % SVMTestAccuracy + "%" + "  Testing time: " + "%.4f" % SVMTestProcessTime+ "  s")






if __name__ == '__main__':
        main()
