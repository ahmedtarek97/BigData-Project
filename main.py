
# Put here the main flow of the program
import numpy as np
from apriori import *


ColumnNames = {
    5:"Customer",
    6:"Roman catholic",
    7:"Protestant",
    8:"Other religion",
    9:"No religion",
    10:"Married",
    11:"Living together",
    12:"Other relation",
    13:"Singles",
    14:"Household without children",
    15:"Household with children",
    16:"High level education"
}

L2 = {

    1: "Successful hedonists",

    2: "Driven Growers",

    3: "Average Family",

    4: "Career Loners",

    5: "Living well",

    6: "Cruising Seniors",

    7: "Retired and Religeous",

    8: "Family with grown ups",

    9: "Conservative families",

    10: "Farmers"
}

DataList = AquireData()


