#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include <cstdlib> // std::exit()
#include <ctime>

#include "misc.cpp"
#include "STOCKS.cpp"
#include "PLAYER.cpp"


std::string display_stock_price(Stock &STOCK, int cout_spaces = 10){
  int stock_length = (STOCK.get_stock_name()).length();
  cout_spaces = cout_spaces - stock_length;
  if(cout_spaces <= 0 ){
    return " ";
  }
  std::string spaces(cout_spaces, ' ');
  std::string display = STOCK.get_stock_name()+':'+spaces+std::to_string(STOCK.get_current_price());
  return display;
}
void display_stocks_info(std::vector<Stock> &stocks, const int SPACES_AFTER_STOCK = 20){
  for(int i = 0;i < stocks.size();i++){
    const std::string DISPLAY_STOCK_PRICE = display_stock_price(stocks[i], SPACES_AFTER_STOCK);
    std::cout << DISPLAY_STOCK_PRICE; // display stock and price
    const int ORDER_COUT_SPACES = 20 - (std::to_string(stocks[i].get_current_price()).length());
    std::string spaces(ORDER_COUT_SPACES, ' ');
    std::cout << spaces << "Order: " << stocks[i].get_symbol() << '\n'; //display order
  }
}
void display_portfolio(Player &player, std::vector<Stock> stocks = {}){
  std::vector<Stock> stocksOwned = {};
  for(int i = 0 ;i < stocks.size();++i){
    if(stocks[i].get_stock_owned() > 0){
      stocksOwned.push_back(stocks[i]);
    }
  }
  
  system("cls"); //windows terminal needs this for some reason 
  std::cout << "PORTFOLIO STATS\n";
  std::cout << "Current Balance: " << std::to_string(player.get_balance()) << '\n';

  if(stocksOwned.size() > 0){
    std::cout << "Current stock holding(s)\n";
  }else{
    std::cout << "You currently have no holdings";
  }
  for(int i = 0;i < stocksOwned.size();++i){
    std::cout << stocksOwned[i].get_symbol() << " stocks: " << stocksOwned[i].get_stock_owned() << '\n';
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
  std::cout << "number      - Number of iterations to skip, note: depending on proccessing power you may not be able to run all of these iterations in a non infinite time." << '\n';
  std::cout << "Order name  - View a stock in more detail" << '\n';
  std::cout << "View        - View portfolio." << '\n';
  std::cout << "Exit        - Exit application and log progress" << '\n';
  std::cout << "Save        - Saves current game" << '\n';
  //std::cout << "" << '\n';
  print("PLEASE NOTE: Not all of these are functional or even factual so please be patient", 10);
  std::string wait;
  getline(std::cin, wait);
}

void save_game(Player player, std::vector<Stock> stocks){
	print("Saving...");
  player.log_player_data();
  for(int i = 0; i < stocks.size();++i){
    stocks[i].log_owned_stock();
    stocks[i].log_current_price();
  }
  std::this_thread::sleep_for(std::chrono::seconds(1)); // <- the illusion of doing stuff ISSUE CURRENT TREAD IS FUNCTION
  print("Game Saved!");
  std::this_thread::sleep_for(std::chrono::seconds(1)); // <- so user can read text
  system("cls");
}

/*Do tasks functions*/
float purchase_stock(Player &player, Stock &stockPick){
	while(true){
      std::string purchaseAmount;
      std::cout << "How many would you like to purchase?: ";
      getline(std::cin, purchaseAmount);
      if(isNumber(purchaseAmount) && player.get_balance() - std::stof(purchaseAmount) * stockPick.get_current_price() >= 0){
        float amount = std::stof(purchaseAmount);
        player.set_balance(player.get_balance() - amount * stockPick.get_current_price());
        return stockPick.get_stock_owned() + amount;
      }
      else if(isNumber(purchaseAmount))
          {std::cout << "You dont have the capitol to do that right now.\n";}
      else if(lower(purchaseAmount) == "max"){
          float amount = player.get_balance()/stockPick.get_current_price();
          player.set_balance(player.get_balance() - amount*stockPick.get_current_price());
          return stockPick.get_stock_owned() + amount;
          }
      else if(lower(purchaseAmount) == "exit")
          {system("cls");break;}
      else
          {std::cout << "That is not a number/cannot compute try again.\n";}
    }
    return stockPick.get_stock_owned(); //failsafe
}
float sell_stock(Player &player,Stock &stockPick){
	while(true)
  {
    std::string sellAmount;
    std::cout << "How many would you like to Sell?: ";
    std::cin >> sellAmount;
    if(isNumber(sellAmount) && stockPick.get_stock_owned() != 0){
      float amount = std::stof(sellAmount);
      if(amount > stockPick.get_stock_owned())
        {amount = stockPick.get_stock_owned();}
			player.set_balance(player.get_balance() + amount * stockPick.get_current_price());
      return stockPick.get_stock_owned() - amount;
    }else if(lower(sellAmount) == "max"){
      float ownedStock = stockPick.get_stock_owned(); //prevent or create bugs idk.
      player.set_balance(player.get_balance() + (ownedStock * stockPick.get_current_price()));
      return 0;
		 }else if(lower(sellAmount) == "exit")
        {system("cls"); break;}
    else if(stockPick.get_stock_owned() == 0)
        {std::cout << "You dont own any of this stock.\n";}
    else
        {std::cout << "That is not a number/cannot compute try again.\n";}
  }
  return stockPick.get_stock_owned(); //failsafe
}

//Decided what to do with input (once of the functions above)
int get_stock_pick_postion(std::vector<Stock> &stocks){
	std::string stockPick;
	while(true){
		std::cout << "What stock order: ";
		getline(std::cin, stockPick);
		if(!stockPick.empty()){
			for(int i = 0; i < stocks.size();++i){
				if(lower(stocks[i].get_symbol()) == lower(stockPick)){return i;}
			}
			std::cout << "No item found in system try again.\n";
		}
	}
}
void manage_user_input(Player &player, std::vector<Stock> &stocks){
	std::cout << "What would you like to do?: ";
	std::string consoleInput;
	getline(std::cin, consoleInput);
	if(consoleInput.empty()){return;} //if user presses enter or something we just skip to next iterations
	consoleInput = lower(consoleInput);

	if(consoleInput == "buy"){;
    int stockPosition = get_stock_pick_postion(stocks);
    stocks[stockPosition].set_stock_owned(purchase_stock(player, stocks[stockPosition]));
	}else if(consoleInput == "sell"){

    int stockPosition = get_stock_pick_postion(stocks);
    stocks[stockPosition].set_stock_owned(sell_stock(player, stocks[stockPosition]));
	}else if(consoleInput == "view" || consoleInput == "portfolio"){
		display_portfolio(player, stocks);
  }else if(isInteger(consoleInput)){
    float iterations = std::stoi(consoleInput);
    for(int i = 0; i < iterations;++i){
      for(int x = 0;x < stocks.size();++x){
        stocks[x].update_stock_price();
      }
    }
	}else if(consoleInput == "save"){
		save_game(player, stocks); //ISSUE CURRENT TREAD IS FUNCTION
	}else if(consoleInput == "exit"){
		save_game(player, stocks); //ISSUE CURRENT TREAD IS FUNCTION
		std::exit(0);		   //kill thread or something to exit
	}else if(consoleInput == "help"){
		user_help();
	}
}
int main() {
  Player player;
  Stock NVIDIA("NVIDIA","NVDA",           .07);
  Stock Microsoft("Microsoft", "MCSFT",   .03);
  Stock Apple("Apple", "APP",             .027);
  Stock Oracle("Oracle", "ORC",           .06);
  Stock Tesla("Tesla", "TSL",             .16);
  Stock Ford("Ford", "FORD",              .039);
  Stock Intel("Intel", "INT",             .017);
  Stock Google("Google", "ABC",           .05);
  Stock Fazbear("Freddy Fazbears", "FAZ", .03);
  Stock Coca_cola("Coca Cola Co", "COLA", .04);
  Stock Pepsi_co("Pepsi Co", "PEPSI",     .04);
  Stock S_and_P("S&P500", "S&P",          .05);
  Stock Dow_jones("Dow Jones", "DWJ",     .07);
  Stock Oil("Oil", "OIL",                 .10);
  Stock Gold("Gold", "GOLD",              .15);
  Stock Uranium("Uranium", "URM",         .17);
  Stock Nat_gas("Natural Gas", "GAS",     .15);
  Stock Ethanol("Ethanol", "ETHN",        .20);

  //initiate stuff
  player.initiate_player();
  for(int i = 0; i < Stock::stocks.size();++i){
    Stock::stocks[i].set_logged_price();
    std::cout << Stock::stocks[i].get_symbol() << '\n';
  }
  
  /*Get logged stocks*/
  std::vector<std::string> initiate_stocks_owned_player = readFile("owned_stocks");
  
  char indexChar = '=';
  for(int i = 0;i < initiate_stocks_owned_player.size();++i){
    int index = initiate_stocks_owned_player[i].find(indexChar) + 1; //+1 so we dont get the '='
    Stock::stocks[i].set_stock_owned(std::stof(initiate_stocks_owned_player[i].substr(index)));
  }
  while(true){
    std::cout << "StockMarket" << '\n';
    std::cout << "type 'exit' to exit." << '\n';
    std::cout << "Current Balance: $" << player.get_balance() << "\n\n";
    display_stocks_info(Stock::stocks);
    manage_user_input(player, Stock::stocks);

    for(int x = 0;x < Stock::stocks.size();++x){
        Stock::stocks[x].update_stock_price();
    }
    system("cls");
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