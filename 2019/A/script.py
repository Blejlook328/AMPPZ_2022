import numpy as np

class Data:
    def __init__(self, n : int, k : int, a : list):
        self._n = n
        self._k = k                                     # Amount of starships
        self._a = a                                     # Planets' amounts of citizens
        self._conquered = np.zeros((n,), dtype=int)     # Planets' states: 1 - conquered; 0 - non-conquered
        self._result = 0                                # Amount of mobilisations

    def _invasion(self, i : int):
        self._conquered[i] = 1
        self._k = self._k - (self._a[i])
        self._a[i] = 2 * self._a[i]
    
    def _mobilisation(self):
        index = 0
        max_val = 0
        # Searching for max amount of starship to mobilize
        for i in range(self._n):
            if self._a[i] > max_val and self._conquered[i] == 1:
                index = i
                max_val = self._a[i]
        
        # If there is no starship to mobilize
        if max_val == 0:
            return False
        
        self._k = self._k + self._a[index]
        self._a[index] = 0
        self._result += 1
        return True

    def execute(self):
        
        # If enconquer all the planets is possible
        if sum(self._a) <= self._k:
            return 0
        
        # Sort planet from min to max
        self._a.sort()
        
        while True:
            
            # For every planet
            for i in range(self._n):
                
                # If next planet is available to conquer
                if i < self._n -1 and self._a[i+1] <= self._k:
                    continue
                
                # If certain planet is available to conquer
                if self._a[i] <= self._k:
                    self._invasion(i)
                    
                    # Check the previous planets
                    for j in range(i, -1, -1):
                        if self._a[j] <= self._k:
                            self._invasion(j)
                    
                    # If there are still planets to conquer
                    if 0 in self._conquered:
                        # If mobilisation is not possible
                        if not self._mobilisation():
                            return -1
                        
                    # If all the planets are conquered
                    return self._result


def main():
    # First Line
    amount = int(input())
    
    # Objects list init
    results = []
    
    # Getting input
    for i in range(amount):
        line = input().split()
        n = int(line[0])
        k = int(line[1])

        line = input().split()
        a = [eval(j) for j in line]

        # Creating data set object
        data = Data(n, k, a)
        
        # Execute algorithm on data set and save result
        results.append(data.execute())
    
    # Delete unnecessary variables
    del n, k, a, line, data, amount
    
    # Print all results
    for result in results:
        print(result)
        
    # Delete results list
    del results
        

if __name__ == '__main__':
    main()