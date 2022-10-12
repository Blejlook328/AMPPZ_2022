class Set:
    def __init__(self, n : int, l : list):
        self._n = n
        self._l = l
        
    def __str__(self):
        return f'{self._n} : {self._l}'
    
    def execute(self):
        
        if self._n < 3:
            return 0

        self._l.sort()

        i = -1
        while True:
            if (self._n + i == 0):
                break
            if self._l[i] < sum(self._l[:i]):
                if i == -1:
                    return sum(self._l)
                return sum(self._l[:i+1])
            i = i - 1
        return 0
            

def main():
    amounts = int(input())

    sets = []

    for z in range(amounts):
        segments_amount = int(input())
        line = input().split()
        segments = []
        for seg in line:
            segments.append(int(seg))

        sets.append(Set(segments_amount, segments))
    
    for set in sets:
        try:
            print(set.execute())
        except NotImplementedError:
            print(f'Not Implemented Algorithm for set: {set}')

if __name__ == '__main__':
    main()
