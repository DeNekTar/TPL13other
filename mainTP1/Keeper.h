#pragma once
#include "Characters.h"
#include <iostream>

class Keeper {

private:

    class Element {        //  ���� ������� � �������
    public:
        Characters* value;          //��������
        Element* prev;

        Element(Characters* data , Element* prev = nullptr) {    //����������� ��������
#ifdef DEBUGg
            std::cout << "Constructor Element\n";
#endif // DEBUG	
            this->value = data;
            this->prev = prev;
        }
    };
    int count;
    Element* head;      //��������� �� ������ �������
    Element* help;

public:
    Keeper() {
#ifdef DEBUGg
        std::cout << "Constuctor Keeper\n";
#endif // DEBUG	
        count = 0;
        head = nullptr;
        help = nullptr;
    }

    ~Keeper() {
#ifdef DEBUGg
        std::cout << "Destructor Keeper\n";
#endif // DEBUG	
        int b = getCount();
        for (int i = 1;i < b + 1;i++) {
           // std::cout << 'C' << getCount() << '\n';

            extractElement(i);
            //std::cout << 'C' << getCount() << '\n';

        }
        head = nullptr;
        help = nullptr;
    }


    int getCount() { return count; }

    Characters& operator[] (const int index) {

        int cnt = getCount();
        Element* cur;
        cur = this->head;

        while (cur != nullptr) {
            if (cnt == index) {
                return  *(cur->value);
            }
            cur = cur->prev;
            cnt--;
        }
    }

    void addElement(Characters* x) {
        if (head == nullptr) {
            head = new Element(x);
            head->value = x;

        }
        else {
            help = new Element(x);
            help->prev = head;
            head = help;
            head->value = x;
        }
        count++;
    }

    void extractElement(const int index) {	//����� �������� �������� �� �������

        if (1 == getCount()) {	//1 elem = head
            delete this->head;	
            count--;
            
        }
        else if (index == getCount()) {	//last
            Element* cur = this->head;	
            head = head->prev;	
            delete cur;			
            count--;	
        }
        else {		//not last and >1 elem
            Element* cur = this->head;		
            Element* current1 = this->head;		
            int c = getCount();	
            bool flag = 0;	
            while (flag != 1) {
                if (c == index) {		
                    int r = getCount();
                    while (r != (c + 1)) {
                        current1 = current1->prev;	
                        r--;
                    }
                    Element* temp = cur;		
                    cur = cur->prev;				
                    current1->prev = cur;		
                    delete temp -> prev;
                    delete temp;
                    flag = 1;	
                    count--;	

                }
                else {	
                    cur = cur->prev;	
                    c--;
                }
            }
            delete cur, current1;
        }
    }


    void display() {
        try {

            if (getCount() == 0) throw std::exception("��������� ���\n");

            std::cout << "\nAll Elements" << std::endl;
            help = head;
            int i = 1;

            while(help != nullptr){

                std::cout << "-------Element # " << i << "-------" << std::endl;
                (help->value)->display();
                help = help->prev;
                i++;
            }
            std::cout << "\nCount of Elements: " << getCount() << std::endl << std::endl;
        }
        catch (const std::exception& ex) {

            std::cout << ex.what() << '\n';
        }
    }


};

