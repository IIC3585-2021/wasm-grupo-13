#pragma adj_matrixCC optimize("Ofast")
#include <emscripten.h>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int MAXN = 16, INF = 1e9;
int dp_table[MAXN][1<<MAXN];
int adj_matrix[MAXN][MAXN];
int nodes;

int dp(int city, int cities_visited_mask){
    if (!cities_visited_mask) return dp_table[city][cities_visited_mask] = 0;
    if (~dp_table[city][cities_visited_mask]) return dp_table[city][cities_visited_mask];
    int ans = INF;
    for (int i = 0; i < nodes; ++i) {
        if ((1<<i)&cities_visited_mask) ans = min(ans, adj_matrix[city][i] + dp(i, cities_visited_mask ^ (1<<i)));
    }
    return dp_table[city][cities_visited_mask] = ans;
}

void recovery(int city, int cities_visited_mask, int val, string &answer_path){
    if (!cities_visited_mask) return;
    for (int i = 0; i < nodes; ++i) {
        if (((1<<i)&cities_visited_mask) && val ==  adj_matrix[city][i] + dp(i, cities_visited_mask ^ (1<<i))){
            answer_path += (i+'A');
            recovery(i,  cities_visited_mask^(1<<i), val - adj_matrix[city][i], answer_path);
            return;
        }
    }
}

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    string * find_best(vector<vector<int>> &A){
        nodes = A.size();
        for (int i = 0; i < nodes; ++i) for (int j = 0; j < nodes; ++j) adj_matrix[i][j] = A[i][j] == -1 ? INF : A[i][j];
        memset(dp_table, -1, sizeof(dp_table));
        int min_cost = INF;
        int start = -1;
        for (int i = 0; i < 1; ++i) {
            if (dp(i, ((1<<nodes)-1)^(1<<i))  < min_cost) min_cost = dp(i, ((1<<nodes)-1)^(1<<i)), start = i;
        }
        if (min_cost == INF){
            static string answer_path = "NO EXISTE CAMINO";
            return &answer_path;
        }
        string answer_path; answer_path += start+'A';
        recovery(start, ((1<<nodes)-1)^(1<<start),  min_cost, answer_path);
        static string final_answer = answer_path;
        return &final_answer;
    }
}


int32_t main(){
    int m; cin >> nodes >> m;
    vector<vector<int>> A(nodes, vector<int>(nodes, INF));
    for (int i = 0; i < m; ++i) {
        int w;
        char u, v; cin >> u >> v >> w;
        A[u-'A'][v-'A'] = A[v-'A'][u-'A'] = w;
    }
    string* s = find_best(A);
    cout << s << "\n";
}