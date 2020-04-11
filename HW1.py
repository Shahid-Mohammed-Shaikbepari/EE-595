#HW 1
# Q2

a=[6,14,19,24,6,7,6,24,1,3]
uniqueSet = set(a)
print(uniqueSet)


# Q3
def stringChecker(list, str):
    for s in list:
        if(s == str):
            print("TRUE")
            return
    print("String was not found")


#Q4
def reverseElem(a):
    a_len = len(a)-1
    while a_len >= 0:
        print(a[a_len])
        a_len -= 1


