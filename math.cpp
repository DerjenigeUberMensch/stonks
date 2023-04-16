#include <random>
template <typename Type>
auto rng(Type min, Type max) {
    std::random_device rd;
    std::uniform_int_distribution<Type> dist(min,max);
    return dist(rd);
}
inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

   char * p;
   strtol(s.c_str(), &p, 10);

   return (*p == 0);
}
bool isNumber(std::string number){
    for(int i = 0;i < number.length();++i){
        if(isdigit(number[i]) != true && number[i] != '.'){return false;}
    }
    return true;
}
/*
#include <random>
int rng(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}
*/
