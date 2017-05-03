#include<iostream>
#include<set>
#include<iomanip>
#include<bitset>

class NumShort
{
private:
    std::bitset<14> num;
public:
    NumShort(const int & number) :
        num(std::bitset<14>(number)) {}

    std::bitset<14> getNum() const
    {
        return this->num;
    }

    friend bool operator< (const NumShort &n1, const NumShort &n2);
};

bool operator< (const NumShort &n1, const NumShort &n2)
{
    return n1.getNum().to_ulong() < n2.getNum().to_ulong();
}

class Num
{
private:
    std::bitset<20> num;
public:
    Num(const int & number) :
        num(std::bitset<20>(number)) {}

    std::bitset<20> getNum() const
    {
        return this->num;
    }

    friend bool operator< (const Num &n1, const Num &n2);
};

bool operator< (const Num &n1, const Num &n2)
{
    return n1.getNum().to_ulong() < n2.getNum().to_ulong();
}

int main()
{
    std::set<Num > uniqueDNA;
    std::set<Num >::iterator it;
    std::set<NumShort> uniqueDNAshort;
    std::set<NumShort>::iterator it2;

    int num;

    char next[6] = {};

    while(std::cin.get(next, 6, '.'))
    {
        if (std::cin.eof())
        {
            break;
        }

        num = std::stoi(next, nullptr, 16);

        if (num <= 16383)
        {
            it2 = uniqueDNAshort.find(NumShort(num));

            if (it2 != uniqueDNAshort.end())
            {
                uniqueDNAshort.erase(it2);
            }
            else
            {
                uniqueDNAshort.insert(NumShort(num));
            }
        }
        else
        {
            it = uniqueDNA.find(Num(num));

            if (it != uniqueDNA.end())
            {
                uniqueDNA.erase(it);
            }
            else
            {
                uniqueDNA.insert(Num(num));
            }
        }
    }

    std::cout << std::setw(5) << std::setfill('0') << std::hex;

    if(uniqueDNA.begin() != uniqueDNA.end())
    {
        std::cout << (*(uniqueDNA.begin())).getNum().to_ulong();
    }
    else
    {
        std::cout << (*(uniqueDNAshort.begin())).getNum().to_ulong();
    }

    return 0;
}
