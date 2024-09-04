#include<bits/stdc++.h>
using namespace std;

// struct Data {
//     string year;
//     double growth_rate;
//     double inflation_rate;
// };

const int MAX_YEARS = 29;                                   // since the data is from year 2001 to 2029 or simply considering from row 2 to 30
const string csvPath = "./A1_data/price-inflation.csv";


// Class to model inflation rate
class InflationRate {

    private:
        int year;
        double rate;
    
    public:
        InflationRate() : year(0), rate(0) {}
        InflationRate(const int year, double rate): year(year), rate(rate) {}

        int getYear() const {return year;}
        double getRate() const {return rate;}
};

// Class to model property growth rate
class PropertyGrowthRate{
    private:
        int year;
        double rate;

    public:
        PropertyGrowthRate() : year(0), rate(0) {}
        PropertyGrowthRate(const int year, double rate) : year(year), rate(rate) {}
        int getYear() const { return year; }
        double getRate() const { return rate; }
};

void read_record(int maxRecords, InflationRate inflationRates[], PropertyGrowthRate growthRates[]){

    int recordCount = 0;

    ifstream file(csvPath);
    string line;

    if (!(file.is_open()))
    {
        cout << "Unable to open file" << endl;
    }
    else
    {
        getline(file, line);    // Skip the header file

        while (getline(file, line) && recordCount < maxRecords){    // Read the other lines
            stringstream ss(line);
            string date, str_growthPrice, str_inflation;

            getline(ss, date, ',');
            getline(ss, str_growthPrice, ',');
            getline(ss, str_inflation, ',');

            int year = stoi(date.substr(0,4));
            double growthPrice = stod(str_growthPrice);
            double inflation = stod(str_inflation);
            growthRates[recordCount] = PropertyGrowthRate(year, growthPrice);
            inflationRates[recordCount] = InflationRate(year, inflation);
           

            recordCount++;
        }

        file.close();

    }    
    
}

bool validateYears(int purchaseYear, int sellingYear) {

    if (purchaseYear < 2001) {
        cerr << "Purchase Year cannot be before 2001" << endl;
        return false;
    }

    else if (purchaseYear > 2030) {
        cerr << "Purchase Year cannot be after 2030" << endl;
        return false;
    }

    else if (sellingYear < 2010) {
        cerr << "Selling Year cannot be before 2010" << endl;
        return false;
    }

    else if (sellingYear > 2030) {
        cerr << "Selling Year cannot be after 2030" << endl;
        return false;
    }

    else if (purchaseYear >= sellingYear) {
        cerr << "Selling Year cannot be before or equal to Purchase Year" << endl;
        return false;
    }
    // All checks passed
    return true;
}

void cumulativeGrowth(){}
void cumulativeInflation(){}
void estimatedSellingPrice(){}
void adjustedSellingPrice(){}

int main(){

    InflationRate inflationRates[MAX_YEARS];
    PropertyGrowthRate growthRates[MAX_YEARS];
    
    read_record(MAX_YEARS, inflationRates, growthRates);        // Read the data from csv file

    int purchaseYear, sellingYear;                              // Get user inputs
    double costPrice;

    cout << "Enter the purchase year: ";
    cin >> purchaseYear;
    cout << "Enter the selling year: ";
    cin >> sellingYear;
    cout << "Enter the cost price (in Rs): ";
    cin >> costPrice;

   if (!validateYears(purchaseYear, sellingYear)) {
        cerr << "Invalid year input. Please correct the input values." << endl;
        return 1;
    } 
    
}