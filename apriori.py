import numpy as np

def apriori(attributes):
      # TODO
      trash = 0 # Delete this when begin to work on it.





def AquireData():
      f = open("ticdata2000.txt","r")
      DataList = []
      for line in f.readlines():
            l = line.split()
            DataList.append(( [ l[5], l[7], l[9], l[11], l[13], l[15], l[17], l[19], l[21], l[23], l[25], l[27] ] ))
      return DataList                  
            