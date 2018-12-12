//
//  main.cpp
//  HashTable
//
//  Created by Rodrigo Castro Ramos on 7/4/16.
//  Copyright © 2016 Rodrigo Castro Ramos. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <list>
#include <algorithm>
#include <thread>
#include <mutex>
#include <sstream>
#include <string>
#include <fstream>
#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */

#include <ctime> 
#include <pthread.h>
 
unsigned t0, t1;
std::mutex mut2;



using namespace std;



class Nodo{
public:
    float m_dimension[91];
};



class Dispersion{
public:

    int modulo(int numero, int total)
    {
        if(numero>0)
        {
            numero = numero%total;
            return numero;
        }
        if (numero<0)
        {
            while(numero<0)
            {
                numero = numero + total;
            }
        }
        return numero;
    }
    int lugar(vector<float> splitter, int size)
    {   
        int a = 0; 
        for(unsigned i = 0; i<91; i++)
        {
            a =  int(splitter[i]) + a;  
        }
        //  cout<<modulo(a,size)<<endl;
        return modulo(a,size);
    }
    int lugar_nodo(Nodo x, int size){

        Nodo y;
        int temp=0;
        for(int k = 0; k < 91; k++)
        {
            // a =  int(temporal[k]) + a;
            y.m_dimension[k]= 2.0;
            // x.m_dimension[k]= float(temporal[k]);
            temp = pow(y.m_dimension[k]-x.m_dimension[k],2) + temp;
        }
        temp = sqrt(temp);
        return modulo(temp,70769);
    }
};



class ListAdtor{
public:
    list<Nodo> l;
    bool find_list(Nodo x){
        list<Nodo>::iterator pos;
        int cont=0;      
        for(pos = l.begin(); pos != l.end(); ++pos) 
        {        
            for(int i = 0; i < 91; i++)
            {
                if (pos->m_dimension[i] == x.m_dimension[i]) {
                    cont++;
                }
                if (cont == 90) {
                    cout<<"si se encontro";
                    return 1;
                }
                      
            }   
        }
        cout<<"no se encontro"<<endl;
        return 0;
    }
    bool insert(Nodo x){
        // if (find_list(x))
        //     return 0;
        l.push_back(x);
        return 1;
    }
    void insert_p(Nodo x){
        // if (find_list(x))
        //     return 0;
        l.push_back(x);
        // cout<<"hola";

    }
    // bool remove(Nodo x){
    //     if (find_list(x))
    //         return 0;
    //     l.remove(x);
    //     return 1;
    // }
    void imprimir(){
        for (list<Nodo>::iterator it=l.begin(); it != l.end(); ++it){
          cout<<"este es la primero de muchas"<<endl;
          for(int i = 0; i < 91; i++)
          {
            cout << it->m_dimension[i]<<" , ";
          }
        }
        // cout << '\n';
    }

    int vecinos(Nodo x, int radio){
        cout<<"Esto son los vecinos mas cercanos"<<endl;
        int temp = 0;
        int cont = 0;
        for(list<Nodo>:: iterator it = l.begin(); it != l.end(); ++it)
        {
            
            for(int i = 0; i < 91; i++)
            {
                temp = pow(it->m_dimension[i]-x.m_dimension[i],2) + temp;
            }
            cout<<"este es el temp de vecino "<< temp<<endl;
            temp = sqrt(temp);
            cout<<temp<<endl;
            if (temp <= radio) {
                cont++;
            }
            
        }
        return cont;
        
    }

    void range_query(Nodo x, int rango){
        cout<<"Comiendo el range query"<<endl;
        
        for(list<Nodo>:: iterator it = l.begin(); it != l.end(); ++it)
        {
            /* code */
        }
        
    }
};



template<class F>
class c_HashTable
{
public:
    ListAdtor *m_ht;
    Dispersion m_f;
    int m_size;
    vector<string> all_words;
    
    c_HashTable(int size)
    {
        m_size=size;
        m_ht=new ListAdtor[m_size];
            ifstream lectura;
    string line = "";
    string word;
    lectura.open("YearPredictionMSD.txt",ios::in);
    //lectura.open("crime50k.csv",ios::in);
    cout << "Csv \n";

    while (getline(lectura, line))
    {
        stringstream strstr(line);
        word = "";
        float number=0;
        while (getline(strstr,word, ','))
        {
            all_words.push_back(word);

        }
    }
    lectura.close();
    cout<<all_words.size()<<endl;
    }
    
    bool _insert(Nodo x, vector<float> splitter)
    {
        // int id=m_f.lugar(splitter, m_size);
        int a = 0;
        for(int i = 0; i < 91; i++)
        {
            a =  int(splitter[i]) + a;
            x.m_dimension[i]= float(splitter[i]);
        }
        int id2 = m_f.modulo(a,m_size);
        
        //cout<< x <<" -> "<<id<<endl;
        return m_ht[id2].insert(x);
    }
    void _insert_mutex(int ini, int fin, vector<float> splitter){
        for(unsigned int i=ini;i<fin;i=i+91)
            {
                // ht._insert(float(splitter[0]));
                Nodo x;
                Nodo y;
                vector<float> temporal;
                // cout<<"entre aqeui"<<endl;
                for(unsigned int j = 0; j<91; j++){
                    // cout<<"segundo for"<<endl;
                    temporal.push_back(stof(all_words[i+j]));
                }
                int a = 0;
                int temp=0;
                for(int k = 0; k < 91; k++)
                {
                    a =  int(temporal[k]) + a;
                    y.m_dimension[k]= 2.0;
                    x.m_dimension[k]= float(temporal[k]);
                    temp = pow(y.m_dimension[k]-x.m_dimension[k],2) + temp;
                }
                temp = sqrt(temp);
                int id2 = m_f.modulo(temp,m_size);
                mut2.lock();
                //cout<< x <<" -> "<<id<<endl;
                m_ht[id2].insert_p(x);
                mut2.unlock();
            }
            // cout<<"hola";
    }

    void insert_paralelo( int tam, vector<float> splitter){
        unsigned int nthreads = std::thread::hardware_concurrency();
        tam = all_words.size()/nthreads;
        vector <thread> ths(nthreads);
        for (int i =0 ; i<nthreads; i++, tam = tam+ all_words.size()/nthreads){
            ths[i] =std:: thread(_insert_mutex, tam, splitter);
            ths[i].join();
        }
        cout<<"este es el size de mi vector"<<endl;
    }

    
    // bool remove(Nodo x, vector<float> splitter)
    // {
    //     int id=m_f.lugar(splitter, 102677);
    //     return m_ht[id].remove(x);
    // }
    
    bool find(Nodo x)
    {
        int id=m_f.lugar_nodo(x, m_size);
        return m_ht[id].find_list(x);
    }
    
    void imprimir()
    {
        for(int i=0; i<m_size;i++)
        {
            m_ht[i].imprimir();
        }
    }

    int knn(Nodo x, int radio){
        int id  = m_f.lugar_nodo(x, m_size);
        int cont = 0;
        for(int i = 0; i < radio; i++)
        {
            cont = m_ht[id].vecinos(x, radio) + cont;
            id++;
        }
        cout<< cont << " este es con cont del knn"<<endl;
        return cont;
    }

    void rangeQuery(Nodo x, int rango){
        int id = m_f.lugar_nodo(x, m_size);
        
        for(int i = 0; i < rango; i++)
        {
            m_ht[id+i].imprimir();
        }
        
    }
    
    
};

int main() {
    // insert code here...
    // c_HashTable<Nodo> ht(102677);
    c_HashTable<Nodo> * myHash = new c_HashTable<Nodo>(70769);
    cout<<"probando aqui "<<myHash->all_words.size();
    vector<float>splitter;
    t0=clock();
    std::thread th(&c_HashTable<Nodo>::_insert_mutex, myHash,  0,  5687500, splitter);
    std::thread th1(&c_HashTable<Nodo>::_insert_mutex, myHash,  5687500, 11375000, splitter);
    std::thread th2(&c_HashTable<Nodo>::_insert_mutex, myHash,  11375000, 17062500, splitter);
    std::thread th3(&c_HashTable<Nodo>::_insert_mutex, myHash,  17062500, 22750000, splitter);
    std::thread th4(&c_HashTable<Nodo>::_insert_mutex, myHash,  22750000,  28437500, splitter);
    std::thread th5(&c_HashTable<Nodo>::_insert_mutex, myHash,  28437500, 34125000, splitter);
    std::thread th6(&c_HashTable<Nodo>::_insert_mutex, myHash,  34125000, 39812500, splitter);
    std::thread th7(&c_HashTable<Nodo>::_insert_mutex, myHash,  39812500, myHash->all_words.size(), splitter);

    th.join();
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time/8 << endl;










    // t0=clock();
    // for(unsigned int i=0;i<myHash->all_words.size();i=i+91)
    // {
    //     // ht._insert(float(splitter[0]));
    //     Nodo x;
    //     vector<float> temporal;
    //     // cout<<"entre aqeui"<<endl;
    //     for(unsigned int j = 0; j<91; j++){
    //         // cout<<"segundo for"<<endl;
    //         temporal.push_back(stof(myHash->all_words[i+j]));
    //     }
    //     myHash->_insert(x, temporal);
    // }
    // t1 = clock();
    // // Nodo x;
    // // vector<float>splitter;
    // // ht.insert_paralelo(x, 0, splitter);
 
    // double time = (double(t1-t0)/CLOCKS_PER_SEC);
    // cout << "Execution Time: " << time << endl;



    // // ht.imprimir();
    // // return 0;
    Nodo prueba;
     for(int j = 91*1456; j < 91*1457; j++)
        {
            prueba.m_dimension[j-(91*1456)] = stof(myHash->all_words[j]);
        }
    // ht.imprimir();
    myHash->find(prueba);
    // myHash->rangeQuery(prueba,1);
    t0=clock();
    myHash->knn(prueba,200);
    t1 = clock();
 
    time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    // unsigned int nthreads = std::thread::hardware_concurrency();
    // cout<<"numero de threads "<<nthreads;
    int size;
    cout<<endl;
    cout<<"es el sizeof "<<sizeof(*myHash);
    cout<<"este es el size de la estructura "<< size<<endl;
    delete myHash;

    return 0;
}
