#include <iostream>
#include <time.h>
using namespace std;
const int N = 6, n = 6, M = 3, k = 4;
class obj
{
    friend void dist(obj A[N], obj B, float S[N], int neig[k]);
private:
    int feat[M];
    float res;

public:
    obj() : res(1 + rand() % 15)
    {
        int i;
        for (i = 0; i < M; i++)
            feat[i] = 1 + rand() % 15;
    }
    obj(int feat[M + 1]) : res(feat[M])
    {
        int i;
        for (i = 0; i < M; i++)
            this->feat[i] = feat[i];
    }

    void print(bool f = false)
    {
        int i;
        cout << " (";
        for (i = 0; i < M; i++)
            cout << " " << feat[i];
        cout << " )";
        if (f)
            cout << " = " << res;
    }

    void set_res(obj A[N], int neig[k])
    {
        int i;
        res = 0;
        for (i = 0; i < k; i++)
            res += A[neig[i]].res;
        res /= k;
    }
};



void sort(float S[N], int ind[N])
{
    int i, j = N - 1, L = 0, R = N - 1, obm;
    for (i = 0; i < N; i++)
        ind[i] = i;
    do
    {
        for (i = R; i > L; i--)
        {
            if (S[ind[i]] < S[ind[i - 1]])
            {
                obm = ind[i];
                ind[i] = ind[i - 1];
                ind[i - 1] = obm;
                j = ind[i];
            }
        }
        L = j;
        for (i = L; i < R; i++)
        {
            if (S[ind[i]] > S[ind[i + 1]])
            {
                obm = ind[i];
                ind[i] = ind[i + 1];
                ind[i + 1] = obm;
                j = ind[i];
            }
        }
        R = j;
    } while (L < R);
}
void dist(obj A[N], obj B, float S[N], int neig[k])
{
    int i, j, ind[N];
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
            S[i] += pow((B.feat[j] - A[i].feat[j]), 2);
        S[i] = sqrt(S[i]);
        cout << " S(" << i << "). " << S[i] << endl;
    }
    sort(S, ind);
    for (i = 0; i < k; i++)
        neig[i] = ind[i];
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int i, j, f[n + 1][M + 1] = {
        5, 1, 0, 300,
        3, 1, 1, 225,
        1, 1, 0, 75,
        4, 0, 1, 200,
        4, 0, 0, 150,
        2, 0, 0, 50,
        4, 1, 0, 0,

        /*2, 5, 1, 3, 1, 4,
        4, 3, 5, 1, 5, 3,
        3, 4, 4, 1, 4, 0,*/

        /*-1, -1, 0,*/
    }, neig[k];
    float S[N] = { 0 };
    obj A[N], B;
    bool ff = false;
    for (i = 0; i < n; i++)
    {
        cout << " " << i << ".";
        A[i] = obj(f[i]);
        A[i].print(true);
        cout << endl;
    }
    for (; i < N; i++)
    {
        cout << " " << i << ".";
        A[i] = obj();
        A[i].print(true);
        cout << endl;
    }
    for (i = 0; i < M; i++)
    {
        if (f[n][i] == -1)
        {
            ff = true;
            break;
        }
    }
    if (ff)
        B = obj();
    else
        B = obj(f[n]);
    B.print();
    cout << endl << endl;

    dist(A, B, S, neig);
    cout << "\n Классификация:\n Ближайшие " << k << " соседей:\n";
    for (i = 0; i < k; i++)
    {
        cout << " " << neig[i] << ".";
        A[neig[i]].print(true);
        cout << " (" << S[neig[i]] << ")\n";
    }

    cout << " Регрессия:";
    B.set_res(A, neig);
    B.print(true);
    return 0;
}