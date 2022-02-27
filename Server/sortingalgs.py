def __merge(array, start, middle, end):
   i = start
   j = middle
   while i < middle and j < end:
       if array[i] > array[j]:           
           temp = array[j]
           #shift all the values between indices by 1
           array[i+1:j+1] = array[i:j]
           array[i] = temp
           i += 1
           j += 1
           middle += 1
       else:
           i += 1
                               
def __mergeSortRecursive(array, start, end):
    if start >= end-1:
        return       
    middle = (start + end) // 2
    __mergeSortRecursive(array, start, middle)
    __mergeSortRecursive(array, middle, end)
    __merge(array, start, middle, end)
    
def mergeSort(array):
    __mergeSortRecursive(array, 0, len(array))