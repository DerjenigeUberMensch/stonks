#include "changeFiles.cpp"
#include "math.cpp"
#include "stringManipulation.cpp"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
class Stock {
public:
  //std::vector<float> prices; //<<Feature Not implemented Yet>>
  std::string SYMBOL; //not const but essential a const value
  std::string stock_name;
  float volatility; // <- <<changing volatility not implemented yet>>
  const int INITIAL_PRICE = rng(1, 1500);
  //int stability = rng(-1, 2); // <- <<not implemented yet>>
  // -1 unstable 0 regular_stock 1 semi-stable 2 stable
  /* Stability: Stock will never drop below initial_price +- x (where x is some
  range) Note we generally dont want rangeless stocks as c++ likes to just drop
  the stocks to 0 and not climb back up
  */
  const float MIN_PRICE = (INITIAL_PRICE * rng(1, 10) * .01) + rng(1, 3); //second rng is so we dont get small nums
  const float MAX_PRICE = INITIAL_PRICE * rng(1, 10) * 10;
  float current_price = INITIAL_PRICE;
  //void log_old_price(){prices.push_back(current_price);}; //<<Feature Not implemented Yet>>
  float stockOwned = 0; // I regret naming it this
};
class Player {
  public:
  const int initial_balance = rng(5000,1000000); //Number doesnt matter
  float current_balance = initial_balance;
};

void update_stock_price(Stock &stock){
  //generate new stock price
  int rise_or_dip = rng(-1, 1);
  if(stock.current_price < stock.MIN_PRICE){
    stock.current_price += ((stock.current_price * stock.volatility * rise_or_dip) +(stock.current_price * stock.volatility * .25));
  }else if(stock.current_price >= stock.MAX_PRICE){
    stock.current_price = stock.current_price - (stock.current_price * stock.volatility * rise_or_dip *rise_or_dip)+ (stock.current_price * stock.volatility * .1);
  }else{
    stock.current_price += (stock.current_price * stock.volatility * rise_or_dip);
  }
  //stock.log_old_price(); //<<Feature Not implemented Yet>>
}


//Data collection
void intiate_player(Player &player){
  std::string file_name = "player_data.txt";
  std::ifstream file(file_name);
  if(!file.is_open()){
    newFile(file_name); //check if file exists if not create it
  }else if(!is_empty(file)){
    std::vector<std::string> player_data = readFile(file_name);
    player.current_balance = std::stof(player_data[0]);
  }
  file.close();
}
void get_logged_stock_prices(Stock &stock){
  std::string file_name = stock.SYMBOL + ".txt";
  std::ifstream file(file_name);
  if (!is_empty(file)) {
    std::vector<std::string> current_price_temp = readFile(file_name);
    try{
      for(int i = 0;i < current_price_temp.size();++i){
        std::stof(current_price_temp[i]);
      }
      stock.current_price = std::stof(current_price_temp[current_price_temp.size() - 1]);
    }
    catch(...){/**/}; // we dont want to do anything if user tampers with the files cause it will just default to stock.current_price
  }
  file.close();
}

std::string display_stock_price(const Stock &STOCK, int cout_spaces = 10){
  int stock_length = STOCK.stock_name.length();
  cout_spaces = cout_spaces - stock_length;
  if(cout_spaces <= 0 ){
    return " ";
  }
  std::string spaces(cout_spaces, ' ');
  std::string display = STOCK.stock_name+':'+spaces+std::to_string(STOCK.current_price);
  return display;
}
void display_stocks_info(const std::vector<Stock> &stocks, const int SPACES_AFTER_STOCK = 20){
  for(int i = 0;i < stocks.size();i++){
    const std::string DISPLAY_STOCK_PRICE = display_stock_price(stocks[i], SPACES_AFTER_STOCK);
    std::cout << DISPLAY_STOCK_PRICE; // display stock and price
    const int ORDER_COUT_SPACES = 20 - (std::to_string(stocks[i].current_price).length());
    std::string spaces(ORDER_COUT_SPACES, ' ');
    std::cout << spaces << "Order: " << stocks[i].SYMBOL << '\n'; //display order
  }
}
void log_stock_info(const std::vector<Stock> stocks){
  for(int i = 0; i < stocks.size();++i){
    writeToFile((stocks[i].SYMBOL + ".txt"), std::to_string(stocks[i].current_price), "overwrite");
  }
}
void log_player_data(const Player player){
  writeToFile("player_data.txt", std::to_string(player.current_balance), "overwrite");
}
void log_owned_stocks(const std::vector<Stock> &stocks){
  writeToFile("owned_stocks","ab", "truncate"); //a doesnt mean anything hear just place_holder text
  for(int i = 0; i < stocks.size();++i){
    writeToFile("owned_stocks", (stocks[i].SYMBOL +'='+ std::to_string(stocks[i].stockOwned)));
  }
}
void display_portfolio(const Player &player, const std::vector<Stock> stocks = {}){
  std::vector<Stock> stocksOwned = {};
  for(int i = 0 ;i < stocks.size();++i){
    if(stocks[i].stockOwned > 0){
      stocksOwned.push_back(stocks[i]);
    }
  }
  clear_screen();
  std::cout << "PORTFOLIO STATS\n";
  std::cout << "Current Balance: " << std::to_string(player.current_balance) << '\n';

  if(stocksOwned.size() > 0){
    std::cout << "Current stock holding(s)\n";
  }else{
    std::cout << "You currently have no holdings";
  }
  for(int i = 0;i < stocksOwned.size();++i){
    std::cout << stocksOwned[i].SYMBOL << " stocks: " << stocksOwned[i].stockOwned << '\n';
  }
  std::cout << '\n';
  std::string input;
  getline(std::cin, input);
  if(input.empty()){
    return;
  }
  return;
}
void user_help(){
  std::cout << "'help' commands";
  std::cout << "Enter(key)  - Skip 1 interation" << '\n';
  std::cout << "INT(number) - Number of iterations to skip, note: depending on proccessing power you may not be able to run all of these iterations in a non infinite time." << '\n';
  std::cout << "Order name  - View a stock in more detail" << '\n';
  std::cout << "View        - View portfolio." << '\n';
  std::cout << "Exit        - Exit application and log progress" << '\n';
  std::cout << "Save        - Saves current game" << '\n';
  //std::cout << "" << '\n';
  print("PLEASE NOTE: Not all of these are functional or even factual so please be patient", 10);
}
int main() {
  Player player;
  std::vector<Stock> stocks;
  Stock NVIDIA;
  NVIDIA.volatility = 0.07;
  NVIDIA.SYMBOL = "NVDA";
  NVIDIA.stock_name = "NVIDIA";
  stocks.push_back(NVIDIA);

  Stock Microsoft;
  Microsoft.volatility = .03;
  Microsoft.SYMBOL = "MCSFT";
  Microsoft.stock_name = "Microsoft";
  stocks.push_back(Microsoft);

  Stock Apple;
  Apple.volatility = .027;
  Apple.SYMBOL = "APP";
  Apple.stock_name = "Apple";
  stocks.push_back(Apple);

  Stock Oracle;
  Oracle.volatility = 0.06;
  Oracle.SYMBOL = "ORC";
  Oracle.stock_name = "Oracle";
  stocks.push_back(Oracle);

  Stock Tesla;
  Tesla.volatility = .16;
  Tesla.SYMBOL = "TSL";
  Tesla.stock_name = "Tesla";
  stocks.push_back(Tesla);

  Stock Ford;
  Ford.volatility = .039;
  Ford.SYMBOL = "FORD";
  Ford.stock_name = "Ford";
  stocks.push_back(Ford);

  Stock Intel;
  Intel.volatility = .017;
  Intel.SYMBOL = "INT";
  Intel.stock_name = "Intel";
  stocks.push_back(Intel);

  Stock Google;
  Google.volatility = .05;
  Google.SYMBOL = "ABC";
  Google.stock_name = "Google";
  stocks.push_back(Google);

  Stock Fazbear;
  Fazbear.volatility = .03;
  Fazbear.SYMBOL = "FAZ";
  Fazbear.stock_name = "Freddy Fazbears";
  stocks.push_back(Fazbear);

  Stock Coca_cola;
  Coca_cola.volatility = .04;
  Coca_cola.SYMBOL = "COLA";
  Coca_cola.stock_name = "Coca Cola Co";
  stocks.push_back(Coca_cola);

  Stock Pepsi_co;
  Pepsi_co.volatility = .04;
  Pepsi_co.SYMBOL = "PEP";
  Pepsi_co.stock_name = "Pepsi Co";
  stocks.push_back(Pepsi_co);

  Stock S_and_P;
  S_and_P.volatility = .05;
  S_and_P.SYMBOL = "S&P";
  S_and_P.stock_name = "S&P500";
  stocks.push_back(S_and_P);

  Stock Dow_jones;
  Dow_jones.volatility = .07;
  Dow_jones.SYMBOL = "DWJ";
  Dow_jones.stock_name = "Dow Jones";
  stocks.push_back(Dow_jones);

  Stock Oil;
  Oil.volatility = .10;
  Oil.SYMBOL = "OIL";
  Oil.stock_name = "Oil";
  stocks.push_back(Oil);

  Stock Gold;
  Gold.volatility = .15;
  Gold.SYMBOL = "GOLD";
  Gold.stock_name = "Gold";
  stocks.push_back(Gold);

  Stock Uranium;
  Uranium.volatility = .17;
  Uranium.SYMBOL = "URM";
  Uranium.stock_name = "Uranium";
  stocks.push_back(Uranium);
  
  Stock Nat_gas; // Natural Gas
  Nat_gas.volatility = .15;
  Nat_gas.SYMBOL = "GAS";
  Nat_gas.stock_name = "Natural Gas";
  stocks.push_back(Nat_gas);

  Stock Ethanol;
  Ethanol.volatility = .20;
  Ethanol.SYMBOL = "ETHN";
  Ethanol.stock_name = "Ethanol";
  stocks.push_back(Ethanol);

  //initiate stuff
  intiate_player(player);
  for(int i = 0;i < stocks.size();++i){
    get_logged_stock_prices(stocks[i]);
  }
  /*finish later something to get stock owned from previous isntance*/
  std::vector<std::string> initiate_stocks_owned_player = readFile("owned_stocks");
  for(int i = 0;i < initiate_stocks_owned_player.size();++i){

  }
  while(true){
    std::cout << "StockMarket" << '\n';
    std::cout << "type 'exit' to exit." << '\n';
    std::cout << "Current Balance: $" << player.current_balance << "\n\n";
    display_stocks_info(stocks);

    std::string user_symbol;
    std::cout << "What would you like to do?\n";
    std::cout << "type 'help' for more info about commands" << '\n';
    getline(std::cin, user_symbol);
    if(lower(user_symbol) == "help"){
      user_help();
      std::cin >> user_symbol;
    }
    /*  if(something_to_detect_enter){
          for(int x = 0;x < stocks.size();++x){
            update_stock_price(stocks[x]);
          }
        }
    */
    //Save game
    if(user_symbol.empty()){ //If user presses enter on no input
      for(int x = 0;x < stocks.size();++x){
          update_stock_price(stocks[x]);
      }
      clear_screen();
      continue;
    }
    if(lower(user_symbol) == "save"){
      print("Saving...");
      log_player_data(player);
      log_stock_info(stocks);
      log_owned_stocks(stocks);
      std::this_thread::sleep_for(std::chrono::seconds(1)); // <- the illusion of doing stuff
      print("Game Saved!");
      std::this_thread::sleep_for(std::chrono::seconds(1)); // <- so user can read text
      clear_screen();
      continue;
    }
    if(lower(user_symbol) == "exit"){
      log_stock_info(stocks);
      log_player_data(player);
      log_owned_stocks(stocks);
      print("exiting...");
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      break;
    }else if(isInteger(user_symbol)){
      //implement somthing to detect non digit input
      for(int i = 0; i < std::stoi(user_symbol);++i){
        for(int x = 0;x < stocks.size();++x){
          update_stock_price(stocks[x]);
        }
      }
    }else if(lower(user_symbol) == "view"){
      display_portfolio(player, stocks);
    }
    else if(!user_symbol.empty()){
      for(int i = 0;i < stocks.size();++i){
        if(stocks[i].SYMBOL == user_symbol){
          std::cout << "Stock Found!\n";

          std::string purchaseOption;
          std::cout << "What would you like to do sell or buy?: ";
          std::cin >> purchaseOption;
          if(lower(purchaseOption) == "sell"){
            while(true){
              std::string sellAmount;
              std::cout << "How many would you like to Sell?: ";
              std::cin >> sellAmount;
              if(isNumber(sellAmount) && stocks[i].stockOwned != 0){
                  float amount = std::stof(sellAmount);
                  if(amount > stocks[i].stockOwned){amount = stocks[i].stockOwned;}
                  player.current_balance += amount * stocks[i].current_price;
                  stocks[i].stockOwned-=amount;
                  break;
                  }
              else if(lower(sellAmount) == "max"){
                float ownedStock = stocks[i].stockOwned; //prevent or create bugs idk.
                stocks[i].stockOwned = 0;
                player.current_balance += (ownedStock * stocks[i].current_price);
                break;
              }
              else if(lower(sellAmount) == "exit")
                {break;}
              else if(stocks[i].stockOwned == 0)
                {std::cout << "You dont own any of this stock.\n";}
              else if(!isNumber(sellAmount))
                {std::cout << "That is not a number/cannot compute try again.\n";}
            }
          }else if(lower(purchaseOption) == "buy"){
            while(true){
                std::string purchaseAmount;
                std::cout << "How many would you like to purchase?: ";
                std::cin >> purchaseAmount;
                if(isNumber(purchaseAmount) && player.current_balance - std::stof(purchaseAmount) * stocks[i].current_price >= 0){
                  float amount = std::stof(purchaseAmount);
                  player.current_balance -= amount * stocks[i].current_price;
                  stocks[i].stockOwned+=amount;
                  break;
                  }
                else if(isNumber(purchaseAmount))
                  {std::cout << "You dont have the capitol to do that right now.\n";}
                else if(lower(purchaseAmount) == "max"){
                  float amount = player.current_balance/stocks[i].current_price;
                  player.current_balance -= amount*stocks[i].current_price;
                  stocks[i].stockOwned += amount;
                  break;
                }
                else if(lower(purchaseAmount) == "exit")
                  {break;}
                else if(!isNumber(purchaseAmount))
                  {std::cout << "That is not a number/cannot compute try again.\n";}
              }
            }
          }
        }
      }
      clear_screen();
    }
  
  return 0;
}
/*
  std::stoi    // string to int
  std::stol    // string to long
  std::stoll   // string to long long
  std::stof    // string to float
  std::stod    // string to double
  std::stold   // string to long double
*/
