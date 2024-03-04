#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <sstream>
#include <string.h>
#include <bits/stdc++.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>



class BankAccount{
    std::string accountNumber;
    float balance;
public:
    BankAccount(){
    }

    BankAccount(std::string accountNumber, float balance = 0)
    :accountNumber(accountNumber),balance(balance)
    {
    }

    std::string getAccountNumber()
    {
	    return this->accountNumber;
    }
};

//INTERFACE - gränssnitt "standard"
class IAccountStorage {
public:    
    virtual void addAccount(BankAccount account) = 0;
	virtual BankAccount *findAccount(std::string accountNumber) = 0;        
};

class Bank
{
private:
	IAccountStorage * accountStorage;
public:
	Bank(IAccountStorage *storage):accountStorage(storage){

    }
	bool addAccount(std::string accountNumber){
        //validate
        //if something (accountNumber) return false
        accountStorage->addAccount(accountNumber);
        return true;
    }
	BankAccount *getAccount(std::string accountNumber){
        return accountStorage->findAccount(accountNumber);
    }
};


/*
class MapAccountStorage: public IAccountStorage{
    std::map<std::string,BankAccount> accounts;
public:
    void addAccount(BankAccount account) override{
        accounts[account.getAccountNumber()] = account;
    }
    BankAccount *findAccount(std::string accountNumber){
        return &(accounts[accountNumber]);
    }

};*/

class DistributedVectorAccountStorage : public IAccountStorage{
    std::vector<BankAccount> accountsStartingWith0;
    std::vector<BankAccount> accountsStartingWith1;
    std::vector<BankAccount> accountsStartingWith2;
    std::vector<BankAccount> accountsStartingWith3;
    std::vector<BankAccount> accountsStartingWith4;
    std::vector<BankAccount> accountsStartingWith5;
    std::vector<BankAccount> accountsStartingWith6;
    std::vector<BankAccount> accountsStartingWith7;
    std::vector<BankAccount> accountsStartingWith8;
    std::vector<BankAccount> accountsStartingWith9;
    std::vector<BankAccount> empty;

    std::vector<BankAccount> &getRef(char firstChar){

        switch(firstChar){
            case '0':
                return accountsStartingWith0;
            case '1':
                return  accountsStartingWith1;
            case '2':
                return accountsStartingWith2;
            case '3':
                return accountsStartingWith3;
            case '4':
                return accountsStartingWith4;
            case '5':
                return  accountsStartingWith5;
            case '6':
                return accountsStartingWith6;
            case '7':
                return accountsStartingWith7;
            case '8':
                return accountsStartingWith8;
            case '9':
                return  accountsStartingWith9;
        }
        return empty;
    }


public:

    void addAccount(BankAccount account) override{
        std::vector<BankAccount> &ref = getRef(account.getAccountNumber()[0]);
        ref.push_back(account);
    }
    BankAccount *findAccount(std::string accountNumber){
        std::vector<BankAccount> &ref = getRef(accountNumber[0]);
        BankAccount *ret = nullptr;
        for(BankAccount &account : ref){
            if(account.getAccountNumber() == accountNumber ){
                return &account;                                        
            }
        }
        return ret;
    }
};

/*
class VectorAccountStorage: public IAccountStorage{
        std::vector<BankAccount> accounts;
public:
    void addAccount(BankAccount account) override{
        accounts.push_back(account);
    }

    BankAccount *findAccount(std::string accountNumber){
        BankAccount *ret = nullptr;
        for(BankAccount &account : accounts){
            if(account.getAccountNumber() == accountNumber ){
                return &account;                                        
            }
        }
        return ret;
    }
};
*/

bool myCmp (BankAccount& b1, BankAccount& b2)
    {
        return b1.getAccountNumber() < b2.getAccountNumber();
    }

class BinarySearchStorage : public IAccountStorage
{
    std::vector<BankAccount> accounts; 
    public:
    void addAccount(BankAccount account) override{
        accounts.push_back(account);
    }
    

   
    
    void sortVector(std::vector<BankAccount> &accounts)
    {
        std::sort(accounts.begin(),accounts.end(),myCmp);
    }

    void shuffleAlgorithm(){
        int n = accounts.size();
        srand(time(NULL));
        for(int i = n - 1; i > 0; i--){
            int j = rand() % (i + 1);
            std::swap(accounts[i], accounts[j]);
        }
    }

    BankAccount *findAccount(std::string accountNumber) 
    {
        /*
        for(BankAccount &account : accounts){
            std:: cout << account.getAccountNumber() << std::endl;
        }
        */

        /* Sorterar vektorn i nummerordning från lågt till högt!
            Men borde den vara här? Sorteringen kommer köras varje gång vi söker på något
            Pros: Om vi inte vet om vectorn blivit förändrad kan de va bra att den ligger här
            Cons: kostar oss tid/batteri ? kan skrivas som en egen funktion som körs varje gång vectorn förändras? */

        auto startTime = std::chrono::high_resolution_clock::now(); 
        sortVector(accounts); 
        auto endTime = std::chrono::high_resolution_clock::now();
        std::cout << "Sorting vector to took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

        /*
        for(BankAccount &account : accounts){
            std:: cout << account.getAccountNumber() << std::endl;
        } 
       */


        BankAccount *ret = nullptr;

        int start = 0;
        int end = accounts.size()-1;
        
        while (start <= end)
        {
            //std::cout << start << "Start  end" << end << std::endl;
            
            int current = start + (end - start)/2; // calculates were the middle of our searchparamater is!
            //std::cout << "Vad vi letar efter" << accounts[current].getAccountNumber() << std::endl;
            //std::cout << "Vad vi letar med "<< accountNumber << std::endl;
            // str1.compare(str2) == 0
            if(accounts[current].getAccountNumber().compare(accountNumber) == 0)
            {
                std::cout << accounts[current].getAccountNumber() << " was found at index: " << current << std::endl;
                return &accounts[current];
                // Here we can get informaion: It exists, what index its found("current"), mby usefull for future
            }
            if (accounts[current].getAccountNumber().compare(accountNumber) < 0) // if our search-element(accountNumber) is greater then ignore left half
            {
                start = current + 1;
            }
            //if (accounts[current].getAccountNumber() < accountNumber) // if our search-element(accountNumber) is smaller then ignore righ half half
            else
            {
                end = current -1; 
            }
        }
        return ret;

    /*
    if (std::binary_search(accounts.begin(), accounts.end(), accountNumber)) {
        std::cout << accountNumber << " found in the vector.\n";
    } else {
        std::cout << accountNumber << " not found in the vector.\n";
    }
    


        for(BankAccount &account : accounts){
            if(account.getAccountNumber() == accountNumber ){
                return &account;                                        
            }
        }
        return ret;
        */
    }
};

class InitializeAccountsZeroPadding
{
private:
public:
    void InitializeZeroPadding(int AntalAccounts, Bank bank, std::string& sFirst, std::string& sLast)
    {  
        for(int i = 0;i < AntalAccounts; i++)
        {
            std::string accountNumber =  std::to_string(i);
            std::stringstream padding; 

            for (int i = 0; i < 10-accountNumber.length(); i++) // relative to size of accountnumber so if padding needs to be 10, change "6" depending on size
            {
                padding << "0";
            }
            padding << accountNumber;
            padding >> accountNumber;
        
            // std::cout << accountNumber << std::endl; // Check om padding funkat
            if(i == 0){
                sFirst = accountNumber;
            }
            if(i == AntalAccounts-1){
                sLast = accountNumber;
            }
            bank.addAccount(accountNumber);
        }
    };

    

    void InitializeRandomZeroPadding(int AntalAccounts, Bank bank, std::string& sFirst, std::string& sLast)
    {  

        srand((unsigned int)time(NULL));
        int number_to_use = 0;
        int numbers_used[AntalAccounts];
        bool unique = false;

        for(int i = 0;i < AntalAccounts; i++)
        {
            do
            {
                number_to_use = (rand() % AntalAccounts) +1;
                unique = true;
                for (int j = 0; j < i; j++)
                {
                    if(numbers_used[j] == number_to_use)
                    {
                        unique = false;
                    }
                }
            } while (!unique);
            // NOT VERY EFFECTIIVE WHEN GOING HIGHER


            numbers_used[i] = number_to_use;

            std::string accountNumber =  std::to_string(number_to_use);
            std::stringstream padding; 

            for (int i = 0; i < 6-accountNumber.length(); i++)  // relative to size of accountnumber so if padding needs to be 10, change "6" depending on size
            {
                padding << "0";
            }
            padding << accountNumber;
            padding >> accountNumber;
        
            // std::cout << "Index: " << i << "We find: " << accountNumber << std::endl; // Check om padding funkat + random ordning
            if(i == 0){
                sFirst = accountNumber;
            }
            if(i == AntalAccounts-1){
                sLast = accountNumber;
            }
            bank.addAccount(accountNumber);
        }
    };
};


template<typename T, unsigned N>  //deklarerar

class Queue
{
private:
    static T staticArrayQue[N];
    int queCheck = 0;
public:
    
    void pushToQue(T input)
    {
        if (queCheck >= N)
        {
            std::cout << "> ERROR < Que is full!" << std::endl;
        }
        else
        {
            Queue<T,N>::staticArrayQue[queCheck] = input;
            queCheck ++; 
        }
    }   
};

template<typename T, unsigned N> T Queue<T,N>::staticArrayQue[N];
// StatiArrayQue behöver defineras(görs inte i klassen) 
// Står:I Classen QUEUE av typen T(finns array av typen T med Index N) är samma som StarricArrayQue




int main(int, char**){

    //VectorAccountStorage storage;
    //DistributedVectorAccountStorage storage;
    BinarySearchStorage storage;
    //MapAccountStorage storage;
    Bank bank(&storage);

    const int AntalAccounts = 1000000;


    std::string sFirst = ""; 
    std::string sLast = ""; 
    std::string sNotFound = "notfound"; 

    std::cout << "INITIALIZE: " << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();

    InitializeAccountsZeroPadding Test;
    //Test.InitializeRandomZeroPadding(AntalAccounts, bank, sFirst, sLast);
    Test.InitializeZeroPadding(AntalAccounts, bank, sFirst, sLast);
    storage.shuffleAlgorithm();
    //for (auto e : storage.accounts) std::cout << e.getAccountNumber() << std::endl;
    std::cout << "sFirst: " << sFirst << ", sLast: " << sLast << std::endl;
    auto endTime = std::chrono::high_resolution_clock::now();
    std::cout << "INIT Took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now(); 
    BankAccount *p = bank.getAccount(sFirst);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sLast);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << p->getAccountNumber() << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    startTime = std::chrono::high_resolution_clock::now();
    p = bank.getAccount(sNotFound);
    endTime = std::chrono::high_resolution_clock::now();
    std::cout << "NOT FOUND" << " took: " << std::chrono::duration_cast<std::chrono::nanoseconds>(endTime    - startTime).count() << " milliseconds" << std::endl;

    

    Queue<int,10>kö1;

    
    for (int i = 0; i < 11; i++)
    {
        kö1.pushToQue(12);
    }
    

}