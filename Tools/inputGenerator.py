# generate random integer values
from numpy.random import randint
from numpy import array2string
import argparse

class Interval:
    def __init__(self,min, max):
        self.__min = min
        self.__max = max
        return
    def min(self):
        return self.__min 
    def max(self):
        return self.__max    

def createTxtFile(fileName, lines, elementsInLine, intInterval ):
    numberOfLines = randint(lines.min(),  lines.max(),1)
    
    # Writing to file
    with open(fileName, "w") as writer:
        for i in range(numberOfLines[0]):
            valuesInLine = randint(intInterval.min(), intInterval.max(), randint(elementsInLine.min(), elementsInLine.max(),1))
            line = array2string(valuesInLine,max_line_width=400)
            writer.write(line[1:-1])
            writer.write("\n")
    return   

def main(fileName, maxLines, maxIntsInLine, maxInt):  
    try:
        createTxtFile(fileName, Interval(0,maxLines), Interval(0,maxIntsInLine), Interval(0,maxInt) )
    except FileNotFoundError as error:
        print(error)
    
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description = 'Generates a txt file ')
    parser.add_argument('fileName',  nargs='?', type=str, default="input.txt", help='name of the txt file to be generated')
    parser.add_argument('maxLines',  nargs='?', type=int, default=1000000, help='max number of lines in txt file')
    parser.add_argument('maxIntsInLine',  nargs='?', type=int, default=100, help='max number of integers in one line')
    parser.add_argument('maxInt',  nargs='?', type=int, default=100, help='max integer value')
    args = parser.parse_args()
    main(args.fileName, args.maxLines, args.maxIntsInLine, args.maxInt )