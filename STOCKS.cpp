/*
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include <random>
*/
bool is_empty(std::ifstream& pFile){
    return pFile.peek() == std::ifstream::traits_type::eof();
}
class Stock {
    private:
        //int stability = rng(-1, 2); // <- <<not implemented yet>>
        // -1 unstable 0 regular_stock 1 semi-stable 2 stable
        /* Stability: Stock will never drop below initial_price +- x (where x is some
        range) Note we generally dont want rangeless stocks as c++ likes to just drop
        the stocks to 0 and not climb back up
        */
        const int INITIAL_PRICE = rng(1, 1500);
        const float MIN_PRICE = (INITIAL_PRICE * rng(1, 10) * .01) + rng(1, 3); //second rng is so we dont get small nums
        float MAX_PRICE = INITIAL_PRICE * rng(1, 10) * 10;
        float current_price;
        float volatility;
        float stockAmountOwned = 0;
        std::string SYMBOL;
        std::string stock_name;
    public:
        inline static std::vector<Stock> stocks;
        Stock(const std::string name, const std::string SETSYMBOL, float stockVolatility){
            stock_name = name;
            volatility = stockVolatility;
            current_price = INITIAL_PRICE;
            SYMBOL = SETSYMBOL;
            //void log_old_price(){prices.push_back(current_price);}; //<<Feature Not implemented Yet>>
            float stockOwned = 0; // I regret naming it this
            stocks.push_back(*this);
        }
        std::string get_stock_name(){return stock_name;}
        std::string get_symbol()    {return SYMBOL;}
        float get_volatility()      {return volatility;}
        float get_current_price()   {return current_price;}
        float get_stock_owned()     {return stockAmountOwned;}
        void  set_current_price(float price)     {current_price = price;}
        void  set_stock_owned(float stockAmount) {stockAmountOwned = stockAmount;}
        std::vector<Stock> access_stocks(){return stocks;}
        void update_stock_price(){
            //generate new stock price
            int rise_or_dip = rng(-1, 1);
            if(current_price < MIN_PRICE){
                current_price += ((current_price * volatility * rise_or_dip) +(current_price * volatility * .25));
            }else if(current_price >= MAX_PRICE){
                current_price = current_price - (current_price * volatility * rise_or_dip *rise_or_dip)+ (current_price * volatility * .1);
            }else{
                current_price += (current_price * volatility * rise_or_dip);
            }
            //log_old_price(); //<<Feature Not implemented Yet>>
        }
        void log_current_price(){
            const std::string file_name = SYMBOL + ".txt";
            std::ofstream file;
            file.open(file_name, std::ios::trunc);
            file << std::to_string(current_price);
        }
        void log_owned_stock(){
            const std::string file_name = "owned_stocks.txt";
            std::ofstream writeFile;
            writeFile.open(file_name);
            writeFile << (SYMBOL + '=' + std::to_string(stockAmountOwned));
            writeFile.close();
        }
        void set_logged_price(){
            std::string file_name = SYMBOL + ".txt";
            std::ifstream file(file_name);
            if (!is_empty(file)) {
                std::string current_price_temp;
                getline(file, current_price_temp);
                try{
                    current_price = std::stof(current_price_temp);
                }
                catch(...){/**/}; // we dont want to do anything if user tampers with the files cause it will just default to stock.current_price
            }
        }

};