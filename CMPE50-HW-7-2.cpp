#include <iostream>

void ReverseWholeArray(int *Array, size_t ElemCount)
{
    int *Front = Array;
    int *Back = Array + ElemCount - 1;
    while (Front < Back)
    {
        std::swap(*Front++, *Back--);
    }
}

template<typename T>
T Prompt(const char *Msg)
{
    T t;
    std::cout << Msg;
    std::cin >> t;
    return t;
}

int main()
{
    using namespace std;
    do {
        int Length = 0;
        do {
            Length = Prompt<int>("Enter array length (> 0): ");
        } while (Length <= 0);

        int *Array = new int[Length];
        cout << "Enter " << Length << " integers separated by space: \n";
        for (int i = 0; i < Length; i++)
        {
            cin >> Array[i];
        }

        ReverseWholeArray(Array, Length);
        cout << "[";
        for (int i = 0; i < Length; i++)
        {
            cout << Array[i];
            if (i != Length - 1)
                cout << ", ";
        }
        cout << "]\n";

        delete[] Array;
    } while (tolower(Prompt<string>("Continue? (y/n)")[0]) == 'y');
    return 0;
}


/*
Enter array length (> 0): 5
Enter 5 integers separated by space:
1 2 3 4 5
[5, 4, 3, 2, 1]
Continue? (y/n)y
Enter array length (> 0): 4
Enter 4 integers separated by space:
1 2 3 4
[4, 3, 2, 1]
Continue? (y/n)n
 */
