//curl_wrapper.h
#ifndef CURL_WRAPPER_H
#define CURL_WRAPPER_H

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

json fetchStockData(const std::string& symbol, const std::string& apiKey);
void extractStockDetails(const json& stockData);
void displayRecentClosePrices(const json& stockData, const std::string& symbol, const std::vector<int>& intervals);

#endif // CURL_WRAPPER_H

/*
#ifndef CURL_WRAPPER_H
#define CURL_WRAPPER_H

#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

// Prototypes for stock data functions
json fetchStockData(const std::string& symbol, const std::string& apiKey);
void populateStockData(const std::vector<std::string>& symbols, const std::string& apiKey);
void getStockArrays(double*& openPrices, std::string*& stockSymbols, int*& stockQuantities);
void extractStockDetails(const json& stockData);
void displayRecentClosePrices(const json& stockData, const std::string& symbol, const std::vector<int>& intervals);

#endif // CURL_WRAPPER_H
*/