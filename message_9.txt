#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
class InvalidTimeException{
public:
    void print()
    {
        cout<<"The time is not valid"<<endl;
    }
};
class Race{
protected:
    char name[41];
    int godina;
    int mesec;
    float najdobroVreme;
    float km;
public:
    Race (char *name=" ",int godina=0,int mesec=0,float najdobroVreme=0.0,float km=0.0)
    {
        strcpy (this->name,name);
        this->godina=godina;
        this->mesec=mesec;
        this->najdobroVreme=najdobroVreme;
        this->km=km;
    }
    Race (const Race &R)
    {
        strcpy (this->name,R.name);
        this->godina=R.godina;
        this->mesec=R.mesec;
        this->najdobroVreme=R.najdobroVreme;
        this->km=R.km;
    }
    Race &operator= (const Race &R)
    {
        if (this!=&R)
        {
            strcpy (this->name,R.name);
            this->godina=R.godina;
            this->mesec=R.mesec;
            this->najdobroVreme=R.najdobroVreme;
            this->km=R.km;
        }
        return *this;
    }
    virtual float heaviness()
    {
        return najdobroVreme/km;
    }
    friend ostream &operator<<(ostream &out,Race &R);
    float getNajdobro()
    {
        return najdobroVreme;
    }
};
ostream &operator<<(ostream &out,Race &R)
{
    out<<R.name<<" "<<R.mesec<<"."<<R.godina<<" "<<R.heaviness()<<endl;
    return out;
}

class CarRace: public Race{
    float *najdobriVreminja;
    int brojNajdobriVreminja;
    int brojKrugovi;
public:
    static float CAR_COEF;
    static void setKoeficient(float a)
    {
        CAR_COEF=a;
    }
    CarRace (char *name=" ",int godina=0,int mesec=0,float najdobroVreme=0.0,float km=0.0,float *najdobriVreminja=0,int brojNajdobriVreminja=0,int brojKrugovi=0):Race(name,godina,mesec,najdobroVreme,km)
    {
        this->brojNajdobriVreminja=brojNajdobriVreminja;
        this->brojKrugovi=brojKrugovi;
        this->najdobriVreminja=new float[brojNajdobriVreminja];
        for (int i=0;i<brojNajdobriVreminja;i++)
        {
            this->najdobriVreminja[i]=najdobriVreminja[i];
        }
    }
    CarRace (const CarRace &CR):Race (CR)
    {
        this->brojNajdobriVreminja=CR.brojNajdobriVreminja;
        this->brojKrugovi=CR.brojKrugovi;
        this->najdobriVreminja=new float[CR.brojNajdobriVreminja];
        for (int i=0;i<CR.brojNajdobriVreminja;i++)
        {
            this->najdobriVreminja[i]=CR.najdobriVreminja[i];
        }
    }
    CarRace &operator=(const CarRace &CR)
    {
        if (this!=&CR)
        {
            delete []najdobriVreminja;
            Race::operator=(CR);
            this->brojNajdobriVreminja=CR.brojNajdobriVreminja;
            this->brojKrugovi=CR.brojKrugovi;
            this->najdobriVreminja=new float[CR.brojNajdobriVreminja];
            for (int i=0;i<CR.brojNajdobriVreminja;i++)
            {
                this->najdobriVreminja[i]=CR.najdobriVreminja[i];
            }
        }
        return *this;
    }
    ~CarRace()
    {
        delete []najdobriVreminja;
    }
    float heaviness()
    {
        float zbir=0;
        float prosek=0;
        for (int i=0;i<brojNajdobriVreminja;i++)
        {
            prosek=prosek+najdobriVreminja[i];
        }
        prosek=prosek/(float)brojNajdobriVreminja;
        zbir=Race::heaviness()+(prosek*CarRace::CAR_COEF);
        if (brojKrugovi>15)
        {
            zbir=zbir+(zbir*10)/100;
        }
        return zbir;
    }
    CarRace &operator+=(float vreme)
    {
        if(vreme<10)
        {
            throw InvalidTimeException();
        }
        float *tmp=new float[brojNajdobriVreminja+1];
        for (int i=0;i<brojNajdobriVreminja;i++)
        {
            tmp[i]=najdobriVreminja[i];
        }
        tmp[brojNajdobriVreminja++]=vreme;
        delete []najdobriVreminja;
        najdobriVreminja=tmp;
        return *this;
    }
    void setNumberLaps (int broj)
    {
        brojKrugovi=broj;
    }
    friend ostream &operator<<(ostream &out,CarRace &Cr);
};
float CarRace::CAR_COEF=0.3;
ostream &operator<<(ostream &out,CarRace &CR)
{
    Race *tmp=dynamic_cast<CarRace*>(&CR);
    out<<*tmp;
    return out;
}


int main(){
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int izbor;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        Race t(city, year, month, bestTime, length);
        cout<<t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        CarRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        CarRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje novo najdobro vreme za prvata CarRace
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            CarRace* nn = dynamic_cast<CarRace*>(niza[i]);
            if (nn != 0){
                flag = 0;
                (*nn) += best;
                break;
            }
        }


        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        CarRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float vreme1,vreme2;
        cin>>vreme1>>vreme2;
        try{
            mgt+=vreme1;
            mgt+=vreme2;
        }
        catch(InvalidTimeException e)
        {
            e.print();
        }
        cout<<mgt;
    }

    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (izbor == 1){
                niza[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        CarRace::setKoeficient(0.7);
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }



    return 0;
}