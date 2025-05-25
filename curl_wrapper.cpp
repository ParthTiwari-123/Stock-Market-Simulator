#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "json.hpp"
#include "curl_wrapper.h"

using json = nlohmann::json;

// Callback function to handle data received from the CURL request
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch stock data
json fetchStockData(const std::string& stockSymbol, const std::string& apiKey) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    json stockData;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + stockSymbol + "&interval=5min&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Reduced verbosity settings in fetchStockData
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);  // Set verbose to 0 to reduce logs
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // For debugging: Disable SSL peer verification (can remove once working)

        // Display essential connection message only
        std::cout << "Fetching data for " << stockSymbol << "..." << std::endl;

        // Perform the CURL request
        res = curl_easy_perform(curl);

        // Check for successful response
        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        if (res == CURLE_OK && response_code == 200) {
            stockData = json::parse(readBuffer);
        } else {
            std::cerr << "Failed to fetch data for " << stockSymbol << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return stockData;
}

// Function to extract latest stock details
void extractStockDetails(const json& stockData) {
    if (stockData.contains("Meta Data") && stockData["Meta Data"].contains("3. Last Refreshed")) {
        std::string latestTime = stockData["Meta Data"]["3. Last Refreshed"];
        auto latestData = stockData["Time Series (5min)"][latestTime];

        // Extract stock details
        std::string stockName = stockData["Meta Data"]["2. Symbol"];
        double openPrice = std::stod(latestData["1. open"].get<std::string>());
        double highPrice = std::stod(latestData["2. high"].get<std::string>());
        double lowPrice = std::stod(latestData["3. low"].get<std::string>());
        double closePrice = std::stod(latestData["4. close"].get<std::string>());
        double volume = std::stod(latestData["5. volume"].get<std::string>());

        // Display extracted stock details
        std::cout << "Stock: " << stockName << std::endl;
        std::cout << "Latest Time: " << latestTime << std::endl;
        std::cout << "Open Price: " << openPrice << std::endl;
        std::cout << "High Price: " << highPrice << std::endl;
        std::cout << "Low Price: " << lowPrice << std::endl;
        std::cout << "Close Price: " << closePrice << std::endl;
        std::cout << "Volume: " << volume << std::endl;
    }
    else {
        std::cerr << "Invalid stock data received." << std::endl;
    }
}

// Function to display close prices at given intervals
void displayRecentClosePrices(const json& stockData, const std::string& symbol, const std::vector<int>& intervals) {
    if (!stockData.contains("Time Series (5min)")) {
        std::cerr << "No time series data available for " << symbol << std::endl;
        return;
    }

    auto& timeSeries = stockData["Time Series (5min)"];
    int intervalIndex = 0;
    int elapsedTime = 0;

    std::cout << "Closing prices for " << symbol << " at specified intervals:\n";

    for (const auto& [time, data] : timeSeries.items()) {
        if (elapsedTime == intervals[intervalIndex]) {
            double closePrice = std::stod(data["4. close"].get<std::string>());
            std::cout << " - " << elapsedTime << " minutes ago: " << closePrice << std::endl;

            intervalIndex++;
            if (intervalIndex >= intervals.size()) break;
        }
        elapsedTime += 5;
    }

    if (intervalIndex < intervals.size()) {
        std::cerr << "Warning: Not enough data to display all intervals for " << symbol << std::endl;
    }
}

/*
#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include "curl_wrapper.h"
#include "json.hpp" // Ensure JSON library is properly linked

using json = nlohmann::json;

// Arrays to store stock data
double open_price[10];
std::string symbol[10];
int quantity[10]; // Stores volume for each stock

// Function to write curl data to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Fetch stock data using curl
json fetchStockData(const std::string& symbol, const std::string& apiKey) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Construct the API URL
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + symbol + "&interval=5min&apikey=" + apiKey;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Disable SSL verification

        // Perform the request
        res = curl_easy_perform(curl);
        
        // Check for errors in the request
        if (res != CURLE_OK) {
            std::cerr << "Curl error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Curl initialization failed." << std::endl;
    }
    curl_global_cleanup();

    // Check if the response is empty
    if (readBuffer.empty()) {
        std::cerr << "Error: Empty response from the API." << std::endl;
        return json(); // Return an empty json object
    }

    // Attempt to parse the JSON response
    try {
        json stockData = json::parse(readBuffer);
        return stockData;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << std::endl;
        return json(); // Return an empty json object on error
    }
}


// Populate stock data arrays
void populateStockData(const std::vector<std::string>& symbols, const std::string& apiKey) {
    for (int i = 0; i < symbols.size(); ++i) {
        json stockData = fetchStockData(symbols[i], apiKey);

        // Parse and assign values to arrays based on JSON response structure
        std::string latestTime = stockData["Meta Data"]["3. Last Refreshed"].get<std::string>();
        open_price[i] = stockData["Time Series (5min)"][latestTime]["1. open"].get<double>();
        quantity[i] = stockData["Time Series (5min)"][latestTime]["5. volume"].get<int>();
        symbol[i] = symbols[i];
    }
}

// Extract and display main stock details
void extractStockDetails(const json& stockData) {
    std::string lastRefreshed = stockData["Meta Data"]["3. Last Refreshed"];
    std::cout << "Last Refreshed: " << lastRefreshed << std::endl;

    auto latestData = stockData["Time Series (5min)"][lastRefreshed];
    std::cout << "Open: " << latestData["1. open"] << ", High: " << latestData["2. high"]
              << ", Low: " << latestData["3. low"] << ", Close: " << latestData["4. close"]
              << ", Volume: " << latestData["5. volume"] << std::endl;
}

// Display recent close prices for specified intervals
void displayRecentClosePrices(const json& stockData, const std::string& symbol, const std::vector<int>& intervals) {
    std::cout << "Recent close prices for " << symbol << ":" << std::endl;
    for (int interval : intervals) {
        std::string timeKey = stockData["Meta Data"]["3. Last Refreshed"];
        std::cout << interval << " minutes ago: Close Price = " << stockData["Time Series (5min)"][timeKey]["4. close"] << std::endl;
    }
}

// Return pointers to arrays for use in main_trial.cpp
void getStockArrays(double*& openPrices, std::string*& stockSymbols, int*& stockQuantities) {
    openPrices = open_price;
    stockSymbols = symbol;
    stockQuantities = quantity;
}
*/