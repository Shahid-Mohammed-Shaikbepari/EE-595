
#Q12
f = open(r'D:\Users\shahi\PycharmProjects\595HW1\HW1-Q12-output.txt', "w+")
a =[2,8,10,15,17,7]
print("Q12")
f.write("Q12 output \n")
def SummationOfOddnMax(a):
    for i in a:
        if i%2 != 0:
            v = i + max(a)
            print(v)
            f.write(str(v) + "\n")

SummationOfOddnMax(a)