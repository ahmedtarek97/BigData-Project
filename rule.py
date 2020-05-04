from support import support

class rule:
  def __init__(self, left, right):
    self.left = left
    self.right = right
  
  def confidence(self):
      # a -> b 
      #confidence = support(a,b)/ support(a)
      temp_num =self.left +self.right 
      num = support(temp_num)
      den = support(self.left)
      conf = num / den
      return conf *100



