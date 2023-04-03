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
int main() {
  Stock NVIDIA;
  NVIDIA.volatility = 0.07;
  NVIDIA.symbol = "NVDA";
  NVIDIA.stock_name = "NVIDIA";
  

  Stock Microsoft;
  Microsoft.volatility = .03;
  Microsoft.symbol = "MCSFT";
  Microsoft.stock_name = "Microsoft";
  

  Stock Apple;
  Apple.volatility = .027;
  Apple.symbol = "APP";
  Apple.stock_name = "Apple";
  

  Stock Oracle;
  Oracle.volatility = 0.06;
  Oracle.symbol = "ORC";
  Oracle.stock_name = "Oracle";
  

  Stock Tesla;
  Tesla.volatility = .16;
  Tesla.symbol = "TSL";
  Tesla.stock_name = "Tesla";
  

  Stock Ford;
  Ford.volatility = .039;
  Ford.symbol = "FORD";
  Ford.stock_name = "Ford";
  

  Stock Intel;
  Intel.volatility = .017;
  Intel.symbol = "INT";
  Intel.stock_name = "Intel";
  

  Stock Google;
  Google.volatility = .05;
  Google.symbol = "ABC";
  Google.stock_name = "Google";
  

  Stock Fazbear;
  Fazbear.volatility = .03;
  Fazbear.symbol = "FAZ";
  Fazbear.stock_name = "Freddy Fazbears";
  

  Stock Coca_cola;
  Coca_cola.volatility = .04;
  Coca_cola.symbol = "COLA";
  Coca_cola.stock_name = "Coca Cola Co";
  

  Stock Pepsi_co;
  Pepsi_co.volatility = .04;
  Pepsi_co.symbol = "PEP";
  Pepsi_co.stock_name = "Pepsi Co";
  

  Stock S_and_P;
  S_and_P.volatility = .05;
  S_and_P.symbol = "S&P";
  S_and_P.stock_name = "S&P500";
  

  Stock Dow_jones;
  Dow_jones.volatility = .07;
  Dow_jones.symbol = "DWJ";
  Dow_jones.stock_name = "Dow Jones";
  

  Stock Oil;
  Oil.volatility = .10;
  Oil.symbol = "OIL";
  Oil.stock_name = "Oil";
  

  Stock Gold;
  Gold.volatility = .15;
  Gold.symbol = "GOLD";
  Gold.stock_name = "Gold";
  

  Stock Uranium;
  Uranium.volatility = .17;
  Uranium.symbol = "URM";
  Uranium.stock_name = "Uranium";
  
  
  Stock Natural_Gas;
  Natural_Gas.volatility = .15;
  Natural_Gas.symbol = "GAS";
  Natural_Gas.stock_name = "Natural Gas";
  

  Stock Ethanol;
  Ethanol.volatility = .20;
  Ethanol.symbol = "ETHN";
  Ethanol.stock_name = "Ethanol";
  
  new_stock_price(Ethanol);

  int some_varaible;
  std::cout << "StockMarket" << "\n";
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
  std::cout << Natural_Gas.stock_name  << ": " << Natural_Gas.current_price<< "\n";
  std::cout << Uranium.stock_name      << ": " << Uranium.current_price  << "\n";
  std::cout << Oil.stock_name          << ": " << Oil.current_price      << "\n";  
  std::cout << Ethanol.stock_name      << ": " << Ethanol.current_price  << "\n";


  std::cin >> some_varaible;
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
