#include <iostream>
#include <string>


class sstring : public std::string
{
public:
    /* default ctor */
    sstring() = default;
    /* c-str ctor */
    sstring(const char *CStr)
        : std::string(CStr)
    {}
    /* cpy ctor (base class) */
    sstring(const std::string& CppStr)
        : std::string(CppStr)
    {}
    /* cpy ctor */
    sstring(const sstring& SStr)
        : std::string(SStr)
    {}
    /* move ctor */
    sstring(sstring&& SStr)
        : std::string(std::move(SStr))
    {}

    sstring& operator=(const char *Rhs)
    {
        assign(Rhs);
        return *this;
    }
    sstring& operator=(const sstring& Rhs)
    {
        assign(Rhs);
        return *this;
    }


    sstring operator-(const sstring& Rhs)
    {
        if (Rhs.length() == 0)
            return *this;

        sstring Result = *this;

        int MatchingLength = 0;
        for (int i = 0; i < Result.length(); i++)
        {
            /* remove if the sequence is equal to the rhs */
            if (MatchingLength == Rhs.length())
            {
                if (MatchingLength > i)
                {
                    /* should not be possible */
                    std::cerr << "Unreachable\n";
                    exit(1);
                }

                int StartIndex = i - MatchingLength;
                /* create a brand new string that exclude the equal parts (slow!) */
                Result = Result.substr(0, StartIndex) + Result.substr(i, Result.length() - i);

                /* reset counters */
                i = StartIndex;
                MatchingLength = 0;
            }

            if (Result[i] == Rhs[MatchingLength])
            {
                /* keep counting the equal chars */
                MatchingLength++;
            }
            else
            {
                /* reset if the sequence of string does not equal the right hand side */
                MatchingLength = 0;
            }
        }
        return Result;
    }
    sstring operator*(size_t Multiple)
    {
        sstring Copy; /* empty str if Multiple = 0 */
        while (Multiple --> 0)
        {
            Copy += *this;
        }
        return Copy;
    }
    sstring operator/(size_t Divisor)
    {
        /* no */
        if (Divisor == 0)
        {
            return sstring();
        }

        size_t NewLength = length() / Divisor;
        return this->substr(0, NewLength);
    }
    sstring operator!()
    {
        sstring New = *this;
        for (size_t i = 0; i < New.length()/2; i++)
        {
            std::swap(New[i], New[New.length() - i - 1]);
        }
        return New;
    }
    sstring operator++() /* ++preinc */
    {
        /* ughhhhh length == 0 */
        if (length() == 0)
            return *this;

        return *this = (at(length() - 1) + *this).substr(0, length());
    }
    sstring operator--() /* --predec */
    {
        if (length() == 0)
            return *this;

        return *this = (*this + at(0)).substr(1, length());
    }
    sstring operator++(int) /* postinc++ */
    {
        sstring Old = *this;
        /* discarding return value (waste?) */
        (void)++(*this);
        return Old;
    }
    sstring operator--(int) /* postdec-- */
    {
        sstring Old = *this;
        (void)--(*this);
        return Old;
    }
};

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
    std::cout << sstring("This is a c-string\n");
    do {
        sstring A = Prompt<sstring>("Enter first string: ");
        sstring B = Prompt<sstring>("Enter second string: ");
        cout << "binary op: \n";
        cout << "A + B = " << A + B << "\n";
        cout << "A - B = " << A - B << "\n";
        cout << "single op: \n";
        cout << "!A  = " << !A << "\n";
        cout << "A-- = " << A-- << "\n";
        cout << "A++ = " << A++ << "\n";
        cout << "A   = " << A << "\n";
        cout << "--A = " << --A << "\n";
        cout << "++A = " << ++A << "\n";
        cout << "A   = " << A << "\n";
        size_t Value = Prompt<size_t>("Enter an unsigned int for mul and div: ");
        cout << "B / " << Value << " = " << B / Value << "\n";
        cout << "B * " << Value << " = " << B * Value << "\n";
    } while (tolower(Prompt<string>("Continue? (y/n)")[0]) == 'y');
    return 0;
}

/*

This is a c-string
Enter first string: hello
Enter second string: ll
binary op:
A + B = helloll
A - B = heo
single op:
!A  = olleh
A-- = hello
A++ = elloh
A   = hello
--A = elloh
++A = hello
A   = hello
Enter an unsigned int for mul and div: 2
B / 2 = l
B * 2 = llll
Continue? (y/n)

 */
