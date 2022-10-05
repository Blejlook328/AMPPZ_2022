class Place:
    def __init__(self, index : int, type : str, value : int):
        self.index = index
        self.type = type       # B | K | C
        self.value = value
    
    def explore(self, health : int):
        if self.type == 'B':
            if health <= self.value:
                return True, health - self.value
            return False, health - self.value
        elif self.type == 'K':
            if health < self.value:
                return True, health - self.value
            return False, health - self.value
        elif self.type == 'C':
            if health <= self.value:
                return False, self.value
            return False, health
    
    
class Day:
    def __init__(self, type : str, place_index : int, place = None):
        self.type = type       # Z | D
        self.place_index = place_index
        self.place = place

    def change(self, places : list):
        places[self.place_index - 1] = self.place
        return places


def examine(begin : int, places : list, health : int):
    result = -1
    
    for p in range(begin - 1, len(places)):
        death, health = places[p].explore(health)
        if death:
            if p == begin - 1:
                return -1
            return p
    
    return len(places)
    

def main():
    
    amount = int(input())

    for i in range(amount):
        
        line = input().split()
        places_amount = int(line[0])
        days_amount = int(line[1])
        health = int(line[2])

        places = []
        days = []
        
        for p in range(places_amount):
            line = input().split()
            places.append(Place(len(places)+1, line[0], int(line[1])))
            
        for d in range(days_amount):
            line = input().split()
            if len(line) == 2:
                days.append(Day(line[0], int(line[1])))
            elif len(line) == 4:
                days.append(Day(line[0], int(line[1]), Place(int(line[1]), line[2], int(line[3]))))
    
    for i in range(len(days)):
        if days[i].type == 'Z':
            places = days[i].change(places)
        else:
            print(examine(days[i].place_index, places, health))
        
        
if __name__ == '__main__':
    main()