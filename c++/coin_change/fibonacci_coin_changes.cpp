#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;

using namespace boost::multiprecision;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
const int MAX = 1000001;
uint256_t dp[MAX][100];

vector<int> fibo = {0,2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040};
int N = fibo.size();

int main(){
    for(int i=0;i<=MAX-1;++i){
        for(int j=0;j<N;++j){
            if(i==0)dp[i][j]=1;
            else if(j==0) dp[i][j] = 0;
            else if( fibo[j] > i)
                dp[i][j]= dp[i][j-1];
            else
                dp[i][j] = dp[i-fibo[j]][j] + dp[i][j-1];
        }
    }
    cout << dp[MAX-1][N-1] << endl;
    return 0;
}

// 35149126091976381690058120656043297588150432104344399
