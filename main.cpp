#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

void sieve(bool* ifPrime, int n, vector<int> prime, int* sPrimeFact) {
    for (int i = 2; i * i <= n; i++) {
        if (ifPrime[i]) {
            prime.push_back(i);
            sPrimeFact[i] = i;
        }

        for (int j = 0; j < prime.size() && i*prime[j] <= n && prime[j] <= sPrimeFact[i]; j++) {
            ifPrime[i*prime[j]] = false;
            sPrimeFact[i * prime[j]] = prime[j] ;
        }
    }
}


vector<int> split(vector<int> a, vector<int> b) {
    if (b.empty()) {
        return a;
    }

    int maxValue = 0; //current max frequency
    unordered_map<int, int> freqCount; //map number->frequency
    vector<int> c;

    for (int & i : a) {
        if (freqCount.find(i) == freqCount.end()) {
            freqCount.insert({i, 0});
        }
    }

    int temp;
    for (int & i : b) {
        if (freqCount.find(i) != freqCount.end()) {
            temp = freqCount[i];
            temp++;
            freqCount[i] = temp;
            if (temp > maxValue) {
                maxValue = temp;
            }
        }
    }

    vector<int> prime;
    int sPrimeFact[maxValue + 1];
    bool ifPrime[maxValue + 1]; // true -> is prime
    memset(ifPrime, true, sizeof(ifPrime));
    ifPrime[0] = ifPrime[1] = false;
    sieve(ifPrime, maxValue, prime, sPrimeFact);

    for (int i : a) {
        temp = freqCount[i];
        if (!ifPrime[temp]) {
            c.push_back(i);
        }
    }
    return c;
}

int main() {
    vector<int> a = {2,3,9,2,5,1,3,7,10};
    vector<int> b = {2,1,3,4,3,10,6,6,1,7,10,10,10};
    vector<int> c = split(a, b);
    for (int i: c)
        cout << i << ' ';
    return 0;
}
