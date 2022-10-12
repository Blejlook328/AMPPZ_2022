import numpy as np

class Scenario:
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

    def _get_next_unconquered(self, index : int):
        for i in range(index + 1, self._n):
            if self._conquered[i] == 0:
                return self._a[i]
        return self._k + 1
        
    def execute(self):
        
        # If enconquer all the planets is possible
        if sum(self._a) <= self._k:
            return 0
        
        # Sort planet from min to max
        self._a.sort()
        
        while True:
            
            for i in range(self._n):
                
                if self._conquered[i] == 1:
                    continue
                
                if i < self._n - 1 and self._get_next_unconquered(i) <= self._k:
                    continue
                
                if self._a[i] <= self._k:
                    self._invasion(i)
                    
                    for j in range(i, -1, -1):
                        if self._a[j] <= self._k:
                            self._invasion(j)
                
                if 0 in self._conquered:
                    
                    if self._mobilisation():
                        
                        break
                    
                    return -1
                
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
        scenario = Scenario(n, k, a)
        
        # Execute algorithm on data set and save result
        results.append(scenario.execute())
    
    # Delete unnecessary variables
    del n, k, a, line, scenario, amount
    
    # Print all results
    for result in results:
        print(result)
        
    # Delete results list
    del results


if __name__ == '__main__':
    main()