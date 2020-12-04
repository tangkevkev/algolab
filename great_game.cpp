#include<iostream>
#include<vector>
#include<stack>

typedef std::vector<bool> VB;
typedef std::vector<VB> MatrixBool;

typedef std::vector<int> VI;
typedef std::vector<VI> MatrixInt;

void testcase(){
    int n,m;
    std::cin >> n;
    std::cin >> m;

    MatrixBool Transitions(n, VB(n, false));


    int red,black;
    std::cin >> red;
    std::cin >> black;

    red = red - 1;
    black = black - 1;

    for(int i = 0; i < m; i++){
        int u,v;
        std::cin >> u;
        std::cin >> v;

        Transitions[u-1][v-1] = true;
    }

    std::vector<std::array<int, 2>>
    std::stack<int> stackPositions;

    stackPositions.push(n-1);

    while(!stackPositions.empty()){

    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;


    for(int i = 0; i < t; i++){
        testcase();
    }

}