#include <vector>
#include <fstream>
#include <algorithm>
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
void writeToFile(std::string file, std::string data , std::string mode = "append"){
    if(mode == "overwrite"){
        std::ofstream writeFile;
        writeFile.open(file, std::ios::trunc);
        writeFile << data << std::endl;
        writeFile.close();
    }else if(mode == "truncate"){
        std::ofstream writeFile;
        writeFile.open(file, std::fstream::out | std::fstream::trunc);
        writeFile.close();
    }else{
        std::ofstream writeFile;
        writeFile.open(file, std::ios::app);
        writeFile << data << std::endl;
        writeFile.close();
    }
}
std::vector<std::string> removeDataCopy(std::string file){
    std::vector<std::string> data = readFile(file);
    for(int i =0; i < data.size();++i){
        auto dataFind = std::find(data.begin() + i + 1, data.end(), data[i]);
        if(dataFind != data.end()){
            data.erase(dataFind);
        }
    }
    return data;
}
void newFile(std::string fileName){
    std::ofstream file(fileName);
    file.close();
}
bool is_empty(std::ifstream& pFile){
    return pFile.peek() == std::ifstream::traits_type::eof();
}
int get_size(std::string file_name){
    std::ifstream inFile(file_name);
    int count = std::count(std::istreambuf_iterator<char>(inFile),
                std::istreambuf_iterator<char>(), '\n');
    inFile.close();
    return count;
}
