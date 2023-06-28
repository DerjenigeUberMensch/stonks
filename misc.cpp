auto getRandomSeed() 
    -> std::seed_seq
{
    // This gets a source of actual, honest-to-god randomness
    std::random_device source;

    // Here, we fill an array of random data from the source
    unsigned int random_data[10];
    for(auto& elem : random_data) {
        elem = source(); 
    }

    // this creates the random seed sequence out of the random data
    return std::seed_seq(random_data + 0, random_data + 10); 
}
int rng(int min, int max) {
    // Making rng static ensures that it stays the same
    // Between different invocations of the function
    static auto seed = getRandomSeed(); 
    static std::default_random_engine rng(seed);

    std::uniform_int_distribution<int> dist(min, max); 
    return dist(rng); 
}
float rng(float min, float max) {
    // Making rng static ensures that it stays the same
    // Between different invocations of the function
    static auto seed = getRandomSeed(); 
    static std::default_random_engine rng(seed);

    std::uniform_real_distribution<float> dist(min, max); 
    return dist(rng); 
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