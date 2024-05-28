#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    chrono::steady_clock::time_point end;

    while (true)
    {
        end = chrono::steady_clock::now();
        chrono::steady_clock::duration elapsed_seconds = end - start;
        if (elapsed_seconds >= chrono::seconds(1))
        {
            cout << "while" << endl;
            break;
        }
    }

    return 0;
}
