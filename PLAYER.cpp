class Player {
  private:
    const int initial_balance = rng(5000,1000000); //Number doesnt matter
    float current_balance = initial_balance;
  public:
    float get_initial_balance(){return initial_balance;}
    float get_balance()        {return current_balance;}
    void  set_balance(float newBalance){current_balance = newBalance;}
    void  initiate_player(const std::string file_name = "player_data.txt"){
        std::ifstream file(file_name);
        if(!file.is_open()){
            newFile(file_name); //check if file exists if not create it
        }else if(!is_empty(file)){
            std::vector<std::string> player_data = readFile(file_name);
            current_balance = std::stof(player_data[0]);
        }
        file.close();
    }
    void  log_player_data(){
        writeToFile("player_data.txt", std::to_string(current_balance), "overwrite");
    }

};
