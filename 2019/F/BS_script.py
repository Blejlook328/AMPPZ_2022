class Result:
    def __init__(self, perms : list):
        self._perms = perms

    def __str__(self):
        result = f'{len(self._perms)}'
        for perm in self._perms:
            result += '\n'
            for element in perm:
                result += f'{element} '
        return result

class Scenario:
    def __init__(self, n : int, k: int, S : list):
        self._n = n
        self._k = k
        self._S = S
        self._C = []

        for i in range(n):
            self._C.append(i+1)

    def _check_sum(self, actC):
        start = 0
        end = self._k

        for value in self._S:
            if value != sum(actC[start:end]):
                return False
            start += 1
            end += 1

        return True

    def _permutation(self, lst: list):
        if len(lst) == 0:
            return []
        if len(lst) == 1:
            return [lst]

        l = []

        for i in range(len(lst)):
            m = lst[i]

            remainderLst = lst[:i] + lst[i+1:]

            for p in self._permutation(remainderLst):
                l.append([m] + p)
        return l


    def execute(self):
        results = []

        for p in self._permutation(self._C):
            if self._check_sum(p):
                results.append(p)

        return Result(results)


def main():
    amount = int(input())

    results = []

    for i in range(amount):
        line = input().split()
        n = int(line[0])
        k = int(line[1])

        line = input().split()
        S = [eval(j) for j in line]

        scenario = Scenario(n, k, S)

        results.append(scenario.execute())


    for result in results:
        print(result)


if __name__ == '__main__':
    main()

