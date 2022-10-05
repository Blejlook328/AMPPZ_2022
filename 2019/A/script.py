# NOTE:
'''

DATA:
-----
n - planets
a[] - planets' citizens

k - starships

    INVASION:
        s - starships to certain planet
        m - certain planet's citizens
        
        s > m
        
        AFTER:
        
        a[x] - m + s;   x - index of certain planet
        s = 0
    
    MOBILIZATION:
        k = k + a[x];   x - index of certain planet
        a[x] = 0

    GOAL:
        Minimal amount of mobilizations to conqer all the planets
        
--------------------------------------

INPUT:
------

data.length()

data[0]:
    n k
    a[0] ... a[n-1]

...

data[data.length() - 1]:
    n k
    a[0] ... a[n-1]


OUTPUT:
-------

Minimal amount of mobilizations for the certain data

OR

-1 if not possible

'''
# ------------------------------------------------------------------------

class Data:
    def __init__(self, n : int, k : int, a : list):
        self._n = n
        self._k = k
        self._a = a

    def execute(self):
        self._a.sort()
        
        if (self._a[0] <= self._k):
            return 0
        return -1

    def run(self):
        result = self.execute()
        print(result)



def main():
    # First Line
    amount = int(input())
    
    # Objects list init
    data_list = []
    
    # Getting input
    for i in range(amount):
        line = input().split()
        n = int(line[0])
        k = int(line[1])

        line = input().split()
        a = [eval(j) for j in line]

        # Creating data set object
        data = Data(n, k, a)
        
        # Adding to list
        data_list.append(data)
    
    # Delete unnecessary variables
    del n, k, a, line, amount
    
    for data in data_list:
        # Algorithm on certain data set and get output
        data.run()
        
        # Delete executed data set
        del data
        
    # Delete empty list
    del data_list
        

if __name__ == '__main__':
    main()