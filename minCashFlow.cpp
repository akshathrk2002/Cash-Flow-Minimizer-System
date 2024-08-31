#include <bits/stdc++.h>
using namespace std;

class Bank
{
public:
    string name;
    int netBalance;
    set<string> paymentTypes;
};

int findMinBalanceIndex(Bank bankList[], int totalBanks)
{
    int minBalance = INT_MAX, minIndex = -1;
    for (int i = 0; i < totalBanks; i++)
    {
        if (bankList[i].netBalance == 0)
            continue;

        if (bankList[i].netBalance < minBalance)
        {
            minIndex = i;
            minBalance = bankList[i].netBalance;
        }
    }
    return minIndex;
}

int findMaxBalanceIndex(Bank bankList[], int totalBanks)
{
    int maxBalance = INT_MIN, maxIndex = -1;
    for (int i = 0; i < totalBanks; i++)
    {
        if (bankList[i].netBalance == 0)
            continue;

        if (bankList[i].netBalance > maxBalance)
        {
            maxIndex = i;
            maxBalance = bankList[i].netBalance;
        }
    }
    return maxIndex;
}

pair<int, string> findBestMatchIndex(Bank bankList[], int totalBanks, int minIndex, Bank allBanks[], int maxPaymentTypes)
{
    int bestMatch = INT_MIN;
    int bestMatchIndex = -1;
    string commonType;

    for (int i = 0; i < totalBanks; i++)
    {
        if (bankList[i].netBalance <= 0)
            continue;

        vector<string> commonTypes(maxPaymentTypes);
        auto it = set_intersection(bankList[minIndex].paymentTypes.begin(), bankList[minIndex].paymentTypes.end(),
                                   bankList[i].paymentTypes.begin(), bankList[i].paymentTypes.end(), commonTypes.begin());

        if ((it - commonTypes.begin()) != 0 && bestMatch < bankList[i].netBalance)
        {
            bestMatch = bankList[i].netBalance;
            bestMatchIndex = i;
            commonType = *(commonTypes.begin());
        }
    }

    return make_pair(bestMatchIndex, commonType);
}

void displayTransactions(vector<vector<pair<int, string>>> transactionsGraph, int totalBanks, Bank allBanks[])
{
    cout << "\nHere are the minimized transactions:\n\n";
    for (int i = 0; i < totalBanks; i++)
    {
        for (int j = 0; j < totalBanks; j++)
        {
            if (i == j)
                continue;

            if (transactionsGraph[i][j].first != 0 && transactionsGraph[j][i].first != 0)
            {
                if (transactionsGraph[i][j].first == transactionsGraph[j][i].first)
                {
                    transactionsGraph[i][j].first = 0;
                    transactionsGraph[j][i].first = 0;
                }
                else if (transactionsGraph[i][j].first > transactionsGraph[j][i].first)
                {
                    transactionsGraph[i][j].first -= transactionsGraph[j][i].first;
                    transactionsGraph[j][i].first = 0;
                    cout << allBanks[i].name << " pays Rs " << transactionsGraph[i][j].first << " to " << allBanks[j].name << " via " << transactionsGraph[i][j].second << endl;
                }
                else
                {
                    transactionsGraph[j][i].first -= transactionsGraph[i][j].first;
                    transactionsGraph[i][j].first = 0;
                    cout << allBanks[j].name << " pays Rs " << transactionsGraph[j][i].first << " to " << allBanks[i].name << " via " << transactionsGraph[j][i].second << endl;
                }
            }
            else if (transactionsGraph[i][j].first != 0)
            {
                cout << allBanks[i].name << " pays Rs " << transactionsGraph[i][j].first << " to " << allBanks[j].name << " via " << transactionsGraph[i][j].second << endl;
            }
            else if (transactionsGraph[j][i].first != 0)
            {
                cout << allBanks[j].name << " pays Rs " << transactionsGraph[j][i].first << " to " << allBanks[i].name << " via " << transactionsGraph[j][i].second << endl;
            }

            transactionsGraph[i][j].first = 0;
            transactionsGraph[j][i].first = 0;
        }
    }
    cout << "\n";
}

void minimizeTransactions(int totalBanks, Bank allBanks[], unordered_map<string, int> &bankIndex, int totalTransactions, vector<vector<int>> &transactionMatrix, int maxPaymentTypes)
{
    Bank netBalances[totalBanks];

    for (int b = 0; b < totalBanks; b++)
    {
        netBalances[b].name = allBanks[b].name;
        netBalances[b].paymentTypes = allBanks[b].paymentTypes;

        int balance = 0;
        for (int i = 0; i < totalBanks; i++)
        {
            balance += transactionMatrix[i][b];
        }
        for (int j = 0; j < totalBanks; j++)
        {
            balance -= transactionMatrix[b][j];
        }

        netBalances[b].netBalance = balance;
    }

    vector<vector<pair<int, string>>> transactionsGraph(totalBanks, vector<pair<int, string>>(totalBanks, {0, ""}));

    int zeroBalanceCount = 0;
    for (int i = 0; i < totalBanks; i++)
    {
        if (netBalances[i].netBalance == 0)
            zeroBalanceCount++;
    }

    while (zeroBalanceCount != totalBanks)
    {
        int minIndex = findMinBalanceIndex(netBalances, totalBanks);
        pair<int, string> bestMatch = findBestMatchIndex(netBalances, totalBanks, minIndex, allBanks, maxPaymentTypes);

        int maxIndex = bestMatch.first;

        if (maxIndex == -1)
        {
            transactionsGraph[minIndex][0].first += abs(netBalances[minIndex].netBalance);
            transactionsGraph[minIndex][0].second = *(allBanks[minIndex].paymentTypes.begin());

            int simpleMaxIndex = findMaxBalanceIndex(netBalances, totalBanks);
            transactionsGraph[0][simpleMaxIndex].first += abs(netBalances[minIndex].netBalance);
            transactionsGraph[0][simpleMaxIndex].second = *(allBanks[simpleMaxIndex].paymentTypes.begin());

            netBalances[simpleMaxIndex].netBalance += netBalances[minIndex].netBalance;
            netBalances[minIndex].netBalance = 0;

            if (netBalances[minIndex].netBalance == 0)
                zeroBalanceCount++;
            if (netBalances[simpleMaxIndex].netBalance == 0)
                zeroBalanceCount++;
        }
        else
        {
            int transactionAmount = min(abs(netBalances[minIndex].netBalance), netBalances[maxIndex].netBalance);

            transactionsGraph[minIndex][maxIndex].first += transactionAmount;
            transactionsGraph[minIndex][maxIndex].second = bestMatch.second;

            netBalances[minIndex].netBalance += transactionAmount;
            netBalances[maxIndex].netBalance -= transactionAmount;

            if (netBalances[minIndex].netBalance == 0)
                zeroBalanceCount++;
            if (netBalances[maxIndex].netBalance == 0)
                zeroBalanceCount++;
        }
    }

    displayTransactions(transactionsGraph, totalBanks, allBanks);
}

int main()
{
    cout << "\n\t\t\t\t**** Welcome to the Global Cash Flow Optimization System ****\n\n\n";
    cout << "Our system simplifies the transaction process between banks globally by reducing the number of transactions required. The World Bank will serve as an intermediary for banks that do not share any common payment methods.\n\n";
    cout << "Please input the total number of banks involved in the transactions:\n";

    int totalBanks;
    cin >> totalBanks;

    Bank allBanks[totalBanks];
    unordered_map<string, int> bankIndex;

    cout << "Provide the following details for each bank:\n";
    cout << "1. Bank name\n";
    cout << "2. The count of payment methods it supports\n";
    cout << "3. List of payment methods (ensure no spaces in names)\n";

    int maxPaymentTypes;
    for (int i = 0; i < totalBanks; i++)
    {
        if (i == 0)
        {
            cout << "World Bank : ";
        }
        else
        {
            cout << "Bank " << i << " : ";
        }
        cin >> allBanks[i].name;
        bankIndex[allBanks[i].name] = i;
        int numTypes;
        cin >> numTypes;

        if (i == 0)
            maxPaymentTypes = numTypes;

        string paymentType;
        while (numTypes--)
        {
            cin >> paymentType;
            allBanks[i].paymentTypes.insert(paymentType);
        }
    }

    cout << "Enter the number of transactions:\n";
    int totalTransactions;
    cin >> totalTransactions;

    vector<vector<int>> transactionMatrix(totalBanks, vector<int>(totalBanks, 0));

    cout << "Enter the details of each transaction:\n";
    cout << "Format: Debtor Bank, Creditor Bank, and amount\n";
    cout << "Transactions can be entered in any order.\n";
    for (int i = 0; i < totalTransactions; i++)
    {
        cout<< "Transaction "<< (i + 1) <<":";
        string debtor, creditor;
        int amount;
        cin >> debtor >> creditor >> amount;
        transactionMatrix[bankIndex[debtor]][bankIndex[creditor]] = amount;
    }

    minimizeTransactions(totalBanks, allBanks, bankIndex, totalTransactions, transactionMatrix, maxPaymentTypes);

    return 0;
}
