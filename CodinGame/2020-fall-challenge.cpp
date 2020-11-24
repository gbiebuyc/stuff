#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

#pragma GCC optimize("Ofast")

struct Action {
    int id;
    string type;
    array<int, 4> delta;
    int price;
    int tomeIndex;
    int taxCount;
    bool castable;
    bool repeatable;
};

struct Node {
    union {
        char representation[204];
        struct {
            char inv[4];
            char casted[100];
            char learned[100];
        };
    };
#ifdef DEBUG
    vector<string> path;
#endif
    string firstAction;
    int distance;
};

string nodeToString(Node &node) {
    return string(node.representation, 204);
}

string deltaToString(array<int, 4> &delta) {
    stringstream ss;
    for (int x : delta)
        ss << x << " ";
    return ss.str();
}

int main()
{
    while (1) {
        int actionCount; // the number of spells and recipes in play
        cin >> actionCount; cin.ignore();
        vector<Action> actions;
        for (int i = 0; i < actionCount; i++) {
            int id; // the unique ID of this spell or recipe
            string type; // in the first league: BREW; later: CAST, OPPONENT_CAST, LEARN, BREW
            int delta0; // tier-0 ingredient change
            int delta1; // tier-1 ingredient change
            int delta2; // tier-2 ingredient change
            int delta3; // tier-3 ingredient change
            int price; // the price in rupees if this is a potion
            int tomeIndex; // in the first two leagues: always 0; later: the index in the tome if this is a tome spell, equal to the read-ahead tax; For brews, this is the value of the current urgency bonus
            int taxCount; // in the first two leagues: always 0; later: the amount of taxed tier-0 ingredients you gain from learning this spell; For brews, this is how many times you can still gain an urgency bonus
            bool castable; // in the first league: always 0; later: 1 if this is a castable player spell
            bool repeatable; // for the first two leagues: always 0; later: 1 if this is a repeatable player spell
            cin >> id >> type >> delta0 >> delta1 >> delta2 >> delta3 >> price >> tomeIndex >> taxCount >> castable >> repeatable; cin.ignore();
            Action a = {id, type, {delta0, delta1, delta2, delta3}, price, tomeIndex, taxCount, castable, repeatable};
            if (type == "OPPONENT_CAST")
                continue;
            actions.push_back(a);
        }
        char inv[4];
        for (int i = 0; i < 2; i++) {
            int inv0, inv1, inv2, inv3, score;
            cin >> inv0 >> inv1 >> inv2 >> inv3 >> score; cin.ignore();
            if (i == 0) {
                inv[0] = (char)inv0;
                inv[1] = (char)inv1;
                inv[2] = (char)inv2;
                inv[3] = (char)inv3;
            }
        }
        auto start = chrono::high_resolution_clock::now();

        // BFS
        Node BFS_result = {};
        queue<Node> q;
        unordered_set<string> discovered;
        Node root = {};
        double best = 0;
        int visited = 0;
        memcpy(root.inv, inv, 4);
        for (int i=0; i<actions.size(); i++) {
            root.learned[i] = (actions[i].type == "LEARN") ? 0 : 1;
            root.casted[i] = (actions[i].type == "CAST" && !actions[i].castable) ? 1 : 0;
        }
        discovered.insert(nodeToString(root));
        q.push(root);
        while (!q.empty()) {
            visited++;
            Node current = q.front();
            q.pop();
            current.distance++;
            auto now = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - start).count();
            if (elapsed > 45) {
                if (best == 0)
                    BFS_result = current;
                goto BFS_done;
            }
            vector<Node> neighbors;
            bool canRest = false;
            for (char x : current.casted)
                if (x == 1)
                    canRest = true;
            if (canRest) {
                Node n = current;
                for (int i=0; i<100; i++)
                    n.casted[i] = 0;
#ifdef DEBUG
                n.path.push_back("REST");
#endif
                if (n.firstAction.empty()) n.firstAction = "REST";
                neighbors.push_back(n);
            }
            for (int i=0; i<actions.size(); i++) {
                Action &action = actions[i];
                if (!current.learned[i]) {
                    if (current.inv[0] < action.tomeIndex)
                        continue;
                    Node n = current;
                    n.inv[0] -= action.tomeIndex;
                    n.inv[0] += action.taxCount;
                    n.learned[i] = 1;
#ifdef DEBUG
                    n.path.push_back("LEARN " + deltaToString(action.delta));
#endif
                    if (n.firstAction.empty()) n.firstAction = "LEARN " + to_string(action.id);
                    neighbors.push_back(n);
                    continue;
                }
                if (current.casted[i])
                    continue;
                Node n = current;
                int tot=0;
                for (int j=0; j<4; j++) {
                    n.inv[j] += action.delta[j];
                    if (n.inv[j] < 0)
                        goto skip_action;
                    tot += n.inv[j];
                }
                if (tot > 10)
                    continue;
                n.casted[i] = 1;
#ifdef DEBUG
                {
                    string actionName = (action.type == "LEARN") ? "CAST" : action.type;
                    n.path.push_back(actionName + " " + deltaToString(action.delta));
                }
#endif
                if (n.firstAction.empty()) n.firstAction = action.type + " " + to_string(action.id);
                if (action.type == "BREW") {
                    double ratio = action.price / (double)n.distance;
                    if (ratio > best) {
                        BFS_result = n;
                        best = ratio;
                    }
                    // goto BFS_done;
                    continue;
                }
                neighbors.push_back(n);
                if (action.repeatable) {
                    for (int repeat=2; repeat<=10; repeat++) {
                        Node n = current;
                        int tot=0;
                        for (int j=0; j<4; j++) {
                            n.inv[j] += (action.delta[j] * repeat); // Repeat
                            if (n.inv[j] < 0)
                                goto next_repeat;
                            tot += n.inv[j];
                        }
                        if (tot > 10)
                            continue;
#ifdef DEBUG
                        string actionName = (action.type == "LEARN") ? "CAST" : action.type;
                        n.path.push_back(actionName + " " + deltaToString(action.delta) + " x" + to_string(repeat));
#endif
                        if (n.firstAction.empty()) n.firstAction = "CAST " + to_string(action.id) + " " + to_string(repeat);
                        neighbors.push_back(n);
                        next_repeat: ;
                    }
                }
            skip_action:
                ;
            }
            for (auto neighbor : neighbors) {
                string repr = nodeToString(neighbor);
                if (discovered.find(repr) == discovered.end()) {
                    discovered.insert(repr);
                    q.push(neighbor);
                }
            }
        }
        cerr << "oh no" << endl;
    BFS_done:
        ;
#ifdef DEBUG
        for (auto a : BFS_result.path) {
            cerr << a << endl;
        }
#endif
        cerr << visited << endl;
        cout << BFS_result.firstAction << endl;
    }
}
