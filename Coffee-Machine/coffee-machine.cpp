/**
 *  COFFEE MACHINE
 */

#include <iostream>
#include <cstdint>


class CoffeeMachine;
class Coffee{
private:
    int_least16_t water_, milk_, coffee_bean_, price_;
public:
    Coffee(int_least16_t, int_least16_t, int_least16_t, int_least16_t);
    friend CoffeeMachine;
};

class CoffeeMachine{
private:
    int_least16_t water_, milk_, coffee_bean_, money_, cups_;
public:
    CoffeeMachine(int_least16_t, int_least16_t, int_least16_t,
        int_least16_t, int_least16_t);
    void Fill(int_least16_t, int_least16_t, int_least16_t,
        int_least16_t);
    void Take();
    void Buy(Coffee);
    bool Possible(Coffee) const;
    void Remaining() const;
};

int GetChoice(std::string);
int_least16_t StringToNumber(std::string);
void Fill(CoffeeMachine &);
void BuyCoffee(CoffeeMachine &, Coffee &, Coffee &, Coffee &);

int main()
{
    Coffee espresso(250, 0, 16, 4);
    Coffee latte(350, 75, 20, 7);
    Coffee cappuccino(200, 100, 12, 6);
    CoffeeMachine CM(400, 540, 120, 550,9);

    while(true){
        std::cout << "Write action (buy, fill, take, remaining, exit): ";
        std::string action;
        std::getline(std::cin, action);

        if(action == "remaining"){
            std::cout << '\n';
            CM.Remaining();
            std::cout << '\n';
        }
        else if(action == "exit"){
            break;
        }
        else if(action == "buy"){
            BuyCoffee(CM, espresso, latte, cappuccino);
        }
        else if(action == "fill"){
            Fill(CM);
        }
        else if (action == "take"){
            CM.Take();
            std::cout << '\n';
        }
        else{
            std::cout << "Wrong input!" << "\n\n";
        }
    }
}

Coffee :: Coffee(int_least16_t water, int_least16_t milk,
                int_least16_t coffee_bean, int_least16_t price){
    water_       = water;
    milk_        = milk;
    coffee_bean_ = coffee_bean;
    price_       = price;
}

CoffeeMachine :: CoffeeMachine(int_least16_t water, int_least16_t milk,
                int_least16_t coffee_bean, int_least16_t money,
                int_least16_t cups){
    water_       = water;
    milk_        = milk;
    coffee_bean_ = coffee_bean;
    money_       = money;
    cups_        = cups;
}

void CoffeeMachine :: Fill(int_least16_t water, int_least16_t milk,
                int_least16_t coffee_bean, int_least16_t cups){
    water_       += water;
    milk_        += milk;
    coffee_bean_ += coffee_bean;
    cups_        += cups;
}

bool CoffeeMachine :: Possible(Coffee coffee) const{
    if(water_ < coffee.water_ ){
        std::cout << "Sorry, not enough water!" << "\n\n";
        return false;
    }
    if ( milk_ < coffee.milk_){
        std::cout << "Sorry, not enough milk!" << "\n\n";
        return false;
    }
    if ( coffee_bean_ < coffee.coffee_bean_){
        std::cout << "Sorry, not enough coffee beans!" << "\n\n";
        return false;
    }
    if ( cups_ == 0){
        std::cout << "Sorry, not enough disposable cups!" << "\n\n";
            return false;
    }
    return true;
}
void CoffeeMachine :: Remaining() const{
    std::cout << "The coffee machine has:" << '\n';
    std::cout << water_ << " ml of water" << '\n';
    std::cout << milk_ << " ml of milk" << '\n';
    std::cout << coffee_bean_ << " g of coffee beans" << '\n';
    std::cout << cups_ << " of disposable cups" << '\n';
    std::cout << "$" << money_ << " of money" << '\n';
}

void CoffeeMachine :: Buy(Coffee coffee){
    water_       -=  coffee.water_;
    milk_        -=  coffee.milk_;
    coffee_bean_ -=  coffee.coffee_bean_;
    money_       +=  coffee.price_;
    cups_--;
}

void CoffeeMachine :: Take(){
    std::cout << "I gave you $" << money_ <<'\n';
    money_ = 0;
}

int GetChoice(std::string input){
    if(input.size() != 1 || input[0] < '1' || input[0] > '3'){
        throw "Wrong input!";
    }

    return input[0] - '0';
}

int_least16_t StringToNumber(std::string input){
    for(char x : input){
        if(x < '0' || x > '9'){
            throw "Not a integer!\n";
        }
    }

    int_least16_t temp = 0;
    for(char x : input){
        temp *= 10;
        temp += x - '0';
    }

    return temp;
}

void Fill(CoffeeMachine &cm){
    int_least16_t water, milk, coffee_bean, money, cups;
    std::string temp;
    std::cout << '\n';

    std::cout << "Write how many ml of water do you want"\
    " to add:";
    getline(std::cin, temp);
    try{
        water = StringToNumber(temp);
    }
    catch (const char * exception){
        std::cout << exception << '\n';
        return;
    }

    std::cout << "Write how many ml of milk do you want"\
    " to add:";
    getline(std::cin, temp);
    try{
        milk = StringToNumber(temp);
    }
    catch (const char * exception){
        std::cout << exception << '\n';
        return;
    }

    std::cout << "Write how many grams of coffee beans do"\
    " you want to add:";
    getline(std::cin, temp);
    try{
        coffee_bean = StringToNumber(temp);
    }
    catch (const char * exception){
        std::cout << exception << '\n';
        return;
    }

    std::cout << "Write how many disposable cups of coffee"\
    " do you want to add:" ;
    getline(std::cin, temp);
    try{
        cups = StringToNumber(temp);
    }
    catch (const char * exception){
        std::cout << exception << '\n';
        return;
    }

    cm.Fill(water, milk, coffee_bean, cups);
    std::cout << '\n';
}

void BuyCoffee(CoffeeMachine &CM, Coffee & espresso,
        Coffee & latte, Coffee & cappuccino){
    std::cout << '\n';
    std::cout << "What do you want to buy? \n1 - espresso, 2 -"\
     "latte, 3 - cappuccino, back - to main menu:" << '\n';
     std::string action;
    std::getline(std::cin, action);

    if(action == "back"){
        std::cout << '\n';
        return;
    }

    int choice;
    try{
        choice = GetChoice(action);
    }
    catch (const char * exception){
        std::cout << exception <<  "\n\n";
        return;
    }

    if(choice == 1){
        if(CM.Possible(espresso)){
            CM.Buy(espresso);
            std::cout << "I have enough resources, making"\
            " you a coffee!" << "\n\n";
        }
    }
    else if(choice == 2){
        if(CM.Possible(latte)){
            CM.Buy(latte);
            std::cout << "I have enough resources, making"\
            " you a coffee!" << "\n\n";
        }
    }
    else{
        if(CM.Possible(cappuccino)){
            CM.Buy(cappuccino);
            std::cout << "I have enough resources, making"\
            " you a coffee!" << "\n\n";
        }
    }
}
