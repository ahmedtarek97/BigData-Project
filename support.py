from attribute import attribute
from main import DataList

def computeInter(list_of_attribute):
      #in case if there are 2 attribute in the same colum
      for i in range(len(list_of_attribute)):
            for j in range(i+1,len(list_of_attribute)):
                  if list_of_attribute[i].col == list_of_attribute[j].col :
                        return 0
      sum = 0
      for i in range(len(DataList)):
            flag = 0
            for j in range(len(list_of_attribute)):
                  if list_of_attribute[j].val == DataList[i][list_of_attribute[j].col] : 
                        flag =1
                  else :
                        flag=0
                        break
            if flag == 1 :
                  sum=sum+1
      return sum


def support(list_of_attribute):
      return ((computeInter(list_of_attribute)/5822 )*100)

