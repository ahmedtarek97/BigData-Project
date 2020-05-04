# Put here the main flow of the program
from support import computeInter
import pandas as pd
import numpy as np

data_frame = pd.DataFrame(np.array([[1, 2, 3], [4, 5, 6],[1,2,4],[1,3,4],[1,3,5]]))


print(computeInter(data_frame))

