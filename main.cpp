#include "categories.cpp"
#include <iostream>
using namespace std;
Category *sections[15];

void init()
{
    sections[0] = new Category("Fruits");
    sections[0]->head = sections[0]->push(sections[0]->head, 101, const_cast<char *>("Apple"), 32.5, 22);
    sections[0]->head = sections[0]->push(sections[0]->head, 102, const_cast<char *>("Banana"), 5, 48);
    sections[0]->head = sections[0]->push(sections[0]->head, 103, const_cast<char *>("Kiwi"), 40, 2);
    sections[0]->head = sections[0]->push(sections[0]->head, 104, const_cast<char *>("Orange"), 7, 35);
    sections[1] = new Category("Vegetables");
    sections[1]->head = sections[1]->push(sections[1]->head, 201, const_cast<char *>("Potato"), 4, 120);
    sections[1]->head = sections[1]->push(sections[1]->head, 202, const_cast<char *>("Tomato"), 9, 35);
    sections[1]->head = sections[1]->push(sections[1]->head, 203, const_cast<char *>("Chilies"), 10, 40);
    sections[1]->head = sections[1]->push(sections[1]->head, 204, const_cast<char *>("Spinach"), 15, 30);
    sections[2] = new Category("Dairy");
    sections[2]->head = sections[2]->push(sections[2]->head, 301, const_cast<char *>("Milk"), 25, 100);
    sections[2]->head = sections[2]->push(sections[2]->head, 302, const_cast<char *>("Cheese"), 130, 20);
    sections[2]->head = sections[2]->push(sections[2]->head, 303, const_cast<char *>("Butter"), 49, 45);
    sections[3] = new Category("Snacks");
    sections[3]->head = sections[3]->push(sections[3]->head, 401, const_cast<char *>("Kurkure"), 10, 2);
    sections[3]->head = sections[3]->push(sections[3]->head, 402, const_cast<char *>("Lays"), 20, 1);
    sections[3]->head = sections[3]->push(sections[3]->head, 403, const_cast<char *>("Bingo"), 15, 25);
    sections[3]->head = sections[3]->push(sections[3]->head, 404, const_cast<char *>("Bourbon"), 30, 29);
}

int checkCategory(Category *sections[15])
{
    int index;
    string catName;
    cout << "Enter category name: ";
    cin >> catName;
    for (index = 0; index < 15; index++)
    {
        if (sections[index]->category_name == catName)
            break;
    }
    if (index == 15)
        cout << endl
             << "Incorrect category name!" << endl
             << endl;
    return index;
}

void vendor()
{
    int catcount = 4;
    int choice = 0;
    int index, id;
    string catName;
    do
    {
        for (index = 0; index < 100; index++)
            cout << ".";
        cout << endl;
        cout << "1.Create New Category\t2.Add New Item\t3.View Category\t 4.Delete Product\n5.Update Price\t\t6.Update Stock\t0.Exit" << endl;
        for (index = 0; index < 100; index++)
            cout << ".";
        cout << endl;
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter category name: ";
            cin >> catName;
            sections[catcount] = new Category(catName);
            catcount++;
            break;
        case 2:
            index = checkCategory(sections);
            if (index == 15)
                break;
            sections[index]->head = sections[index]->push(sections[index]->head);
            break;
        case 3:
            index = checkCategory(sections);
            if (index == 15)
                break;
            sections[index]->listAll(sections[index]->head);
            break;
        case 4:
            index = checkCategory(sections);
            if (index == 15)
                break;
            cout << "Enter product id: ";
            cin >> id;
            sections[index]->head = sections[index]->pop(sections[index]->head, id);
            break;
        case 5:
            index = checkCategory(sections);
            if (index == 15)
                break;
            cout << "Enter product id: ";
            cin >> id;
            sections[index]->updatePrice(sections[index]->head, id);
            break;
        case 6:
            index = checkCategory(sections);
            if (index == 15)
                break;
            cout << "Enter product id: ";
            cin >> id;
            sections[index]->updateStock(sections[index]->head, id);
            break;
        case 0:
            break;
        default:
            cout << "Enter a valid choice!" << endl;
        }
    } while (choice != 0);
}

void customer()
{
    Cart cart;
    int index, choice, catNum, pId, confirm = 0;
    do
    {
        for (index = 0; index < 100; index++)
            cout << ".";
        cout << endl;
        cout << "1.View Categories\t2.View Cart\t3.Edit Cart\t0.Exit" << endl;
        for (index = 0; index < 100; index++)
            cout << ".";
        cout << endl;
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            for (index = 0; index < 15; index++)
            {
                if (sections[index] != NULL)
                    cout << index + 1 << ". " << sections[index]->category_name << endl;
            }
            cout << "Which category would you like to explore? (Enter category number) ";
            cin >> catNum;
            catNum--;
            sections[catNum]->listAll(sections[catNum]->head);
            cout << "What product would you like to buy? (Enter product id [0 - None]) ";
            cin >> pId;
            cart.head = cart.push(sections, cart.head, catNum, pId, catNum);
            break;
        case 2:
            confirm = cart.listAll(sections, cart.head);
            if (confirm == 1)
            {
                return;
            }
            break;
        case 3:
            cart.head = cart.editCart(cart.head);
            break;
        case 0:
            break;
        }
    } while (choice != 0);
}

int main()
{
    init();
    int mode;
    do
    {
        cout << "1 => Vendor\t2 => Customer\t0 => Exit Program\tEnter mode: ";
        cin >> mode;
        if (mode == 1)
            vendor();
        else if (mode == 2)
            customer();
    } while (mode != 0);
    return 0;
}