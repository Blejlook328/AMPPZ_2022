/* Epidemia
 * Model solution
 * O((n + q + sum c_i) * log n)
 * Krzysztof Kleiner
*/

#define ENCODING

#include <bits/stdc++.h>
using namespace std;

struct ContactNode {
    vector<int> forwardEdges {};
    vector<int> backwardEdges {};
    // Each person's pawn is located in the node of this person's most recent contact.
    set<int> pawns {};
    // Number of potentually infected people meeting in this node.
    int safetyConcerns = 0;
};

class ContactGraph {
    vector<ContactNode> graph {};
    vector<int> pawnLocations {};
    set<int> possiblyInfected {}; // People not in the quarantine, who cannot be sure to be healthy.

    void movePersonToNode(int person, int nodeIndex) {
        auto previous = graph.begin() + pawnLocations[person];
        auto current = graph.begin() + nodeIndex;
        assert(previous != current);

        previous->forwardEdges.push_back(nodeIndex);
        if(previous->safetyConcerns != 0)
            current->safetyConcerns++;

        current->backwardEdges.push_back(pawnLocations[person]);
        pawnLocations[person] = nodeIndex;

        previous->pawns.erase(person);
        current->pawns.insert(person);
    }

    // Mark all implications of the fact that a node is healthy.
    void cleanNode(int nodeIndex) {
        auto& node = graph[nodeIndex];

        if(!node.safetyConcerns)
            return;
        node.safetyConcerns = 0;

        for (int person : node.pawns)
            possiblyInfected.erase(person);

        for (int v : node.backwardEdges)
            cleanNode(v);

        for (int v : node.forwardEdges) {
            if(graph[v].safetyConcerns > 1)
                graph[v].safetyConcerns--; // We're no longer a concern from v's perspective.
            else
                cleanNode(v);
        }
    }

public:
    ContactGraph(int n) {
        graph.resize(n);
        pawnLocations.resize(n);

        // Nodes 0..(n-1) are every person's "contacts" with themselves.
        for (int i = 0; i < n; i++) {
            graph[i].pawns.insert(i);
            graph[i].safetyConcerns = 1;
            pawnLocations[i] = i;
            possiblyInfected.insert(i);
        }
    }

    int getFirstPossiblyInfected(int start) const {
        if(possiblyInfected.empty())
            return -1;

        auto it = possiblyInfected.lower_bound(start);
        if(it != possiblyInfected.end())
            return *it;
        return *possiblyInfected.begin();
    }

    void processContact(const vector<int>& people) {
        int nodeInd = graph.size();
        graph.push_back(ContactNode{});

        for (auto p : people)
            movePersonToNode(p, nodeInd);

        if(graph[nodeInd].safetyConcerns) {
            for (auto p : people)
                possiblyInfected.insert(p);
        }
    }

    void processPositiveResult(int person) {
        int numRemoved = possiblyInfected.erase(person);
        if(numRemoved) { // Otherwise, this person has been already removed earlier
            graph[pawnLocations[person]].pawns.erase(person);
            pawnLocations[person] = -1;
        }
    }

    void processNegativeResult(int person) {
        cleanNode(pawnLocations[person]);
    }
};

class Solution {
    const int n, k;
    ContactGraph contacts;
    int firstPossiblyInfected = -1;

    int decodeInputNumber() const {
        int p; cin >> p;
        p--;
#ifdef ENCODING
        p = (p + firstPossiblyInfected + 1) % n;
#endif
        return p;
    }

    void processContact() {
        int num;
        cin >> num;
        vector<int> people(num);
        for (auto& p : people)
            p = decodeInputNumber();
        contacts.processContact(people);
    }

    void printIterationResult() const {
        if(firstPossiblyInfected == -1)
            cout << "TAK\n";
        else
            cout << "NIE " << firstPossiblyInfected + 1 << endl;
    }

public:
    Solution(int n, int k) : n(n), k(k), contacts(n) {}

    void solve() {
        for (int i = 0; i < k; i++) {
            char event; cin >> event;

            if (event == 'K') {
                processContact();
            } else if(event == 'P') {
                contacts.processPositiveResult(decodeInputNumber());
            } else if(event == 'N') {
                contacts.processNegativeResult(decodeInputNumber());
            } else /* event == 'Q' */ {
                int queryStart = decodeInputNumber();
                firstPossiblyInfected = contacts.getFirstPossiblyInfected(queryStart);
                printIterationResult();
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int z; cin >> z;
    while (z--) {
        int n, k; cin >> n >> k;
        Solution(n, k).solve();
    }
    return 0;
}

