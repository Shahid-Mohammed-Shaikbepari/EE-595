
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
def readData():
    #taken from https://medium.com/@petehouston/read-csv-file-using-pandas-94288353dd34
    pd_reader = pd.read_csv('candyshop_data.txt', header=None)
    X1 = pd_reader.iloc[:, :-1].values
    dataFrame_X1 = pd.DataFrame(data=X1)
    Y = pd_reader.iloc[:, [1]]
    dafaFrame_Y = pd.DataFrame(data=Y)
    column = np.ones((97, 1), dtype=int)
    X = np.concatenate((X1, column), 1)
    dataFrame_X = pd.DataFrame(data=X)
    #w = (X^T*X)^-1*X^T*y
    XT = X.T  #X transpose
    dataFrame_XT = pd.DataFrame(data=XT)
    #taken from https://pythontic.com/pandas/dataframe-binaryoperatorfunctions/dot
    mul =  dataFrame_XT.dot(dataFrame_X)
    inv = np.linalg.inv(mul) #taken from tutorialspoint.com
    dataFrame_inv = pd.DataFrame(data=inv)
    temp_res = dataFrame_inv.dot(dataFrame_XT)
    w = temp_res.dot(dafaFrame_Y)
    plt.scatter(dataFrame_X1, dafaFrame_Y)
    abline(w[1][0], w[1][1])
    plt.xlabel('population of a city')
    plt.ylabel('profit')
    plt.show()

    print("the profit for city with 20000 population is")
    print("$ " + str(line(2,w[1][0], w[1][1])*10000))
    print("the profit for city with 50000 population is")
    print("$ " + str(line(5,w[1][0], w[1][1])*10000) )



    # print(f'\t{row[0]} --  {row[1]} ')

# taken from https://stackoverflow.com/questions/7941226/how-to-add-line-based-on-slope-and-intercept-in-matplotlib
def abline(slope, intercept):
    """Plot a line from slope and intercept"""
    axes = plt.gca()
    x_vals = np.array(axes.get_xlim())
    y_vals = intercept + slope * x_vals
    plt.plot(x_vals, y_vals)
def line(x, slope, intercept):
    return slope*x + intercept
readData()
