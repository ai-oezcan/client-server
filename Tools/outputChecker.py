import argparse

def readTxtFile(fileName):
    # reading from file
    with open(fileName, "r") as reader:
        line = reader.readline()
        while line != '':
            arr = [int(i) for i in line.split()]
            assert all(arr[i] <= arr[i + 1] for i in range(len(arr)-1)), f"Error: Line is not sorted: {line}"           
            line = reader.readline()
    return   

def main(fileName):  
    try:
        readTxtFile(fileName)
        print("File is sorted correctly.")
    except FileNotFoundError as error:
        print(error)
    except AssertionError as error:
        print(error)
    
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description = 'Checks each line of the txt file ')
    parser.add_argument('fileName', nargs='?', type=str, default="output.txt", help='name of the txt file to be checked')
    args = parser.parse_args()
    main(args.fileName)