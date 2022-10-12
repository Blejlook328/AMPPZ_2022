class Frog:
    def __init__(self, r : int, s : int):
        self.r = r
        self.s = s

class Stone:
    def __init__(self, init_frog : Frog):
        self._frogs = []
        self._frogs.append(init_frog)
    
    def get_intelligence_sum(self):
        if len(self._frogs) == 0:
            return 0
        
        sum = 0
        for frog in self._frogs:
            sum = sum + frog.s
        
        return sum
    
    def add_frog(self, frog : Frog):
        if len(self._frogs) < 3:
            self._frogs.append(frog)
            return

        minS = self._frogs[0].s
        index = 0

        for i in range(len(self._frogs)):
            if minS > self._frogs[i].s:
                minS = self._frogs[i].s
                index = i

        if minS < frog.s:
            self._frogs[index] = frog

    def get_sum(self):
        value = 0
        for frog in self._frogs:
            value = value + frog.s
        return value

class Scenario:
    def __init__(self, frogs : list):
        self._n = len(frogs)
        self._frogs = frogs
        
        self._stones = []

        for frog in self._frogs:
            self._stones.append(Stone(frog))


    def execute(self):
        # For every stone
        for i in range(self._n):
            
            # Check every frog
            for j in range(self._n):
                if j == i:
                    continue
                        
                distance = j - i
                if distance < 0:
                    distance = distance * -1

                if distance <= self._frogs[j].r:
                    self._stones[i].add_frog(self._frogs[j])

        maxSum = self._stones[0].get_sum()

        for stone in self._stones:
            actSum = stone.get_sum()
            if maxSum < actSum:
                maxSum = actSum

        return maxSum


# --------------------------------------------------


def main():
    amount = int(input())

    results = []

    for i in range(amount):
        n = int(input())
        
        frogs = []

        for j in range(n):
            line = input().split()
            ri = int(line[0])
            si = int(line[1])

            frogs.append(Frog(ri, si))

        scenario = Scenario(frogs)
        
        results.append(scenario.execute())

    del amount, i, j, n, frogs, line, ri, si, scenario

    for result in results:
        print(result)

    del result

if __name__ == '__main__':
    main()
