#include <iostream>
#include <string>
using namespace std;

class string_array
{
public:
    string_array()
        : m_DynamicArray(nullptr), m_Size(0)
    {}
    ~string_array()
    {
        delete[] m_DynamicArray;
        m_DynamicArray = nullptr;
        m_Size = 0;
    }
    bool Add(const string& NewEntry)
    {
        m_Size++;
        string* Tmp = new string[m_Size];

        /* NOTE: danger territory, shallow copy strings in dynamic array */
        for (int i = 0; i < m_Size - 1; i++)
        {
            Tmp[i] = std::move(m_DynamicArray[i]);
        }
        Tmp[m_Size - 1] = NewEntry;

        delete[] m_DynamicArray;
        m_DynamicArray = Tmp;

        return true;
    }
    bool Delete(const string& Entry)
    {
        if (m_Size == 0)
            return false;

        int FoundIndex = 0;
        bool Found = false;
        for (int i = 0; i < m_Size; i++)
        {
            if (m_DynamicArray[i] == Entry)
            {
                Found = true;
                FoundIndex = i;
                break;
            }
        }

        if (Found)
        {
            m_Size--;
            string* Tmp = new string[m_Size];

            for (int i = 0; i < m_Size; i++)
            {
                Tmp[i] = std::move(m_DynamicArray[i + (i >= FoundIndex)]);
            }

            delete[] m_DynamicArray;
            m_DynamicArray = Tmp;
        }
        return Found;
    }
    /* assignment required a copy of the string itself to be returned if found, 
     * but nullptr when not found?? */
    /* dangerous to get a pointer to the array, especially when it resizes everytime Add or Delete is called, 
     * caller should make a copy */
    string *Get(int Pos)
    {
        if (Pos < 0 || m_Size <= Pos)
        {
            return nullptr;
        }
        return m_DynamicArray + Pos;
    }
    int GetSize()
    {
        return m_Size;
    }
    void Display(ostream& OutStream)
    {
        OutStream << "[";
        for (int i = 0; i < m_Size; i++)
        {
            OutStream << m_DynamicArray[i];
            if (i != m_Size - 1)
                OutStream << ", ";
        }
        OutStream << "]";
    }

private:
    string *m_DynamicArray;
    int m_Size;
};


template<typename T>
T Prompt(const char *Msg)
{
    T t;
    cout << Msg;
    cin >> t;
    return t;
}

int main()
{
    cout << "Commands: \n"
        <<  "  A <sample string>: add a sample string\n"
        <<  "  D <sample string>: delete a sample string\n"
        <<  "  G <int>:           get a string at index <int>\n"
        <<  "  S:                 get size\n"
        <<  "  Q:                 quit/exit\n";
    string_array SA;
    bool ShouldContinue = true;
    while (ShouldContinue)
    {
        char Cmd = toupper(Prompt<string>("\nEnter a command: ")[0]);
        switch (Cmd)
        {
        case 'A': 
        {
            string Input;
            cin.ignore();
            getline(cin, Input);
            SA.Add(Input);
            cout << "Added: '" << Input << "'";
        } break;
        case 'D':
        {
            string Input;
            cin.ignore();
            getline(cin, Input);
            if (SA.Delete(Input))
            {
                cout << "Deleted '" << Input << "' from string array.";
            }
            else
            {
                cout << "Unable to find '" << Input << "' in string array.";
            }
        } break;
        case 'G':
        {
            int Index = Prompt<int>("");
            string* TmpPtr = SA.Get(Index);
            if (nullptr == TmpPtr)
            {
                cout << "Invalid index: " << Index;
            }
            else
            {
                cout << "[" << Index << "] = " << *TmpPtr;
            }
        } break;
        case 'S':
        {
            cout << "Size: " << SA.GetSize();
        } break;
        case 'Q':
        {
            ShouldContinue = false;
        } break;
        default:
        {
            cout << "Unknown command: '" << Cmd << "'";
        } break;
        }

        cout << '\n';
        SA.Display(cout);
        cout << '\n';
    }
    return 0;
}


/*
Commands:
  A <sample string>: add a sample string
  D <sample string>: delete a sample string
  G <int>:           get a string at index <int>
  S:                 get size
  Q:                 quit/exit

Enter a command: a first
Added: 'first'
[first]

Enter a command: a second
Added: 'second'
[first, second]

Enter a command: a third
Added: 'third'
[first, second, third]

Enter a command: a fourth
Added: 'fourth'
[first, second, third, fourth]

Enter a command: d second
Deleted 'second' from string array.
[first, third, fourth]

Enter a command: d fifth
Unable to find 'fifth' in string array.
[first, third, fourth]

Enter a command: d first
Deleted 'first' from string array.
[third, fourth]

Enter a command: d fourth
Deleted 'fourth' from string array.
[third]

Enter a command: d third
Deleted 'third' from string array.
[]

Enter a command: a first
Added: 'first'
[first]

Enter a command: q

[first]

 */
