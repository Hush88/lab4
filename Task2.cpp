#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Wallet {
private:
    string name;
    string currency;
    double balance;
    bool isOpen;
public:
    Wallet(string name, string currency, double balance, bool isOpen) {
        this->name = name;
        this->currency = currency;
        this->balance = balance;
        this->isOpen = isOpen;
    }

    string getName() const {
        return name;
    }

    string getCurrency() const {
        return currency;
    }

    double getBalance() const {
        return balance;
    }

    bool getIsOpen() const {
        return isOpen;
    }

    void setIsOpen(bool isOpen) {
        this->isOpen = isOpen;
    }

    void addBalance(double amount) {
        balance += amount;
    }

    void subtractBalance(double amount) {
        balance -= amount;
    }
};

class CryptoExchange {

public:
    vector<Wallet*> wallets;

    CryptoExchange() {}

    void addWallet(Wallet* wallet) {
        wallets.push_back(wallet);
    }

    void removeWallet(string name) {
        for (int i = 0; i < wallets.size(); i++) {
            if (wallets[i]->getName() == name) {
                wallets.erase(wallets.begin() + i);
                break;
            }
        }
    }

    void sortWallets() {
        sort(wallets.begin(), wallets.end(), [](Wallet* a, Wallet* b) { return a->getBalance() > b->getBalance(); });
    }

    double getTotalBalance() const {
        double total = 0;
        for (int i = 0; i < wallets.size(); i++) {
            if (wallets[i]->getIsOpen()) {
                total += wallets[i]->getBalance();
            }
        }
        return total;
    }

    double getDailyGrowth() const {
        double total = 0;
        for (int i = 0; i < wallets.size(); i++) {
            if (wallets[i]->getIsOpen()) {
                double balance = wallets[i]->getBalance();
                double growth = (rand() % 11) / 100.0; // simulate daily growth with random percentage
                total += balance * growth;
            }
        }
        return total;
    }

    double getWeeklyGrowth() const {
        double total = 0;
        for (int i = 0; i < wallets.size(); i++) {
            if (wallets[i]->getIsOpen()) {
                double balance = wallets[i]->getBalance();
                double growth = (rand() % 31) / 100.0; // simulate weekly growth with random percentage
                total += balance * growth;
            }
        }
        return total;
    }

    double getMonthlyGrowth() const {
        double total = 0;
        for (int i = 0; i < wallets.size(); i++) {
            if (wallets[i]->getIsOpen()) {
                double balance = wallets[i]->getBalance();
                double growth = (rand() % 101) / 100.0; // simulate monthly growth with random percentage
                total += balance * growth;
            }
        }
        return total;
    }
};

int main() {
    CryptoExchange exchange;

    // create wallets
    exchange.addWallet(new Wallet("Bitcoin", "BTC", 10.0, true));
    exchange.addWallet(new Wallet("Ethereum", "ETH", 20.0, true));
    exchange.addWallet(new Wallet("Litecoin", "LTC", 30.0, true));
    exchange.addWallet(new Wallet("Bitcoin Cash", "BCH", 15.0, true));
    exchange.addWallet(new Wallet("Cardano", "ADA", 5.0, true));
    exchange.addWallet(new Wallet("Dogecoin", "DOGE", 25.0, true));

    // add fiat wallet
    Wallet* fiat = new Wallet("USD", "USD", 1000.0, true);
    exchange.addWallet(fiat);

    // close some wallets
    exchange.removeWallet("Litecoin");
    exchange.removeWallet("Cardano");

    // display total balance
    cout << "Total balance: " << exchange.getTotalBalance() << " USD" << endl;

    // display daily growth
    double dailyGrowth = exchange.getDailyGrowth();
    cout << "Daily growth: " << dailyGrowth << " USD" << endl;

    // display weekly growth
    double weeklyGrowth = exchange.getWeeklyGrowth();
    cout << "Weekly growth: " << weeklyGrowth << " USD" << endl;

    // display monthly growth
    double monthlyGrowth = exchange.getMonthlyGrowth();
    cout << "Monthly growth: " << monthlyGrowth << " USD" << endl;

    // sort wallets by balance
    exchange.sortWallets();

    // display sorted wallets
    cout << "Sorted wallets:" << endl;
    for (int i = 0; i < exchange.wallets.size(); i++) {
        Wallet* wallet = exchange.wallets[i];
        cout << wallet->getName() << " (" << wallet->getCurrency() << "): " << wallet->getBalance() << " " << wallet->getCurrency() << endl;
    }

    // close fiat wallet
    fiat->setIsOpen(false);

    return 0;
}
