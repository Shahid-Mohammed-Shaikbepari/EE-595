import random
import subprocess
import os
import math

def cross_entropy(Zcomputed, Zblackbox):
   res = []
   try:
      a = Zcomputed * math.log(float(Zblackbox), 2) 
      b = float(Zblackbox) * math.log(float(Zcomputed), 2)
      res.append(a)
      res.append(b)
   except ValueError, e:
      print "error", e, "on value", Zblackbox
   
   return res
   
randomlist = []
for i in range(0,10000):
    x = random.uniform(-100, 100) #pynative.com
    y = random.uniform(-100, 100)
    d = random.uniform(0, 100)
    tempTuple = (x, y, d) #w3schools.com
    randomlist.append(tempTuple)
    
Zblackbox = []
Zcomputed = []

for i in randomlist:
   r = math.pow(i[0], 2) + math.pow(i[1], 2)
   Zcomputed.append(r)
   res = subprocess.check_output('./blackbox '+str(i[0])+' '+str(i[1])+' '+str(i[2]), shell=True) #youtube.com/sentdex
   Zblackbox.append(res)
   
f= open("results.txt","w+") #guru99.com
for i in range(0, 10000):
   res = cross_entropy(Zcomputed[i], Zblackbox[i])
   f.write(str(res[0]) + " " + str(res[1]) + "\n") 
   

