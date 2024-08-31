# Cash Flow Minimizer System

The **Cash Flow Minimizer System** is designed to **optimize financial transactions** between multiple banks by minimizing the number of transactions required. The **Global Bank** acts as an intermediary for banks that do not share common payment methods.

---

## Overview

This system helps in efficiently managing and optimizing transactions between banks by reducing the total number of transactions. The Global Bank serves as a bridge for banks that have different payment methods.

### Example Banks

1. **Global Bank** (Universal Intermediary)
2. **Metro Bank**
3. **Standard Chartered**
4. **Barclays**
5. **HSBC**
6. **JPMorgan Chase**

### Sample Transactions

Here’s an example of the transactions that need to be processed:

| **From Bank**         | **To Bank**           | **Amount** |
| --------------------- | --------------------- | ---------- |
| JPMorgan Chase        | Global Bank           | ₹150       |
| JPMorgan Chase        | Metro Bank            | ₹250       |
| JPMorgan Chase        | Standard Chartered    | ₹150       |
| JPMorgan Chase        | Barclays              | ₹200       |
| HSBC                  | Global Bank           | ₹400       |
| HSBC                  | Standard Chartered    | ₹250       |
| Global Bank           | Metro Bank            | ₹350       |
| Metro Bank            | Standard Chartered    | ₹300       |
| Standard Chartered    | Barclays              | ₹450       |

---

## Payment Methods

Each bank supports specific payment methods. The **Global Bank** supports all payment methods. The payment methods in this example are:

1. **Stripe**
2. **Square**
3. **ApplePay**

### Supported Payment Methods by Bank

| **Bank**              | **Supported Methods** |
| --------------------- | ---------------------- |
| Global Bank           | Stripe, Square, ApplePay |
| Metro Bank            | Stripe, Square         |
| Standard Chartered    | Square                 |
| Barclays              | Stripe, ApplePay       |
| JPMorgan Chase        | ApplePay               |
| HSBC                  | Square, ApplePay       |

---

## System Functionality

The system follows these steps to minimize transactions:

1. **Net Balance Calculation:** Compute each bank’s net balance:
   
    Net Balance = [Sum of all **credits**(_amounts to be received_)] - [Sum of all **debits**(_amounts to pay_)] 

2. **Transaction Optimization:**
   - Identify the bank with the **lowest net balance** (debtor) and the bank with the **highest net balance** (creditor) that share a common payment method.
   - Execute a transaction between these two banks for the smaller of the two net balances.
   - Repeat the process until all transactions are optimized.

### Example Graphs

1. **Transaction Graph:** This graph represents the initial transaction relationships between banks.

   ![image](https://github.com/user-attachments/assets/5b235457-c2b5-41c7-8580-50290fbeb409)
<!-- Replace with actual image URL -->

2. **Optimized Transactions Graph:** This graph shows the minimized transactions after optimization.

   ![image](https://github.com/user-attachments/assets/843f254b-ca08-4bdc-8b74-e5e0060b6d8e) <!-- Replace with actual image URL -->

3. **Execution Example:** This example demonstrates the menu-driven execution of the system.

   ![image](https://github.com/user-attachments/assets/6ad4ab90-6e7b-4526-bfe2-47e85e8fea23) <!-- Replace with actual image URL -->

---

## How to Use

### Input Instructions

1. **Total Number of Banks**
   - Enter the number of banks involved in the transactions.

2. **Details for Each Bank**
   - Enter the bank name, number of payment methods, and list of payment methods.

3. **Number of Transactions**
   - Specify the number of transactions.

4. **Details of Each Transaction**
   - For each transaction, provide the debtor bank name, creditor bank name, and transaction amount.

### Running the Application

Run the C++ application and follow the interactive prompts to input the bank details and transactions. The system will process and minimize the transactions accordingly.


