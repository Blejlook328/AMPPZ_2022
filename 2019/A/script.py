# NOTE:
'''
FOR INPUT:
4
3 15
6 5 26
3 15
6 5 27
2 1000000000
500123123 497000000
7 2
6 2 4 1 9 3 12

SCRIPTS RETURNS:
2
-1
0
6

EXPECTED OUTPUT:
2
-1
0
4

'''
# ------------------------------------------------------------------------

class Data:
    def __init__(self, n : int, k : int, a : list):
        
        # NOTE: N is NECESSARY ?
        self._n = n             # Amount of planets
        
        self._k = k             # Amount of starships
        self._a = a             # Planets' amounts of citizens
        self._conquered = []    # Conquered planets' Amounts of citizens
        self._result = 0        # Amount of mobilisations

    def _invasion(self, m : int):
        self._conquered.append((2 * m))
        self._k = self._k - (m)
        self._conquered.sort()
    
    def _mobilisation(self):
        self._k = self._k + self._conquered[-1]
        self._conquered[-1] = 0
        self._conquered.sort()
        self._result += 1

    def execute(self):
        self._a.sort()
        
        # If any invasion is possible
        if (self._a[0] < self._k):
            
            # For every planet
            for m in self._a:
                
                # If invasion is possible
                if m <= self._k:
                    self._invasion(m)
                    continue
                    
                while True:
                    # If mobilisation is not possible
                    if self._conquered[-1] == 0:
                        return -1
                    
                    self._mobilisation()
                    
                    # If invasion is possible
                    if m <= self._k:
                        self._invasion(m)
                        break
                        
            return self._result
        
        return -1


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