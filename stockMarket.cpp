#include "changeFiles.cpp"
#include "math.cpp"
#include "stringManipulation.cpp"
#include <chrono>
#include <cmath> // floor division
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class Stock {
public:    
  std::string symbol;
  std::string stock_name;
  float volatility;
  const int initial_price = rng(1, 1500);
  int stability; // -1 unstable 0 regular_stock 1 semi-stable 2 stable
  /* Stability: Stock will never drop below initial_price +- x (where x is some
  range) Note we generally dont want rangeless stocks as c++ likes to just drop
  the stocks to 0 and not climb back up
  */
  const float min_price = (initial_price * rng(1, 10) * .01) + rng(1, 3); //second rng is so we dont get small nums
  const float max_price = initial_price * rng(1, 10) * 10;
  float current_price = initial_price;

protected:
  int bitBurnerVol = 2;
  std::string bitBurnerSym = "w0r1d_d43m0n";
  std::string stockName = "BitBurner";
};
void update_stock_price(Stock &stock){
  //generate new stock price
  int rise_or_dip = rng(-1, 1);
  if(stock.current_price < stock.min_price){
    stock.current_price = stock.current_price + ((stock.current_price * stock.volatility * rise_or_dip) +(stock.current_price * stock.volatility * .25));
  }else if(stock.current_price >= stock.max_price){
    stock.current_price = stock.current_price - (stock.current_price * stock.volatility * rise_or_dip *rise_or_dip);
  }else{
    stock.current_price = stock.current_price + (stock.current_price * stock.volatility * rise_or_dip);
  }
}
void new_stock_price(Stock &stock, const int numOfIterations = 1) {
  std::string file_name = stock.symbol + ".txt";
  std::ifstream file(file_name);
  if (is_empty(file)) {
  } else {
    std::vector<std::string> current_price_temp = readFile(file_name);
    stock.current_price = std::stof(current_price_temp[current_price_temp.size() - 1]);
  }
  file.close();
  if(numOfIterations == 1){
    update_stock_price(stock);
    //log stock price
    writeToFile(file_name, std::to_string(stock.current_price));
  }else{
    for (int i = 0; i < numOfIterations; ++i) {
      update_stock_price(stock);
      writeToFile(file_name, std::to_string(stock.current_price));
    }
  }

}
std::string display_stock_price(const Stock stock, int cout_spaces = 10){
  int stock_length = stock.stock_name.length();
  cout_spaces = cout_spaces - stock_length;
  if(cout_spaces <= 0 ){
    return " ";
  }
  std::string spaces(cout_spaces, ' ');
  std::string display = stock.stock_name+':'+spaces+std::to_string(stock.current_price);
  return display;
}
int main() {
  std::vector<Stock> stocks;
  Stock NVIDIA;
  NVIDIA.volatility = 0.07;
  NVIDIA.symbol = "NVDA";
  NVIDIA.stock_name = "NVIDIA";
  stocks.push_back(NVIDIA);

  Stock Microsoft;
  Microsoft.volatility = .03;
  Microsoft.symbol = "MCSFT";
  Microsoft.stock_name = "Microsoft";
  stocks.push_back(Microsoft);

  Stock Apple;
  Apple.volatility = .027;
  Apple.symbol = "APP";
  Apple.stock_name = "Apple";
  stocks.push_back(Apple);

  Stock Oracle;
  Oracle.volatility = 0.06;
  Oracle.symbol = "ORC";
  Oracle.stock_name = "Oracle";
  stocks.push_back(Oracle);

  Stock Tesla;
  Tesla.volatility = .16;
  Tesla.symbol = "TSL";
  Tesla.stock_name = "Tesla";
  stocks.push_back(Tesla);

  Stock Ford;
  Ford.volatility = .039;
  Ford.symbol = "FORD";
  Ford.stock_name = "Ford";
  stocks.push_back(Ford);

  Stock Intel;
  Intel.volatility = .017;
  Intel.symbol = "INT";
  Intel.stock_name = "Intel";
  stocks.push_back(Intel);

  Stock Google;
  Google.volatility = .05;
  Google.symbol = "ABC";
  Google.stock_name = "Google";
  stocks.push_back(Google);

  Stock Fazbear;
  Fazbear.volatility = .03;
  Fazbear.symbol = "FAZ";
  Fazbear.stock_name = "Freddy Fazbears";
  stocks.push_back(Fazbear);

  Stock Coca_cola;
  Coca_cola.volatility = .04;
  Coca_cola.symbol = "COLA";
  Coca_cola.stock_name = "Coca Cola Co";
  stocks.push_back(Coca_cola);

  Stock Pepsi_co;
  Pepsi_co.volatility = .04;
  Pepsi_co.symbol = "PEP";
  Pepsi_co.stock_name = "Pepsi Co";
  stocks.push_back(Pepsi_co);

  Stock S_and_P;
  S_and_P.volatility = .05;
  S_and_P.symbol = "S&P";
  S_and_P.stock_name = "S&P500";
  stocks.push_back(S_and_P);

  Stock Dow_jones;
  Dow_jones.volatility = .07;
  Dow_jones.symbol = "DWJ";
  Dow_jones.stock_name = "Dow Jones";
  stocks.push_back(Dow_jones);

  Stock Oil;
  Oil.volatility = .10;
  Oil.symbol = "OIL";
  Oil.stock_name = "Oil";
  stocks.push_back(Oil);

  Stock Gold;
  Gold.volatility = .15;
  Gold.symbol = "GOLD";
  Gold.stock_name = "Gold";
  stocks.push_back(Gold);

  Stock Uranium;
  Uranium.volatility = .17;
  Uranium.symbol = "URM";
  Uranium.stock_name = "Uranium";
  stocks.push_back(Uranium);
  
  Stock Nat_gas; // Natural Gas
  Nat_gas.volatility = .15;
  Nat_gas.symbol = "GAS";
  Nat_gas.stock_name = "Natural Gas";
  stocks.push_back(Nat_gas);

  Stock Ethanol;
  Ethanol.volatility = .20;
  Ethanol.symbol = "ETHN";
  Ethanol.stock_name = "Ethanol";
  stocks.push_back(Ethanol);

  std::cout << "StockMarket" << "\n";
  for(int i = 0;i < stocks.size();++i){
    std::cout << display_stock_price(stocks[i], 20) << "\n";
  }
  
  /*
  std::cout << NVIDIA.stock_name       << ": " << NVIDIA.current_price   << "\n";
  std::cout << Google.stock_name       << ": " << Google.current_price   << "\n";
  std::cout << Oracle.stock_name       << ": " << Oracle.current_price   << "\n";
  std::cout << Intel.stock_name        << ": " << Intel.current_price    << "\n";
  std::cout << Microsoft.stock_name    << ": " << Microsoft.current_price<< "\n";
  std::cout << Tesla.stock_name        << ": " << Tesla.current_price    << "\n";
  std::cout << Ford.stock_name         << ": " << Ford.current_price     << "\n";
  std::cout << Fazbear.stock_name      << ": " << Fazbear.current_price  << "\n";
  std::cout << Coca_cola.stock_name    << ": " << Coca_cola.current_price<< "\n";
  std::cout << Pepsi_co.stock_name     << ": " << Pepsi_co.current_price << "\n";
  std::cout << Dow_jones.stock_name    << ": " << Dow_jones.current_price<< "\n";
  std::cout << S_and_P.stock_name      << ": " << S_and_P.current_price  << "\n";
  std::cout << Nat_gas.stock_name      << ": " << Nat_gas.current_price  << "\n";
  std::cout << Uranium.stock_name      << ": " << Uranium.current_price  << "\n";
  std::cout << Oil.stock_name          << ": " << Oil.current_price      << "\n";  
  std::cout << Ethanol.stock_name      << ": " << Ethanol.current_price  << "\n";
  */
  //writeToFile("stocks.txt",)
  return 0;
}
// std::cout << << "\n";
// Know issues: using larger numbers leads to price dropping to 0
/*
  std::stoi    // string to int
  std::stol    // string to long
  std::stoll   // string to long long
  std::stof    // string to float
  std::stod    // string to double
  std::stold   // string to long double
*/

/*
  std::ifstream file("nums.txt");
  if (is_empty(file)) {
  } else {
    std::vector<std::string> current_price_temp = readFile("nums.txt");
    Ethanol.current_price =
  std::stof(current_price_temp[current_price_temp.size() - 1]);
    // std::cout << std::to_string(Ethanol.current_price);
  }
  file.close();
  // Ethanol.current_price = current_price_temp.size() - 1;

  for (int i = 0; i < 100; ++i) {
    Ethanol.current_price =
        stock_new_price(Ethanol.current_price, Ethanol.volatility);
    // std::cout << Ethanol.current_price << std::endl;
    writeToFile("nums.txt", std::to_string(Ethanol.current_price));
  }
  */
