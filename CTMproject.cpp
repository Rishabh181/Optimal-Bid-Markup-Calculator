#include <bits/stdc++.h>
using namespace std;

double cumulativeNormal(double x) {
    return 0.5 * std::erfc(-x * M_SQRT1_2);
}

double friedmanprice(double x, double n, double mean, double stddeviation, int principle) {
    double biddingpercentage = x / 100 + 1;
    double z = (biddingpercentage - mean) / stddeviation;
    double prob = 1 - cumulativeNormal(z);
    double probfinal = pow(prob, n);
    double expected = principle * (biddingpercentage - 1) * probfinal;
    return expected;
}

double gatesmodel(double x, double n, double mean, double stddeviation, int principle ){
    double biddingpercentage = x / 100 + 1;
    double z = (biddingpercentage - mean) / stddeviation;
    double prob = 1 - cumulativeNormal(z);
    double finalprob = 1/(n*(1-prob)/prob + 1 ) ;
    double expected = principle*(biddingpercentage - 1 )*finalprob ;
    return expected ;
}

double findpeak(int n, double mean, double stddeviation, int principle) {
    double lowval = 1, highval = 20.0;
    double peak = -1;

    while (lowval <= highval) {
        double midval = (lowval + highval) / 2.0;
        double midback = friedmanprice(midval - 0.001, n, mean, stddeviation, principle);
        double midfront = friedmanprice(midval + 0.001, n, mean, stddeviation, principle);
        double midddd = friedmanprice(midval, n, mean, stddeviation, principle);

        if (midback < midddd && midddd > midfront) {
            peak = midval;
            break;
        }
        if (midddd > midback) {
            lowval = midval + 0.001;
        } else {
            highval = midval - 0.001;
        }
    }
    return peak;
}


double findpeakgatesmodel(int n, double mean, double stddeviation, int principle) {
    double lowval = 1, highval = 20.0;
    double peak = -1;

    while (lowval <= highval) {
        double midval = (lowval + highval) / 2.0;
        double midback = gatesmodel(midval - 0.001, n, mean, stddeviation, principle);
        double midfront = gatesmodel(midval + 0.001, n, mean, stddeviation, principle);
        double midddd = gatesmodel(midval, n, mean, stddeviation, principle);

        if (midback < midddd && midddd > midfront) {
            peak = midval;
            break;
        }
        if (midddd > midback) {
            lowval = midval + 0.001;
        } else {
            highval = midval - 0.001;
        }
    }
    return peak;
}

int main() {

    int numberofcompetitor, principle;
    double mean, stddeviation;

    cout << "Enter number of competitors: ";
    cin >> numberofcompetitor;
    cout << "Enter principle of the project: ";
    cin >> principle;
    cout << "Enter mean (B/TC ratio) of a typical competitor: ";
    cin >> mean;
    cout << "Enter standard deviation: ";
    cin >> stddeviation;

    char ch , check = 'K' ;
    cout<<"which method do you want to use gates model(G) or friedmans model(F) ? " ;
    cin>>ch ;
    double peakfriedman , peakgate , peak ;

     peakgate = findpeakgatesmodel(numberofcompetitor, mean, stddeviation, principle);
    peakfriedman = findpeak(numberofcompetitor, mean, stddeviation, principle);
    // while(ch != check ){if(ch == 'G'){
    //     peak = findpeakgatesmodel(numberofcompetitor, mean, stddeviation, principle);
    //     check = 'G' ;
    // } else if(ch == 'F'){
    //     peak = findpeak(numberofcompetitor, mean, stddeviation, principle);
    //     check = 'F' ;
    // }else {
    //     cout<<"your selection was incorrect... please rewrite it"<<endl;
    //     char cc ;
    //     cin>>cc ;
    //     ch = cc ;
    // }
    // }
    int ansgate = gatesmodel(peakgate ,numberofcompetitor, mean, stddeviation, principle) ;
    int ansfriedman = friedmanprice(peakfriedman ,numberofcompetitor, mean, stddeviation, principle) ;
    cout << "answer with gates model '" << peakgate <<"' and amount " <<ansgate
    << endl;
    cout<<" answer with friedmans model '"<< peakfriedman <<"' and amount "<<
    ansfriedman << endl ;

    cout<<"moderate percentage of markup would be = " << (ansfriedman + ansgate )/ 2 <<endl;

    // if(ch == 'F')
    // cout << " with amount "<< friedmanprice(peak ,numberofcompetitor, mean, stddeviation, principle) ;
    // else {
    //     cout<< "with amount "<< gatesmodel(peak ,numberofcompetitor, mean, stddeviation, principle) ;
    // }



    return 0;
}
