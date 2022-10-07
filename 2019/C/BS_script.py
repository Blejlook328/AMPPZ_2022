class Set:
    def __init__(self, n : int, l : list):
        self._n = n
        self._l = l
        
    def __str__(self):
        return f'{self._n} : {self._l}'
    
    def execute(self):
        if self._n < 3:
            return 0
        elif self._n == 3:
            if self._l[0] > self._l[1] + self._l[2] and self._l[1] > self._l[0] + self._l[2] and self._l[2] > self._l[0] + self._l[1]:
                return sum(self._l)
            else:
                return 0
        else:
            # TODO: Check condition of creation the figure
            raise NotImplementedError

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