#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

class LoanCalculator {
private:
    double principal;
    double rate;
    double tenure; 

    double calculateEMI() const {
        double monthlyRate = rate / 12 / 100;

        return (principal * monthlyRate * pow(1 + monthlyRate, tenure)) / (pow(1 + monthlyRate, tenure) - 1);
    }

    string getCurrentDate() const {
        time_t now = std::time(0);
        tm *ltm = localtime(&now);
        return to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
    }

    string calculateEndDate() const {
        time_t now = std::time(0);
        tm *ltm = localtime(&now);
        ltm->tm_mon += static_cast<int>(tenure);
        mktime(ltm);
        return to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
    }

public:
    LoanCalculator(double principal, double rate, double tenure)
        : principal(principal), rate(rate), tenure(tenure) {}

    void calculateAndPrintEMI(const string& bankName) const {
        double emi = calculateEMI();
        string startDate = getCurrentDate();
        string endDate = calculateEndDate();

        cout << "EMI for " << bankName << ": Rs." << emi << endl;
        cout << "Loan Start Date: " << startDate << endl;
        cout << "Loan End Date: " << endDate << endl;
    }

    void saveDetails(const string& bankName, ofstream& outputFile) const {
        double emi = calculateEMI();
        string startDate = getCurrentDate();
        string endDate = calculateEndDate();

        outputFile << "Bank: " << bankName << "\tPrincipal: Rs." << principal
                   << "\tTenure: " << tenure << " months\tEMI: Rs." << emi
                   << "\tStart Date: " << startDate << "\tEnd Date: " << endDate << endl;
    }
};

int main() {
    ofstream outputFile("EMI_Details.txt", ios::app);
    if (!outputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    int choice;
    do {
        cout << "*******EMI CALCULATOR*********" << endl;
        cout << "Select Bank:\n";
        cout << "1. HDFC BANK(@8.5 pcpa)\n2. SBI BANK(@9.0 pcpa)\n3. YES BANK(@9.5 pcpa)\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                double principal, tenure;
                cout << "Enter principal amount for HDFC bank: ";
                cin >> principal;
                cout << "Enter tenure in months: ";
                cin >> tenure;

                LoanCalculator hdfcLoan(principal, 8.5, tenure);
                hdfcLoan.calculateAndPrintEMI("HDFC Bank");
                hdfcLoan.saveDetails("HDFC Bank", outputFile);
                break;
            }

            case 2: {
                double principal, tenure;
                cout << "Enter principal amount for SBI Bank: ";
                cin >> principal;
                cout << "Enter tenure in months: ";
                cin >> tenure;

                LoanCalculator sbiLoan(principal, 9.0, tenure);
                sbiLoan.calculateAndPrintEMI("SBI Bank");
                sbiLoan.saveDetails("SBI Bank", outputFile);
                break;
            }

            case 3: {
                double principal, tenure;
                cout << "Enter principal amount for YES Bank: ";
                cin >> principal;
                cout << "Enter tenure in months: ";
                cin >> tenure;

                LoanCalculator yesLoan(principal, 9.5, tenure);
                yesLoan.calculateAndPrintEMI("YES Bank");
                yesLoan.saveDetails("YES Bank", outputFile);
                break;
            }

            case 4:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    outputFile.close();
    return 0;
}
