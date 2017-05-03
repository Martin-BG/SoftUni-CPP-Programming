#include<string>
#include<iostream>
#include<set>
#include<iomanip>
#include<limits>

int main()
{
    std::set<int> uniqueDNS;
    std::set<int>::iterator it;
    std::set<unsigned short> uniqueDNSshort;
    std::set<unsigned short>::iterator it2;

    int num;

    char next[6] = {};

    while(std::cin.get(next, 6, '.'))
    {
        if (std::cin.eof())
        {
            break;
        }

        num = std::stoi(next, nullptr, 16);

        if (num <= USHRT_MAX)
        {
            it2 = uniqueDNSshort.find(num);

            if (it2 != uniqueDNSshort.end())
            {
                uniqueDNSshort.erase(it2);
            }
            else
            {
                uniqueDNSshort.insert(num);
            }
        }
        else
        {
            it = uniqueDNS.find(num);

            if (it != uniqueDNS.end())
            {
                uniqueDNS.erase(it);
            }
            else
            {
                uniqueDNS.insert(num);
            }
        }
    }

    std::cout << std::setw(5) << std::setfill('0') << std::hex;

    if(uniqueDNS.begin() != uniqueDNS.end())
    {
        std::cout << (*(uniqueDNS.begin()));
    }
    else
    {
        std::cout << (*(uniqueDNSshort.begin()));
    }

    return 0;
}
