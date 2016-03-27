#include <string.h>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;
struct nod {
    string nume;
    nod* next;
};
ifstream f;
ofstream g;
void add_map(nod* &current_node, string stare2);
void citire_vector( char vector[], int n){
    int cont = 0;
    char element;
    while( cont < n ){
        f >> element;
        vector[ cont ] = element;
        cont ++;
    }
}

void citire_vector( string vector[], int n){
    int cont = 0;
    string element;
    while( cont < n ){
        f >> element;
        vector[ cont ] = element;
        cont ++;
    }
}

void initialize_map(map < string,map < char, nod*> > &delta, string stare[],char litera[],int nr_litere, int nr_stari){

    for(int i=0; i < nr_stari;i++)
        for(int j = 0; j < nr_litere; j++)
            if (j < nr_litere-1) delta[ stare[i] ][litera [j]] = NULL;
            else {
                nod* node = new nod;
                node -> next = NULL;
                node -> nume = stare[i];
                delta[ stare[i] ][litera [j]] = node;
            }

}

void complete_map( map < string,map < char, nod*> > &delta, int nr_tranzitii ){

    int cont = 0;
    while( cont < nr_tranzitii){
        string stare1 , stare2;
        char lit;
        f>>stare1>>lit>>stare2;
        add_map( delta[ stare1 ][ lit ] , stare2);
        cont ++;
    }

}

void add_map(nod* &current_node, string stare2){
        nod* node = new nod;
        node -> next = NULL;
        node -> nume = stare2;
        if (current_node == NULL)
         current_node = node;

        else{

            nod* temp = current_node;
            while(temp -> next) temp = temp -> next;
            temp -> next = node;
        }

}

void show_map(map < string,map < char, nod*> > &delta,int nr_stari, int nr_litere, string stare[], char litera[]){

    for(int i=0; i < nr_stari;i++){
        for(int j = 0; j < nr_litere; j++)
            if (delta[ stare[i] ][litera [j]]) {
                cout<<"| ";
                nod*  temp = delta[ stare[i] ][litera [j]];
                while (temp){
                    cout<<temp->nume<<" ";
                    temp = temp -> next;
                }
                cout<<"| ";
            }

            else cout<<"NULL ";
        cout<<"\n";
   }

}

bool stare_finala(string stare, int nr_stari_finale, string stari_finale[]){
    for(int i = 0; i < nr_stari_finale; i++)
        if(stari_finale[i] == stare ) return 1;
    return 0;

}
void verifica_cuvant( map < string,map < char, nod*> > delta, string stare_curenta, string cuvant, int nr_stari_finale, string stari_finale[], bool* gasit){

    if(!*gasit){
        if ( cuvant.length() == 0 )
            if( stare_finala( stare_curenta, nr_stari_finale, stari_finale ) ){
                *gasit = true;
                    g << "DA\n";

            }
            else;
        else{
            // cout<<stare_curenta<<" -> "<<cuvant<<"\n";
            nod* temp = delta[stare_curenta][cuvant[0]];
            nod* temp2 = delta[stare_curenta]['.'] -> next;
            while(temp || temp2 && !*gasit)
                if (temp) {
             //  cout<<"--"<<temp -> nume<<" "<<cuvant<<" "<<*gasit<<"\n";
                string cuv = cuvant;
                verifica_cuvant(delta, temp -> nume, cuv.erase(0,1), nr_stari_finale, stari_finale, gasit);
                temp = temp->next;
                }
                else{
             //  cout<<"**"<<temp2 -> nume<<"--"<<cuvant<<" "<<*gasit<<"\n";
                verifica_cuvant(delta, temp2 -> nume, cuvant, nr_stari_finale, stari_finale, gasit);

                temp2 = temp2 -> next;
                }
            }
        }
}
int main(){
    int nr_stari, nr_litere, nr_stari_finale, nr_tranzitii, nr_teste;
    string stare_initiala;
    map < string,map < char, nod*> > delta;
    f.open( "LNFA.in" );
    f >> nr_stari;
    string stare[ nr_stari ];
    citire_vector( stare, nr_stari );
    f >> nr_litere;
    nr_litere ++;
    char litera[ nr_litere ];
    citire_vector( litera , nr_litere-1 );
    litera[ nr_litere-1 ] = '.';
    f >> stare_initiala;
    f >> nr_stari_finale;
    string stari_finale[ nr_stari_finale ];
    citire_vector( stari_finale , nr_stari_finale );
    initialize_map( delta, stare, litera ,  nr_litere, nr_stari );
    f >> nr_tranzitii;
    complete_map ( delta, nr_tranzitii );
    show_map( delta, nr_stari, nr_litere, stare, litera); //optional
    f >> nr_teste;
    bool* gasit = new bool;
    g.open("LNFA.out");

    for(int i = 0; i < nr_teste; i++){
        string cuvant_curent;
        f >> cuvant_curent;
        *gasit = false;
    verifica_cuvant( delta, stare_initiala, cuvant_curent, nr_stari_finale, stari_finale, gasit);
    if(!*gasit) g<<"NU\n";
    }
    f.close();
    g.close();

}
