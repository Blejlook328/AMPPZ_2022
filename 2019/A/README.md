# **Zadanie A**: Asymilacja

## *Limit czasowy: 1s, limit pamięciowy: 512 MB*

___

## **Treść**

Źli i podstępni...znaczy się, dzielni i szlachetni Obcy chcą przemocą zasymilować i włączyć do zbiorowego umysłu...znaczy się, doprowadzić do doskonałości i otworzyć na nowe możliwości
nowy system gwiezdny.
W systemie jest 𝑛 planet, na których znajduje się odpowiednio 𝑎1, 𝑎2, . . . , 𝑎𝑛 mieszkańców. 

Na początku Obcy mają 𝑘 statków asymilacyjnych. Obcy mogą wykonywać następujące posunięcia:
 - inwazję – lądowanie na planecie pewną liczbą statków asymilacyjnych. Liczba statków 𝑠
musi być większa lub równa liczbie 𝑚 mieszkańców planety. Po inwazji statki znikają, a
planeta jest opanowana i ma 𝑚 + 𝑠 mieszkańców.

 - mobilizację – opanowana planeta może wystawić tyle statków asymilacyjnych, ile sama ma
mieszkańców. Może to jednak zrobić tylko raz.

Dla Obcych dokonywanie inwazji jest naturalne niczym oddychanie, trudną operacją jest za
to mobilizacja opanowanej planety. Pomóż im – wyznacz najmniejszą liczbę mobilizacji, jakich
trzeba dokonać, aby opanować wszystkie planety.

## **Wejście**

Dla każdego zestawu danych wypisz w osobnej linii jedną liczbę całkowitą: najmniejszą liczbę
operacji mobilizacji koniecznych do opanowania wszystkich 𝑛 planet. Jeśli asymilacja całego
systemu nie jest możliwa, wypisz −1.

### **Przykład:**

#### **Wejście**:

    4
    3 15
    6 5 26
    3 15
    6 5 27
    2 1000000000
    500123123 497000000
    7 2
    6 2 4 1 9 3 12

#### **Wyjście**:

    2
    -1
    0
    4
___

## **Wyjaśnienie**

W pierwszym zestawie zaczynamy z 15 statkami. Możemy wysłać 6 statków (lub o kilka więcej) do przeprowadzenia inwazji na pierwszej planecie, po czym jest tam 6 + 6 = 12 mieszkańców. Pozostaje 15 − 6 = 9 statków, ale możemy przeprowadzić mobilizację 12 mieszkańców pierwszej planety. To daje 9 + 12 = 21 statków.
Następnie wydzielamy 5 lub więcej statków, lądujemy na drugiej planecie, mobilizujemy tę planetę i mamy 26 statków – w sam raz na przeprowadzenie inwazji na ostatniej planecie.
Przedstawiona strategia używa mobilizacji dwa razy i jest to optymalny wynik. 
Istnieją też inne optymalne strategie, w tym taka, że najpierw opanowujemy drugą planetę.