#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
typedef struct Node
{
    int product_id;
    char product_name[32];
    double price;
    int stock;
    int category; // optional (only for adding to cart)
    Node *link;
} Node;

class Category
{
public:
    Node *head = NULL;
    string category_name;
    Category()
    {
    }
    Category(string obj_name)
    {
        category_name = obj_name;
    }
    Node *createNode()
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->link = NULL;
        cout << "Enter product id: ";
        cin >> newNode->product_id;
        cout << "Enter product name: ";
        cin >> newNode->product_name;
        cout << "Enter product price: ";
        cin >> newNode->price;
        cout << "Enter product stock: ";
        cin >> newNode->stock;
        return newNode;
    }
    Node *createNode(int id, char name[32], double price, int stock)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->link = NULL;
        newNode->product_id = id;
        copy_n(name, 32, newNode->product_name);
        newNode->price = price;
        newNode->stock = stock;
        return newNode;
    }

    Node *push(Node *head)
    {
        Node *newNode = createNode();
        Node *temp = head;
        if (head == NULL)
        {
            return newNode;
        }
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = newNode;
        newNode->link = NULL;
        return head;
    }
    Node *push(Node *head, int id, char name[32], double price, int stock)
    {
        Node *newNode = createNode(id, name, price, stock);
        Node *temp = head;
        if (head == NULL)
        {
            return newNode;
        }
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = newNode;
        newNode->link = NULL;
        return head;
    }

    Node *pop(Node *head, int id)
    {
        if (head == NULL)
        {
            cout << "Empty category!" << endl
                 << endl;
            return head;
        }
        else if (head->link == NULL && head->product_id == id)
        {
            cout << "Product with id " << id << " has been successfully deleted." << endl
                 << endl;
            free(head);
            return NULL;
        }
        Node *first = NULL, *second = head, *third = head->link;
        while (second != NULL)
        {
            if (second->product_id == id)
            {
                break;
            }
            first = second;
            second = third;
            if (third != NULL)
                third = third->link;
        }
        if (second == NULL)
        {
            cout << "Product not found!" << endl
                 << endl;
            return head;
        }
        first->link = third;
        cout << "Product with id " << id << " has been successfully deleted." << endl
             << endl;
        free(second);
        return head;
    }

    void listAll(Node *head)
    {
        cout << endl
             << category_name << endl;
        for (int index = 0; index < 100; index++)
            cout << ".";
        cout << endl;
        if (head == NULL)
        {
            cout << "Empty category!" << endl
                 << endl;
            return;
        }
        cout << "Product ID\tProduct name\tPrice\t\tStock" << endl;
        while (head != NULL)
        {
            cout << head->product_id << "\t\t" << head->product_name << "\t\t" << head->price << "\t\t" << head->stock << endl;
            head = head->link;
        }
        cout << endl;
    }
    void updatePrice(Node *head, int id)
    {
        int price;
        if (head == NULL)
        {
            cout << "Empty category!" << endl
                 << endl;
            return;
        }
        else if (head->link == NULL && head->product_id == id)
        {
            cout << "Enter new price of " << head->product_name << ": ";
            cin >> price;
            head->price = price;
            cout << "Product with id " << id << " has been successfully updated." << endl
                 << endl;
            return;
        }
        Node *first = head, *second = head->link;
        while (first != NULL)
        {
            if (first->product_id == id)
            {
                break;
            }
            first = second;
            if (second != NULL)
                second = second->link;
        }
        if (first == NULL)
        {
            cout << "Product not found!" << endl
                 << endl;
            return;
        }
        cout << "Enter new price of " << first->product_name << ": ";
        cin >> price;
        first->price = price;
        cout << "Product with id " << id << " has been successfully updated." << endl
             << endl;
        return;
    }
    void updateStock(Node *head, int id)
    {
        int stock;
        if (head == NULL)
        {
            cout << "Empty category!" << endl
                 << endl;
            return;
        }
        else if (head->link == NULL && head->product_id == id)
        {
            cout << "Enter new stock of " << head->product_name << ": ";
            cin >> stock;
            head->stock = stock;
            cout << "Product with id " << id << " has been successfully updated." << endl
                 << endl;
            return;
        }
        Node *first = head, *second = head->link;
        while (first != NULL)
        {
            if (first->product_id == id)
            {
                break;
            }
            first = second;
            if (second != NULL)
                second = second->link;
        }
        if (first == NULL)
        {
            cout << "Product not found!" << endl
                 << endl;
            return;
        }
        cout << "Enter new stock of " << first->product_name << ": ";
        cin >> stock;
        first->stock = stock;
        cout << "Product with id " << id << " has been successfully updated." << endl
             << endl;
        return;
    }
    void updateStock2(Node *head, int id, int editStock)
    {
        if (head == NULL)
        {
            cout << "Empty category!" << endl
                 << endl;
            return;
        }
        else if (head->link == NULL && head->product_id == id)
        {
            head->stock -= editStock;
            return;
        }
        Node *first = head, *second = head->link;
        while (first != NULL)
        {
            if (first->product_id == id)
            {
                break;
            }
            first = second;
            if (second != NULL)
                second = second->link;
        }
        first->stock -= editStock;
        return;
    }
};

class Cart : public Category
{
public:
    Node *createNode(Category *sections[15], int catNum, int id, int catId)
    {
        int pQty, flag = 0;
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->link = NULL;
        newNode->product_id = id;
        Node *temp = sections[catNum]->head;
        while (temp != NULL)
        {
            if (temp->product_id == id)
            {
                cout << "Enter desired quantity: ";
                cin >> pQty;
                if (temp->stock >= pQty)
                {
                    copy_n(temp->product_name, 32, newNode->product_name);
                    newNode->price = temp->price;
                    newNode->stock = pQty;
                    newNode->category = catId;
                    cout << newNode->product_name << " added to cart." << endl;
                    break;
                }
                else
                {
                    cout << "Entered quantity is not available!" << endl;
                    flag = 1;
                    break;
                }
            }
            temp = temp->link;
        }
        if (flag == 1)
            return nullptr;
        return newNode;
    }
    Node *push(Category *sections[15], Node *head, int catNum, int id, int catId)
    {
        Node *newNode = createNode(sections, catNum, id, catId);
        if (newNode != nullptr)
        {
            Node *temp = head;
            if (head == NULL)
            {
                return newNode;
            }
            while (temp->link != NULL)
            {
                temp = temp->link;
            }
            temp->link = newNode;
            newNode->link = NULL;
        }
        return head;
    }
    int listAll(Category *sections[15], Node *head)
    {
        double sum = 0;
        int confirm;
        Node *temp = head;
        Node *temp2 = head;
        for (int index = 0; index < 100; index++)
            cout << ".";
        cout << endl;
        if (temp == NULL)
        {
            cout << "Empty cart!" << endl
                 << endl;
            return 0;
        }
        cout << "Product ID\tProduct name\tPrice\t\tQty" << endl;
        while (temp != NULL)
        {
            cout << temp->product_id << "\t\t" << temp->product_name << "\t\t" << temp->price << "\t\t" << temp->stock << endl;
            sum += temp->price * temp->stock;
            temp = temp->link;
        }
        cout << endl;
        cout << "Total Amount: " << sum << "\t||\tGST (10%): " << 0.1 * sum << "\t||\tNet Total: " << 1.1 * sum << endl;
        sum *= 1.1;
        cout << "Confirm order? (0 - No | 1 - Yes) ";
        cin >> confirm;
        if (confirm == 1)
        {
            cout << "Your order has been placed successfully!" << endl;
            cout << "Your bill has been generated..." << endl;
            ofstream MyFile("bill.txt");
            MyFile << "Product ID\t\tProduct name\tPrice\t\tQty" << endl;
            while (temp2 != NULL)
            {
                for (int index = 0; index < 70; index++)
                    MyFile << ".";
                MyFile << endl;
                MyFile << temp2->product_id << "\t\t\t\t" << temp2->product_name << "\t\t\t" << temp2->price << "\t\t\t" << temp2->stock << endl;
                for (int index = 0; index < 70; index++)
                    MyFile << ".";
                MyFile << endl;
                sections[temp2->category]->updateStock2(sections[temp2->category]->head, temp2->product_id, temp2->stock);
                temp2 = temp2->link;
            }

            MyFile << endl;
            MyFile << "Total Amount: \t\t\t\t" << sum << endl;
            MyFile << "GST (10%): \t\t\t\t\t" << 0.1 * sum << endl;
            MyFile << "Net Total: \t\t\t\t\t" << 1.1 * sum << endl;
            for (int index = 0; index < 70; index++)
                MyFile << ".";
            MyFile << endl;
            MyFile.close();
            return 1;
        }
        return 0;
    }
    Node *editCart(Node *head)
    {
        int confirmChoice, pId;
        Node *temp = head;
        for (int index = 0; index < 100; index++)
            cout << ".";
        cout << endl;
        if (temp == NULL)
        {
            cout << "Empty cart!" << endl
                 << endl;
            return NULL;
        }
        cout << "Product ID\tProduct name\tPrice\t\tQty" << endl;
        while (temp != NULL)
        {
            cout << temp->product_id << "\t\t" << temp->product_name << "\t\t" << temp->price << "\t\t" << temp->stock << endl;
            temp = temp->link;
        }
        cout << endl;
        cout << "Delete any items? (0 - No | 1 - Yes) ";
        cin >> confirmChoice;
        if (confirmChoice == 1)
        {
            cout << "Enter product id: ";
            cin >> pId;
            head = pop(head, pId);
        }
        return head;
    }
};
