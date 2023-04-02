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
  std::string symbol;
  std::string stock_name;
  float volatility;
  const int initial_price = rng(1, 1500);
  int stability; // -1 unstable 0 regular_stock 1 semi-stable 2 stable
  /* Stability: Stock will never drop below initial_price +- x (where x is some range)
  Note we generally dont want rangeless stocks as c++ likes to just drop the stocks to 0 and not climb back up
  */
  const int min_price = ;
  const int max_price = ;
  float current_price = initial_price;

protected:
  int bitBurnerVol = 2;
  std::string bitBurnerSym = "w0r1d_d43m0n";
  std::string stockName = "BitBurner";
};
float stock_new_price(float current_price, float volatility) {
  int rise_or_dip = rng(-1, 1);
  current_price = current_price + ((current_price * volatility * rise_or_dip) +
                                   (current_price * volatility * .05));
  if (current_price < 0.1) {
    return current_price + (current_price * volatility * 1.5);
  } else {
    return current_price;
  }
  return current_price;
}
void new_stock_price(Stock stock) {
  std::string file_name = stock.symbol + ".txt";
  std::ifstream file(file_name);
  if (is_empty(file)) {
  } else {
    std::vector<std::string> current_price_temp = readFile(file_name);
    stock.current_price = std::stof(current_price_temp[current_price_temp.size() - 1]);
  }
  file.close();

  for (int i = 0; i < 100; ++i) {
    stock.current_price =
    stock_new_price(stock.current_price, stock.volatility);
    writeToFile(file_name, std::to_string(stock.current_price));
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

  Stock Ford_Motor_Company;
  Ford_Motor_Company.volatility = .039;
  Ford_Motor_Company.symbol = "FORD";
  Ford_Motor_Company.stock_name = "Ford.";

  Stock Intel_Corporation;
  Intel_Corporation.volatility = .017;
  Intel_Corporation.symbol = "INT";
  Intel_Corporation.stock_name = "Intel.";

  Stock Google;
  Google.volatility = .05;
  Google.symbol = "ABC";
  Google.stock_name = "Google.";

  Stock Fazbear_entertainment;
  Fazbear_entertainment.volatility = .03;
  Fazbear_entertainment.symbol = "FAZ";
  Fazbear_entertainment.stock_name = "Freddy Fazbears.";

  Stock Coca_cola;
  Coca_cola.volatility = .04;
  Coca_cola.symbol = "COLA";
  Coca_cola.stock_name = "Coca Cola Co.";

  Stock Pepsi_co;
  Pepsi_co.volatility = .04;
  Pepsi_co.symbol = "PEP";
  Pepsi_co.stock_name = "Pepsi Co.";

  Stock S_and_P;
  S_and_P.volatility = .05;
  S_and_P.symbol = "S&P";
  S_and_P.stock_name = "S&P500.";

  Stock Dow_jones;
  Dow_jones.volatility = .07;
  Dow_jones.symbol = "DWJ";
  Dow_jones.stock_name = "Dow_Jones.";

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
  Natural_Gas.stock_name = "Natural_Gas";

  Stock Ethanol;
  Ethanol.volatility = .20;
  Ethanol.symbol = "ETHN";
  Ethanol.stock_name = "Ethanol";
  new_stock_price(Ethanol);
  /*
  std::ifstream file("nums.txt");
  if (is_empty(file)) {
  } else {
    std::vector<std::string> current_price_temp = readFile("nums.txt");
    Ethanol.current_price = std::stof(current_price_temp[current_price_temp.size() - 1]);
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
  return 0;
}
// Know issues: using larger numbers leads to price dropping to 0
/*
  std::stoi    // string to int
  std::stol    // string to long
  std::stoll   // string to long long
  std::stof    // string to float
  std::stod    // string to double
  std::stold   // string to long double
*/