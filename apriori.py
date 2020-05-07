import numpy as np

def apriori(attributes):
      # TODO
      trash = 0 # Delete this when begin to work on it.





def AquireData():
      f = open("ticdata2000.txt","r")
      DataList = []
      for line in f.readlines():
            l = line.split()
            DataList.append(( [ l[5], l[6], l[7], l[8], l[9], l[10], l[11], l[12], l[13], l[14], l[15], l[16] ] ))
      return DataList                  
            