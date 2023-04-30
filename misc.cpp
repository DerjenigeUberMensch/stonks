int rng(int min, int max) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(min,max);
    return dist(rd);
}
float rng(float min, float max) {
    std::random_device rd;
    std::uniform_real_distribution<float> dist(min,max);
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

void print(std::string string, int sleep_time = 50) {
  for (int i = 0; i < string.size(); ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    std::cout << string[i];
  }
  std::cout << std::endl;
}
std::string lower(std::string string) {
  std::transform(string.begin(), string.end(), string.begin(), ::tolower);
  return string;
}

std::vector<std::string> readFile(std::string file){
    std::string lineData;
    std::vector<std::string> readData = {};
    std::ifstream fileData(file);
    while (getline (fileData, lineData)) {
        readData.push_back(lineData);
        //std::cout <<  lineData << std::endl;
    }
    return readData;
}