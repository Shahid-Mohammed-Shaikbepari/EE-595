
#Q10
#scenario 1 without indentation
f = open(r'D:\Users\shahi\PycharmProjects\595HW1\HW1-Q10-output.txt', "w+")
intA = 5
f.write("Q10 scenario 1 without indentation \n")
if intA > 10:
    print("hello")
print(intA)
f.write(str(intA) + "\n")
f.write("end \n")

#scenario 1 with indentation

intA = 5
f.write("Q10 scenario 1 with indentation \n")
if intA > 10:
    print("hello")
    print(intA)
    f.write(str(intA) + "\n")
f.write("end \n")
#scenario 2 with indentation
f.write("scenario 2 with indentation \n")
a = 5
for i in range(5):
    a = i
    print(a)
    f.write(str(a) + "\n")

#scenario 2 without indentation
f.write("scenario 2 without indentation \n")
a = 5
for i in range(5):
    a = i
print(a)
f.write(str(a) + "\n")