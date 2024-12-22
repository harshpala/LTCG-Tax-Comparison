#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>


using namespace std;

// since the data is from year 2001 to 2029 or simply considering from row 2 to 30
const int MAX_YEARS = 29;
const string csvPath = "./data/price-inflation.csv";


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

    if (!sellingYear)
    {
        cerr<<"Please Enter year in digits, eg: 2002"<<endl;
        return false;
    }
    
    // if (purchaseYear < 2001) {
    //     cerr << "Purchase Year cannot be before 2001" << endl;
    //     return false;
    // }

    // else if (purchaseYear > 2028) {
    //     cerr << "Purchase Year cannot be after 2028" << endl;
    //     return false;
    // }

    else if (sellingYear < 2002) {
        cerr << "Selling must be minimun 2024" << endl;
        return false;
    }

    else if (sellingYear > 2029) {
        cerr << "Selling Year cannot be after 2029" << endl;
        return false;
    }

    else if (purchaseYear >= sellingYear) {
        cerr << "Selling Year cannot be before or same as the Purchase Year" << endl;
        return false;
    }
    // If all checks passed
    return true;
}

// Function to calculate combined cumulative growth rate adjusted by inflation
double cumulativeGrowthInflationCalculator(int purchaseYear, int sellingYear, 
                                         const PropertyGrowthRate growthRates[], 
                                         const InflationRate inflationRates[], 
                                         double &cumulativeInflation) {
    double cumulativeResult = 1.0;
    cumulativeInflation = 1.0;

    for (int year = purchaseYear ; year < sellingYear; ++year) {            // Loop from purchase year to selling year
        int index = year - 2001;                                            // Assuming the data starts at year 2001

        double growthRate = growthRates[index].getRate();                   // Calculate the adjusted rate (Gi - Ii)
        double inflationRate = inflationRates[index].getRate();

        cumulativeResult *= (1 + (growthRate - inflationRate) / 100.0);     // Apply the formula for growth-inflation adjusted rate
        cumulativeInflation *= (1 + inflationRate / 100.0);
    }

    cumulativeResult -= 1;                                                  // Convert back to percentage
    cumulativeInflation -= 1;                                               // Convert back to percentage for inflation

    return cumulativeResult;
}

double calculateOldLTCG(double sellingPrice, double costPrice, double cumulativeInflation) {
   double rawProfit = sellingPrice - costPrice;
    double LTCGTax = 0;
    if (!(rawProfit<0))
    {
        double inflationAdjustedProfit = rawProfit / (1 + cumulativeInflation);  // Adjusting the profit with inflation
        LTCGTax = 0.20 * inflationAdjustedProfit;                                // 20% tax on the inflation-adjusted profit
    }
    return LTCGTax;                                                          
}

// LTCG calculation under new scheme (no inflation adjustment, 12.5% tax)
double calculateLTCGNewScheme(double sellingPrice, double costPrice) {
    double rawProfit = sellingPrice - costPrice;
    double LTCGTax = 0;
    if (!(rawProfit<0))
    {
    LTCGTax = 0.125 * rawProfit;
    }
    return LTCGTax;
}

int main(){

    InflationRate inflationRates[MAX_YEARS];
    PropertyGrowthRate growthRates[MAX_YEARS];

    // Read the data from csv file
    read_record(MAX_YEARS, inflationRates, growthRates);        

    // Get user inputs
    int purchaseYear = 2010;
    int sellingYear;                              
    double costPrice = 5000000;


    // cout << "Enter the purchase year: ";
    // cin >> purchaseYear;

    cout << "Enter the selling year: ";
    cin >> sellingYear;

    // cout << "Enter the cost price (in Rs): ";
    // cin >> costPrice;

    cout << endl;

   if (!validateYears(purchaseYear, sellingYear)) {
        cerr << "Invalid year input. Please correct the input values." << endl;
        return 1;
    }

    double cumulativeInflation = 0.0;

    // Calculate cumulative growth and inflation
    double cumulativeResult = cumulativeGrowthInflationCalculator(purchaseYear, sellingYear, growthRates, inflationRates, cumulativeInflation);

    // Calculate estimated and adjusted selling price
    int estimatedSellingPrice = round(costPrice * (1 + cumulativeResult));              // Rounding the estimated selling price
    cout << "Estimated Selling Price: Rs " << estimatedSellingPrice << endl;

    int LTCGOld = round(calculateOldLTCG(estimatedSellingPrice, costPrice, cumulativeInflation));    // Rounding the oldLTCGTax

    int LTCGNew = round(calculateLTCGNewScheme(estimatedSellingPrice, costPrice));                      // Rounding the newLTCGTax

    cout << "LTCG Tax under New Scheme: Rs " << LTCGNew << endl;
    cout << "Old LTCG Tax to be paid: Rs " <<LTCGOld << endl;
    cout << "Difference in LTCG Tax: Rs " << abs(LTCGOld - LTCGNew) << endl;

    
}