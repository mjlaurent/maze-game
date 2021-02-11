//ONLY SUBMIT THIS FILE TO ZINC
#include "given.h"
#include "todo.h"
#include <iostream>
using namespace std;
//be reminded that you should NOT include any additional library, please read "Additional Notes" on the PA3 webpage 
// g++ -std=c++11 *.cpp -o pa3.o && ./pa3.o
Node*** generateMap(int width, int height)
{
    // Initiliaze Head Pointers
    Node*** head = new Node** [height];
    
    // Initialize the HEIGHT of 2D Dynamic Array
    for (int i = 0 ; i < height ; ++i)
    {
        head[i] = new Node* [width];
    }

    // Initialize the WIDTH and the CONTENT of the 2D Dynamic Array
    for(int i = 0 ; i < height ; ++i)
    {
        for(int j = 0 ; j < width ; ++j)
        {
            head[i][j] = nullptr;
        }
    }

    // Return Statement
    return head; 
}

void printHeroStatus(const HeroStatus& heroStatus)
{
    cout << "Hero status: x=" << heroStatus.x << " y=" << heroStatus.y << " #mace=" << heroStatus.maceCount << " #dagger=" << heroStatus.daggerCount << " #sword=" << heroStatus.swordCount << endl; 
}

void printMonsterCount(Node*** map, int width, int height)
{
    int count = 0;
    count = getMonsterCount(map, width, height);
    if(count == 1)
    {
        cout << "There is still one more monster left!"<<endl;
    }
    else
    {
        cout << "There are "<< count <<" monsters left in the world!" << endl;
    }
}

int getLinkedListLength(const Node* head)
{
    const Node* p = head;
    if (p == nullptr)
        return 0;
    else
    {
        int len = 0;
        while (p != nullptr)
        {
            len++;
            p = p->next;
        }
        return len;
    }
    
    return 0;
}

bool addThing(Node*** map, int width, int height, int x, int y, Thing thing, int quantity)
{
    // Out of range input
    if (x < 0 || y < 0 || x > width || y > height)
        return false;
    
    // addThing Operation
    // Empty Linked List
    if (map[y][x] == nullptr)
    {
        // New Node
        Node* newNode = new Node;
        newNode->thing = thing;
        newNode->quantity = quantity;
        newNode->next = nullptr;
        map[y][x] = newNode;
    }
    // Not Empty Linked List
    else if (map[y][x] != nullptr)
    {
        Node* temp = nullptr;
        temp = map[y][x];
        while (temp != nullptr && temp->thing != thing)
            temp = temp->next;

        // Existing Item
        if (temp != nullptr)
        {
            temp->quantity += quantity;
        }
        // New Item
        else
        {
            // New Node
            Node* newNode = new Node;
            Node* p = nullptr;
            p = map[y][x];
            while( p->next != nullptr)
                p = p->next;
                
            newNode -> thing = thing;
            newNode -> quantity = quantity;
            newNode -> next = nullptr;
            p -> next = newNode;
            
        }
    }
    return true;
}

bool removeThing(Node*** map, int width, int height, int x, int y, Thing thing, int quantity)
{
    // Out of range input
    if (x < 0 || y < 0 || x > width || y > height)
        return false;

    // removeThing operation

    // LL not empty 
    if (map[y][x] != nullptr)
    {
        Node* p = nullptr;
        p = map[y][x];

        // Find the Node
        while (p != nullptr && p->thing != thing)
            p = p->next;
        
        // Item not found
        if (p == nullptr)
        {
            //cout << "abort" << endl;
            return false;
        }
            
        
        // Removing the item

        // Quantity smaller than remove
        if (p->quantity < quantity)
        {
            //cout << "case 1" << endl;
            return false;
        }

        // Quantity more than remove
        else if (p->quantity > quantity)
        {
            //cout << "case 2" << endl;
            p->quantity -= quantity;
        }

        // Quantity equals to remove , Remove Node also
        else if (p->quantity == quantity)
        {
            //cout << "case 3" << endl;
            // First and Middle Position 
            Node* prev = nullptr;
            Node* current = map[y][x];

            while (current != nullptr && current->thing != thing)
            {
                prev = current;
                current = current->next;
            }
            if (current != nullptr)
            {
                if (current == map[y][x])
                    map[y][x] = map[y][x]->next;
                else
                    prev->next = current->next;
                delete current;
            }
        }

    }

    // LL empty
    else if (map[y][x] == nullptr)
    {
        //cout << "no ll" << endl;
        return false;
    }
        
    return true;
}

void deleteLinkedList(Node*& head)
{
    // Empty
    if (head == nullptr)
        return;
    
    // Recursion
    deleteLinkedList(head->next);

    delete head;
    head = nullptr;
}

void deleteMap(Node*** map, int width, int height)
{
    for (int y = 0 ; y < height ; ++y)
    {
        for(int x = 0 ; x < width ; ++x)
        {
            deleteLinkedList(map[y][x]);
        }
        delete [] map[y];
    }
    delete [] map;
}

bool moveHero(char move, Node*** map, int width, int height, HeroStatus &heroStatus)
{
    // Invalid Move
    if ((move == 'a' && heroStatus.x == 0) || (move == 'd' && heroStatus.x == width-1) || (move == 'w' && heroStatus.y == 0) || (move == 's' && heroStatus.y == height-1))
        return false;
    
    // Initial Value
    bool isLosing = false;
    int init_x = heroStatus.x , init_y = heroStatus.y ;
    int new_x = init_x, new_y = init_y;
    

    if (move == 'w')
        new_y = init_y-1;
    else if (move == 's')
        new_y = init_y+1;
    else if (move == 'a')
        new_x = init_x-1;
    else if (move == 'd')
        new_x = init_x+1;
    
    // Update Struct
    heroStatus.x = new_x;
    heroStatus.y = new_y;

    // if the map is not empty
    if (map[new_y][new_x] != nullptr)
    {
        // Acquire weapon 
        if((map[new_y][new_x]->thing == 0) || (map[new_y][new_x]->thing == 1) || (map[new_y][new_x]->thing == 2))
        {
            Node* p = nullptr;
            p = map[new_y][new_x];
            while(p != nullptr)
            {
                if (p->thing == 0)
                {
                    heroStatus.maceCount += p->quantity;
                
                }
                if (p->thing == 1)
                {
                    heroStatus.daggerCount += p->quantity;
                    
                }
                if (p->thing == 2)
                {
                    heroStatus.swordCount += p->quantity;
                    
                }
                p = p->next;
            }
        }

        // Fight with the Monster
        if((map[new_y][new_x]->thing == 3) || (map[new_y][new_x]->thing == 4) || (map[new_y][new_x]->thing == 5))
        {
            Node* temp = nullptr;
            temp = map[new_y][new_x];
            while(temp != nullptr)
            {
                if (temp->thing == 3)
                {
                    if (temp->quantity > heroStatus.maceCount)
                        isLosing = true;
                }
                if (temp->thing == 4)
                {
                    if (temp->quantity > heroStatus.daggerCount)
                        isLosing = true;
                }
                if (temp->thing == 5)
                {
                    if (temp->quantity > heroStatus.swordCount)
                        isLosing = true;
                }
                temp = temp->next;
            }

            if(!isLosing)
            {
                Node* fight = nullptr;
                fight = map[new_y][new_x];
                while(fight != nullptr)
                {
                    if (fight->thing == 3)
                    {
                        heroStatus.maceCount -= fight->quantity;
                    }
                    if (fight->thing == 4)
                    {
                        heroStatus.daggerCount -= fight->quantity;
                    }
                    if (fight->thing == 5)
                    {
                        heroStatus.swordCount -= fight->quantity;
                    }
                    fight = fight->next;
                }
            }
        }


    }
    // Move the hero && Empty Cell
    if(!isLosing)
    {
        Node* deleting = map[new_y][new_x];
        deleteLinkedList(deleting);
        map[new_y][new_x] = nullptr;
        Node* temp = nullptr;
        temp = map[init_y][init_x];
        map[new_y][new_x] = temp;
        map[init_y][init_x] = nullptr; 
    }

    else if(isLosing)
    {
        heroStatus.alive = false;
        delete map[init_y][init_x];
        map[init_y][init_x] = nullptr;
    }
    
    return true;
}

int getMonsterCount(Node*** map, int width, int height)
{
    int count = 0;
    for(int y = 0; y < height ; ++y)
    {
        for(int x = 0 ; x < width ; ++x)
        {
            if(map[y][x] != nullptr)
            {
                Node* p = nullptr;
                p = map[y][x];
                while (p != nullptr)
                {
                    if (p->thing == 3 || p->thing == 4 || p->thing == 5)
                        count += p->quantity;
                    // Iterate
                    p = p ->next;
                }
            }
        }
    }
    return count;
}
