
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "drink.h"
#include "util.h"
using namespace std;


namespace sdds
{
    const int MAXDRINKS = 5;
    static Drink machine[MAXDRINKS];
    void loadDrinksFromFile(const char* filename)
    {
        FILE* fp = NULL;
        fp = fopen(filename, "r");
        char* name = nullptr;
        int ch, i = 0, volume = 0, quantity = 0;
        double price = 0;
        while (!feof(fp))
        {
            name = new char[11];
            fscanf(fp, "%s[^]%*c", name);
            ch = fgetc(fp);
            fscanf(fp, "%d", &volume);
            ch = fgetc(fp);
            fscanf(fp, "%lf", &price);
            ch = fgetc(fp);
            fscanf(fp, "%d", &quantity);
            ch = fgetc(fp);
            strcpy(machine[i].name, name);
            machine[i].volume = volume;
            machine[i].price = price;
            machine[i].quantity = quantity;
            i++;
            delete[]name;
            name = nullptr;
            if (!feof(fp))
                ungetc(ch, fp);

        }fclose(fp);

    }

   /* void loadDrinks()
    {
        machine[0] = Drink{ "Coffee", 300, 1.50, 5 };
        machine[1] = Drink{ "Tea", 250, 1.25, 3 };
        machine[2] = Drink{ "Cola", 350, 2.50, 2 };
        machine[3] = Drink{ "Water", 500, 3.10, 15 };
        machine[4] = Drink{ "Beer", 350, 5.25, 0 };
    }*/

    void drinkMenu()
    {
        cout << "-----------Available Drinks-----------" << endl;
        cout << left << setw(10) << "Drink" << setw(10) << "Volume";
        cout << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (int i = 0; i < MAXDRINKS; ++i)
        {
            cout << i + 1 << ".";
            displayDrink(&machine[i]);
        }
    }

    void displayDrink(const Drink* drink)
    {
        cout << left << setw(10) << drink->name << setw(10) << drink->volume
            << setw(10) << drink->price << setw(10) << drink->quantity << endl;
    }

    int chooseDrink()
    {
        bool done = false;
        int sel = 0;
        cout << "Select a drink from the menu (1-" << MAXDRINKS << "): ";
        do
        {
            cin >> sel;
            clearBuffer();
            if (sel >= 1 && sel <= MAXDRINKS)
            {
                if (updateDrink(sel) == true)
                    done = true;
                else
                    cout << "Out of stock for that drink, try again: ";
            }
            else
                cout << "Selection was was invalid try again: ";
        } while (!done);
        return sel;
    }

    bool updateDrink(int sel)
    {
        bool res = false;
        if (machine[sel - 1].quantity > 0)
        {
            machine[sel - 1].quantity--;
            res = true;
        }
        return res;
    }
}