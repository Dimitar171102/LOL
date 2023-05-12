#include <iostream>
#include <cstring>
using namespace std;

class FoodItem {
protected:
    char* tip;
    int n;

public:
    FoodItem() {
        this->tip = new char[8];
        strcpy(this->tip, "empty");
        this->n = 0;
    }

    FoodItem(char* type, int n) {
        this->tip = new char[strlen(type) + 1];
        strcpy(this->tip, type);
        this->n = n;
    }

    char* getType() { return tip; }

    virtual int getPrice() = 0;

    virtual int getTime() = 0;

    virtual ~FoodItem() {
        delete [] tip;
    }
};

class Pizza : public FoodItem {
    char* dough;

public:
    Pizza() : FoodItem() {
        this->dough = new char[12];
        strcpy(this->dough, "wholeWheat");
    }

    Pizza(char* tip, int n, char* dough) : FoodItem(tip, n) {
        this->dough = new char[strlen(dough) + 1];
        strcpy(this->dough, dough);
    }

    int getPrice() {
        if(strcmp(this->dough, "wholeWheat") == 0) {
            return 250 * n;
        }
        else if(strcmp(this->dough, "glutenFree") == 0) {
            return 350 * n;
        } else {
            return 0;
        }
    }

    int getTime() { return 25; }

    ~Pizza() {
        delete [] dough;
    }
};

class Steak : public FoodItem {
    bool cooked;

public:
    Steak() : FoodItem() {
        this->cooked = false;
    }

    Steak(char* tip, int n, bool cooked) : FoodItem(tip, n) {
        this->cooked = cooked;
    }

    int getPrice() { return 1300 * n; }

    int getTime() {
        if(cooked) return 20;
        else if(!cooked) return 15;
        else return 0;
    }

    ~Steak() { }
};

FoodItem* getMaxFoodItem(FoodItem* pItem[], int n) {
    FoodItem* item = pItem[0];
    int max_food_price = pItem[0]->getPrice();

    for(int i = 0; i < n; i++) {
        if(max_food_price < pItem[i]->getPrice()) {
            max_food_price = pItem[i]->getPrice();
            item = pItem[i];
        }
    }

    return item;
}

int main() {
    FoodItem *p;
    int n;
    cin>>n;

    char type[30];
    char dough[30];
    bool cooked;
    int size;

    FoodItem *items[n];

    for (int i = 0; i <n; ++i) {
        cin>>type;
        cin>>size;


        if(strcmp(type, "pizza")==0 ) {
            cin>>dough;
            items[i] = new Pizza(type, size, dough);
        }else{
            cin>>cooked;
            items[i] = new Steak(type, size, cooked);
        }


    }

    FoodItem *it = getMaxFoodItem(items, n);
    cout<<"Type: "<<it->getType()<<endl;
    cout<<"The max price is: "<<it->getPrice()<<endl;
    cout<<"Time to cook: "<<it->getTime();
    return 0;
}