#include <iostream>
#include <string>

using namespace std;

int main()
{
    int TT;
    cin >> TT;
    while(TT--)
    {
        string haslo;
        cin >> haslo;
        for(int i=0; i<(int)haslo.size(); i++)
            haslo[i] = 'a'+((haslo[i]-'a'+13)%26);
        cout << haslo << endl;
    }
}
