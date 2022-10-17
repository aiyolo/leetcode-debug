
#include "header.h"

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row[9][10] = {0};
        int col[9][10] = {0};
        int box[9][10] = {0};
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                if(board[i][j]=='.') continue;
                if(row[i][board[i][j]-'0']==1) return false;
                if(col[j][board[i][j]-'0']==1) return false;
                if(box[3*(i/3)+j/3][board[i][j]-'0']==1) return false;
                row[i][board[i][j]-'0'] = 1;
                col[j][board[i][j]-'0'] =1;
                box[3*(i/3)+j/3][board[i][j]-'0'] =1;
            }
        }
        return true;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
  Excecutor<Solution, true> exc("../testcases.txt");
  exc.instance = exc.createInstance<void>();
  REGISTER(isValidSudoku)
  exc.run();
}