# 📈 Stock Market Simulator

A C++-based educational tool that simulates stock market trading to help users understand the dynamics of buying/selling stocks, portfolio management, price fluctuations, and predictions — all in a virtual, risk-free environment.

---

## 🔍 Project Overview

This simulator offers a real-time trading experience using virtual credits. Users can:
- Buy and sell predefined stocks.
- View and manage their portfolios.
- Track stock price fluctuations.
- Predict future stock prices using data structures.
- Simulate real-world market behavior — all without financial risk.

---

## 🎯 Features

- **Buy/Sell Operations**: Trade stocks using virtual credits.
- **Portfolio Management**: Track your holdings, evaluate performance.
- **Price Prediction**: Forecast minimum and maximum price ranges using BST.
- **Fluctuation Tracker**: Monitor real-time stock price changes using Queues.
- **User Accounts**: Sign up and log in to save your balance and trades.

---

## 🧠 Data Structures Used

| Feature | Data Structure | Purpose |
|--------|----------------|---------|
| Trading | Linked List, Vector | Efficient access to stocks and trades |
| Prediction | Binary Search Tree (BST) | Fast retrieval of predicted price ranges |
| Fluctuation | Queue | Real-time monitoring of price changes |
| Portfolio | Linked List | Track and update stock holdings |

---

## ⚙️ Technologies & Libraries

- **C++**
- **cURL** for API access (Alpha Vantage)
- **nlohmann/json** for parsing JSON data
- **File I/O** for storing user and trade data

---

## 🏁 Getting Started

### 🔧 Prerequisites
- g++
- libcurl
- `nlohmann/json.hpp`
- Alpha Vantage API Key (replace in `Main_trial.cpp`)

### 🛠️ Compile

```bash
g++ simulator.cpp linkedlistfunction.cpp -o simulator -DMAIN_FUNCTION_LINKEDLIST
g++ fluctuator.cpp -o fluctuator
g++ predictor.cpp -o predictor
g++ main_trial.cpp curl_wrapper.cpp -lcurl -o fetch
