#include <iostream>
#include <stdlib.h>
#include <locale.h>
#include <ctime>
#include <string.h>
#include <windows.h>
#include <fstream>




using namespace std;

enum Gender {Female, Male};

struct pet {
    int code;
    char name[21];
    char type[11];
    char breed[31];
    Gender gender;
    int age;
    float weight;
    struct pet* next;
};

//INICIALIZANDO AS FUNÇÕES
void insertEnd(pet **list, int code, char name[], char type[], char breed[], Gender gender, int age, float weight);
void createPet(pet **list);
void printPetRec(pet *list);
void removePet (pet **list);
void removePetByCode( pet **list, int code, char name[]);
void changePet(pet **list);
int getCount(pet *list);
int getCountType(pet *list, char type[]);
pet* searchByName(pet *list, char name[]);
void searchByType(pet *list);
void searchByTypeAndBreed(pet *list);
pet* searchByCode (pet*list, int code);
void restoreBackup(pet **list, ifstream &infile);
int findHighestCode(pet* list);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



void insertEnd(pet **list, int code, char name[], char type[], char breed[], Gender gender, int age, float weight) {
    pet *head = new pet;
    try {
        head->code = code;
        strcpy(head->name, name);
        strcpy(head->type, type);
        strcpy(head->breed, breed);
        head->gender = gender;
        head->age = age;
        head->weight = weight;
        head->next = NULL;
        if((*list) == NULL) (*list) = head;
        else {
            pet *temp = (*list);
            while(temp->next) temp = temp->next;
            temp->next = head;
        }
    } catch (const char * err) {
        cout<<"\nErro: " << err << "\n";
        throw;
    }
    
}


Gender selectGender(int option) {
    return static_cast<Gender>(option);
}

int findHighestCode (pet* list) {
    int nextCode = 0;

    while (list) {
        if (list->code > nextCode)
            nextCode = list->code;
        list = list->next;
    }

    nextCode++;


    return nextCode;
}

void createPet(pet **list) {
    pet data;

    int tempGender;
    try {
        SetConsoleTextAttribute(hConsole, 9); cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<< endl;
        SetConsoleTextAttribute(hConsole, 11); cout << "       Informações do"; 
        SetConsoleTextAttribute(hConsole, 10); cout << " Pet"; 
        SetConsoleTextAttribute(hConsole, 11); cout << " a ser adicionado \n    (Não utilize espaços, utilize underline _)" << endl;
        SetConsoleTextAttribute(hConsole, 9); cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<< endl << endl;
        SetConsoleTextAttribute(hConsole, 14); cout << "Nome"; 
        SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> data.name; //name = input();
        SetConsoleTextAttribute(hConsole, 14); cout << "Espécie";
        SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> data.type;
        SetConsoleTextAttribute(hConsole, 14); cout << "Raça"; 
        SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> data.breed;
        do {
            cin.ignore();
			if(cin.fail())
        	{
            cin.clear();
            cin.ignore(1200, '\n');
            SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente números.\n";
        	} while(cin.fail());
            SetConsoleTextAttribute(hConsole, 14); cout << "Sexo ";
            SetConsoleTextAttribute(hConsole, 15); cout << "(";
            SetConsoleTextAttribute(hConsole, 13); cout << "Fêmea = 1";
            SetConsoleTextAttribute(hConsole, 15); cout << "/";
            SetConsoleTextAttribute(hConsole, 11); cout << "Macho = 2";
            SetConsoleTextAttribute(hConsole, 15); cout << "): "; 
            SetConsoleTextAttribute(hConsole, 15); cin >> tempGender;
        } while(tempGender != 1 && tempGender != 2);
        data.gender = selectGender(tempGender - 1);
        do {
			if(cin.fail())
        	{
            cin.clear();
            cin.ignore(1200, '\n');
            SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente números.\n";
        	}while(cin.fail());
            SetConsoleTextAttribute(hConsole, 14); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> data.age;
        } while(cin.fail() || data.age < 0 || data.age > 500);
        do {
			if(cin.fail())
        	{
            cin.clear();
            cin.ignore(1200, '\n');
            SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente números.\n";
        	}while(cin.fail());
            SetConsoleTextAttribute(hConsole, 14); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> data.weight;
        }while(cin.fail() || data.weight < 0 || data.weight > 500);
        
        int code = findHighestCode(*list);

        insertEnd(list, code, data.name, data.type, data.breed, data.gender, data.age, data.weight);
    } catch (const char *err) {
        SetConsoleTextAttribute(hConsole, 12); cout<<"\nErro: " << err << endl;
    }
}


void printPetRec(pet *list) {
    if (getCount(list) != 0)
    { 
        if(list) {
            SetConsoleTextAttribute(hConsole, 10); cout << "Código";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->code << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Nome";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->name << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Espécie";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->type << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Raça";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->breed << endl;
            if(list->gender == Female)
            {
                SetConsoleTextAttribute(hConsole, 10); cout << "Sexo";
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";
                SetConsoleTextAttribute(hConsole, 13); cout <<"Fêmea"<< endl;
            }
            else
            { 
                SetConsoleTextAttribute(hConsole, 10); cout << "Sexo: ";
                SetConsoleTextAttribute(hConsole, 11); cout <<"Macho" << endl;
            }
            SetConsoleTextAttribute(hConsole, 10); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->age << " anos" << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->weight << "kg" << endl << endl;
            printPetRec(list->next);
        }
    }
}


void removePet (pet **list) {
    char name[21];

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite o nome do pet a ser";
    SetConsoleTextAttribute(hConsole, 12); cout <<" removido";
    SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> name;
    cin.ignore();
    
    pet *target = *list;

    while(target && strcmp(target->name, name) != 0) target = target->next;

    pet* listPetsWithName = searchByName(*list, name);
    int count = getCount(listPetsWithName);

    if (count == 0) {
        SetConsoleTextAttribute(hConsole, 12); cout << "Pet [";
		SetConsoleTextAttribute(hConsole, 15); cout << name;
		SetConsoleTextAttribute(hConsole, 12); cout << "] não encontrado!" << endl;
        return;
    }
    else {
        int seekedCode;
        if (count > 1) 
        {
        	SetConsoleTextAttribute(hConsole, 15); cout<<"Códigos de pets chamados [";
			SetConsoleTextAttribute(hConsole, 13);cout<<name;
			SetConsoleTextAttribute(hConsole, 15);cout<< "] disponíveis para remoção: | ";
            while(listPetsWithName) { 
			SetConsoleTextAttribute(hConsole, 10); cout<<listPetsWithName->code;
			SetConsoleTextAttribute(hConsole, 15);cout<<" | ";  
			listPetsWithName = listPetsWithName->next;}
            SetConsoleTextAttribute(hConsole, 15); cout<<"\nDigite o código do pet a ser removido: "; cin >> seekedCode;
            target = searchByCode(*list, seekedCode);
        }
        if(target == NULL) {
            SetConsoleTextAttribute(hConsole, 12); cout << "Pet ["; 
            SetConsoleTextAttribute(hConsole, 15); cout << name;
            SetConsoleTextAttribute(hConsole, 12); cout << "] e código [";
			SetConsoleTextAttribute(hConsole, 15); cout<<seekedCode;
			SetConsoleTextAttribute(hConsole, 12); cout<<"] não encontrado!" << endl;
            //return;
        } else {         

            SetConsoleTextAttribute(hConsole, 10); cout << "Pet ["; 
			SetConsoleTextAttribute(hConsole, 15); cout << name;
			SetConsoleTextAttribute(hConsole, 10); cout << "] removido com sucesso!" << endl;
            // Se target ï¿½ o primeiro da lista 
            if(target == *list) {
                *list = target->next;
                delete target;
                return;
            }
            // Se target está no meio da lista
            pet *temp = *list;
            while(temp->next != target) temp = temp->next;
            temp->next = target->next;
            delete target;
        }
    }
}

pet* searchByCode (pet*list, int code) {
    int count = 0;

    pet* foundByCode = NULL;

    while(list) {
        if(list->code == code) {
            foundByCode = list;
            SetConsoleTextAttribute(hConsole, 10); cout << "Nome";
            SetConsoleTextAttribute(hConsole, 15); cout << ":" << list->name << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Espécie";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->type << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Raça";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->breed << endl;
            if(list->gender == Female)
            {
                SetConsoleTextAttribute(hConsole, 10); cout << "Sexo";
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";
                SetConsoleTextAttribute(hConsole, 13); cout <<"Fêmea"<< endl;
            }
            else
            { 
                SetConsoleTextAttribute(hConsole, 10); cout << "Sexo: ";
                SetConsoleTextAttribute(hConsole, 11); cout <<"Macho" << endl;
            }
            SetConsoleTextAttribute(hConsole, 10); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->age << " anos" << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->weight << "kg" << endl << endl;
            count++;
        }
        list = list->next;
    }

    if (count > 1) {
        SetConsoleTextAttribute(hConsole, 15); cout << "Erro! Foram encontrados mais de 1 ("; 
        SetConsoleTextAttribute(hConsole, 10); cout << count << ") pets cadastrados com o codigo ["; 
        SetConsoleTextAttribute(hConsole, 15); cout << code << "]" << endl;

        return NULL;
    }

    return foundByCode;
}

void changePet(pet **list) {
    char name[21];

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite o nome do pet a ser ";
    SetConsoleTextAttribute(hConsole, 13); cout << "alterado";
    SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> name;
    cin.ignore();

    pet *target = *list;

    while(target && strcmp(target->name, name) != 0) target = target->next;

    pet* listPetsWithName = searchByName(*list, name);
    int count = getCount(listPetsWithName);

    if(count == 0) {
        SetConsoleTextAttribute(hConsole, 12); cout << "Pet ["; 
        SetConsoleTextAttribute(hConsole, 15); cout << name;
        SetConsoleTextAttribute(hConsole, 12); cout << "] não encontrado!" << endl;
    }
    else {
        int tempGender;
        try {
            int seekedCode;
            if (count > 1) {
                SetConsoleTextAttribute(hConsole, 15); cout<<"Códigos de pets chamados [";
				SetConsoleTextAttribute(hConsole, 13);cout<<name;
				SetConsoleTextAttribute(hConsole, 15);cout<< "] disponíveis para remoção: | ";
                while(listPetsWithName) { 
				SetConsoleTextAttribute(hConsole, 10); cout<<listPetsWithName->code;
				SetConsoleTextAttribute(hConsole, 15);cout<<" | ";  
				listPetsWithName = listPetsWithName->next;}
                cout<<"\nDigite o código do pet a ser alterado: "; cin >> seekedCode;
                target = searchByCode(*list, seekedCode);
            }
            if(target == NULL) {
                SetConsoleTextAttribute(hConsole, 12); cout << "Pet ["; 
                SetConsoleTextAttribute(hConsole, 15); cout << name;
                SetConsoleTextAttribute(hConsole, 12); cout << "] e código ["<<seekedCode<<"] não encontrado!" << endl;
            } else {
                SetConsoleTextAttribute(hConsole, 15);cout <<"\nO pet retornado tem nome [";
				SetConsoleTextAttribute(hConsole, 13);cout <<target->name;
				SetConsoleTextAttribute(hConsole, 15);cout <<"] e código [";
				SetConsoleTextAttribute(hConsole, 10); cout<<target->code;
				SetConsoleTextAttribute(hConsole, 15); cout<<"]"<<endl;
                SetConsoleTextAttribute(hConsole, 1); cout << "\n=-=-=-=-=-=- ";
                SetConsoleTextAttribute(hConsole, 11); cout << "Informações do Pet a ser alterado";
                SetConsoleTextAttribute(hConsole, 1); cout << " -=-=-=-=-=-=\n" << endl;
                SetConsoleTextAttribute(hConsole, 14); cout << "Novo Nome"; 
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";cin >> target->name;
                SetConsoleTextAttribute(hConsole, 14); cout << "Nova Espécie"; +
                
                SetConsoleTextAttribute(hConsole, 15); cout << ": "; cin >> target->type;
                SetConsoleTextAttribute(hConsole, 14); cout << "Nova Raça "; 
                SetConsoleTextAttribute(hConsole, 15); cout<< ": "; cin >> target->breed;
                do{
                    cin.ignore();
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1200, '\n');
                        SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente números.\n";
                    }while(cin.fail());
                    SetConsoleTextAttribute(hConsole, 14); cout << "Novo Sexo ";
                    SetConsoleTextAttribute(hConsole, 15); cout <<"(";
                    SetConsoleTextAttribute(hConsole, 13); cout <<"Fêmea = 1"; 
                    SetConsoleTextAttribute(hConsole, 15); cout <<"/"; 
                    SetConsoleTextAttribute(hConsole, 11); cout << "Macho = 2";
                    SetConsoleTextAttribute(hConsole, 15); cout <<"): "; cin >> tempGender;
                    }while(tempGender != 1 && tempGender != 2);
                target->gender = selectGender(tempGender - 1);
                do{
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1200, '\n');
                        SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente números.\n";
                    }while(cin.fail());
                    SetConsoleTextAttribute(hConsole, 14); cout << "Nova Idade: "; 
                    SetConsoleTextAttribute(hConsole, 15); cin >> target->age;
                    }while(cin.fail() || target->age < 0 || target->age > 500);
                do{
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(1200, '\n');
                        SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente números.\n";
                    }while(cin.fail());
                    SetConsoleTextAttribute(hConsole, 14); cout << "Novo Peso: "; 
                    SetConsoleTextAttribute(hConsole, 15); cin >> target->weight;
                }while(cin.fail() || target->weight < 0 || target->weight > 500);     
            }       
        } catch (const char *err) {
            SetConsoleTextAttribute(hConsole, 12); cout<<"\nErro: " << err << endl;
        }
    }

}

int getCount(pet *list) {
    if (list == NULL) return 0;

    int count = 0;

    while (list) {
        count++;
        list = list->next;
    }
    

    return count;
}

int getCountType(pet *list, char type[]) {
    if (list == NULL) return 0;

    int count = 0;

    while(list) {
        if(strcmp(list->type, type) == 0) {
            count++;
        }
        list = list->next;
    }
    return count;
}


pet* searchByName(pet *list, char name[]) {
    int count = 0;

    pet* foundByName = NULL;
    while(list) {
        if(strcmp(list->name, name) == 0) {
            insertEnd(&foundByName, list->code, list->name, list->type, list->breed, list->gender, list->age, list->weight);
            count++;
        }
        list = list->next;
    }
    if (count == 0){
        SetConsoleTextAttribute(hConsole, 12); cout << "Não foi encontrado nenhum pet chamado ["; 
        SetConsoleTextAttribute(hConsole, 15); cout << name ;
        SetConsoleTextAttribute(hConsole, 12); cout << "]"<< endl;
        return NULL;
        }
    SetConsoleTextAttribute(hConsole, 15); cout << "Encontrado ["; 
    SetConsoleTextAttribute(hConsole, 10); cout << count;
    if (count > 1){
        SetConsoleTextAttribute(hConsole, 15); cout << "] pets chamados [";
		SetConsoleTextAttribute(hConsole, 13); cout<< name;
		SetConsoleTextAttribute(hConsole, 15); cout << "]" << endl;}
    else if (count == 1){
        SetConsoleTextAttribute(hConsole, 15); cout << "] pet chamado ";
        SetConsoleTextAttribute(hConsole, 15); cout<< name << endl;
    }

    return foundByName;
}


void searchByType(pet *list) {
    char type[11];
    int count = 0;

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
    SetConsoleTextAttribute(hConsole, 13); cout << "espécie ";
    SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
    cin >> type;
    cin.ignore();
    cout << endl;
    while(list) {
        if(strcmp(list->type, type) == 0) {

            SetConsoleTextAttribute(hConsole, 10); cout << "Nome";
            SetConsoleTextAttribute(hConsole, 15); cout << ":" << list->name << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Espécie";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->type << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Raça";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->breed << endl;
            if(list->gender == Female)
            {
                SetConsoleTextAttribute(hConsole, 10); cout << "Sexo";
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";
                SetConsoleTextAttribute(hConsole, 13); cout <<"Fêmea"<< endl;
            }
            else
            { 
                SetConsoleTextAttribute(hConsole, 10); cout << "Sexo: ";
                SetConsoleTextAttribute(hConsole, 11); cout <<"Macho" << endl;
            }
            SetConsoleTextAttribute(hConsole, 10); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->age << " anos" << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->weight << "kg" << endl << endl;
            count++;
        }
        list = list->next;
    }
    if (count == 0){
        SetConsoleTextAttribute(hConsole, 12); cout << "Não foi encontrado nenhum pet da espécie ["; 
        SetConsoleTextAttribute(hConsole, 15); cout << type ;
        SetConsoleTextAttribute(hConsole, 12); cout << "]"<< endl;
    }
    else{
        SetConsoleTextAttribute(hConsole, 15); cout << "Encontrado ["; 
        SetConsoleTextAttribute(hConsole, 10); cout << count << " "; 
        SetConsoleTextAttribute(hConsole, 15); cout << type << "] " << endl;}
}


void searchByTypeAndBreed(pet *list) {
    char type[11];
    char breed[31];
    int count = 0;

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
    SetConsoleTextAttribute(hConsole, 13); cout << "espécie ";
    SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
    cin >> type;
    cin.ignore();

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
    SetConsoleTextAttribute(hConsole, 13); cout << "raça ";
    SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
    cin >> breed;
    cin.ignore();
    cout << endl;
    while(list) {
        if(strcmp(list->type, type) == 0 && strcmp(list->breed, breed) == 0) {
            SetConsoleTextAttribute(hConsole, 10); cout << "Nome";
            SetConsoleTextAttribute(hConsole, 15); cout << ":" << list->name << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Espécie";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->type << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Raça";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->breed << endl;
            if(list->gender == Female)
            {
                SetConsoleTextAttribute(hConsole, 10); cout << "Sexo";
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";
                SetConsoleTextAttribute(hConsole, 13); cout <<"Fêmea"<< endl;
            }
            else
            { 
                SetConsoleTextAttribute(hConsole, 10); cout << "Sexo: ";
                SetConsoleTextAttribute(hConsole, 11); cout <<"Macho" << endl;
            }
            SetConsoleTextAttribute(hConsole, 10); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->age << " anos" << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->weight << "kg" << endl << endl;
            count++;
        }
        list = list->next;
    }
    if (count == 0){
        SetConsoleTextAttribute(hConsole, 12); cout << "Não foi encontrado nenhum pet da espécie ["; 
        SetConsoleTextAttribute(hConsole, 15); cout << type;
        SetConsoleTextAttribute(hConsole, 12); cout << "] e raça [";
        SetConsoleTextAttribute(hConsole, 15); cout << breed;
        SetConsoleTextAttribute(hConsole, 12); cout << "]"<< endl;
    }
    else{
        SetConsoleTextAttribute(hConsole, 15); cout << "Encontrado ["; 
        SetConsoleTextAttribute(hConsole, 10); cout << count;
        SetConsoleTextAttribute(hConsole, 15); cout << "] "; 
        SetConsoleTextAttribute(hConsole, 15); cout << type << " ";
        SetConsoleTextAttribute(hConsole, 15); cout<< breed << endl;
    }
}

void searchByTypeBreedAndGender(pet *list) {
    char type[11];
    char breed[31];
    int gender;
    int count = 0;

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
    SetConsoleTextAttribute(hConsole, 13); cout << "espécie ";
    SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
    cin >> type;
    cin.ignore();

    SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
    SetConsoleTextAttribute(hConsole, 13); cout << "raça ";
    SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
    cin >> breed;
    cin.ignore();

    do {
        SetConsoleTextAttribute(hConsole, 14); cout << "Sexo ";
        SetConsoleTextAttribute(hConsole, 15); cout << "(";
        SetConsoleTextAttribute(hConsole, 13); cout << "Fêmea = 1";
        SetConsoleTextAttribute(hConsole, 15); cout << "/";
        SetConsoleTextAttribute(hConsole, 11); cout << "Macho = 2";
        SetConsoleTextAttribute(hConsole, 15); cout << "): "; 
        cin >> gender;
    } while(gender != 1 && gender != 2);
    cout << endl;
    while(list) {
        if(strcmp(list->type, type) == 0 && strcmp(list->breed, breed) == 0 && list->gender == selectGender(gender - 1)) {
            SetConsoleTextAttribute(hConsole, 10); cout << "Nome";
            SetConsoleTextAttribute(hConsole, 15); cout << ":" << list->name << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Espécie";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->type << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Raça";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->breed << endl;
            if(list->gender == Female)
            {
                SetConsoleTextAttribute(hConsole, 10); cout << "Sexo";
                SetConsoleTextAttribute(hConsole, 15); cout << ": ";
                SetConsoleTextAttribute(hConsole, 13); cout <<"Fêmea"<< endl;
            }
            else
            { 
                SetConsoleTextAttribute(hConsole, 10); cout << "Sexo: ";
                SetConsoleTextAttribute(hConsole, 11); cout <<"Macho" << endl;
            }
            SetConsoleTextAttribute(hConsole, 10); cout << "Idade";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->age << " anos" << endl;
            SetConsoleTextAttribute(hConsole, 10); cout << "Peso";
            SetConsoleTextAttribute(hConsole, 15); cout << ": " << list->weight << "kg" << endl << endl;
            count++;
        }
        list = list->next;
    }
    if (count == 0){
        SetConsoleTextAttribute(hConsole, 12); cout << "Não foi encontrado nenhum pet da espécie ["; 
        SetConsoleTextAttribute(hConsole, 15); cout << type;
        SetConsoleTextAttribute(hConsole, 12); cout << "] e raça [";
        SetConsoleTextAttribute(hConsole, 15); cout << breed;
        SetConsoleTextAttribute(hConsole, 12); cout << "]";
    }
    else{
        SetConsoleTextAttribute(hConsole, 15); cout << "Encontrado ["; 
        SetConsoleTextAttribute(hConsole, 10); cout << count; 
        SetConsoleTextAttribute(hConsole, 15); cout << "] "; cout << type << " ";
        SetConsoleTextAttribute(hConsole, 15); cout<< breed << " ";
    }
    if(selectGender(gender - 1) == Female) {
        SetConsoleTextAttribute(hConsole, 15); cout << "[";
		SetConsoleTextAttribute(hConsole, 13); cout << "Fêmea";
        SetConsoleTextAttribute(hConsole, 15); cout << "]" << endl;
        }
    else {
        SetConsoleTextAttribute(hConsole, 12); cout << " [";
		SetConsoleTextAttribute(hConsole, 11); cout << "Macho";
        SetConsoleTextAttribute(hConsole, 12); cout << "]" << endl;
        }
}


void restoreBackup(pet **list, ifstream &infile) {
    pet *head;
    int code;
    char name[21];
    char type[11];
    char breed[31];
    int genderInt;
    int age;
    float weight;

    while(infile >> code >> name >> type >> breed >> genderInt >> age >> weight) {
        try {
            head = new pet;
            head->code = code;
            strcpy(head->name, name);
            strcpy(head->type, type);
            strcpy(head->breed, breed);
            head->gender = selectGender(genderInt);
            head->age = age;
            head->weight = weight;
            head->next = NULL;
            if((*list) == NULL) (*list) = head;
            else {
                pet *temp = (*list);
                while(temp->next) temp = temp->next;
                temp->next = head;
            }
        } catch (const char * err) {
            cout<<"\nErro: " << err << "\n";
            throw;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");  //MOSTRAR ACENTOS NO GERAL
    //SetConsoleOutputCP(65001);  //MOSTRAR ACENTOS NO VSCODE
    
    ofstream outfile;
    ifstream infile;
    
    SetConsoleTitle("Pets"); // MUDA O TITULO DA JANELA DO CMD//
    int option;
    char type[11];
    char name[21];
    pet *list = NULL;

    infile.open ("pet_data.txt");
    if(!infile.is_open()){
        SetConsoleTextAttribute(hConsole, 12); cout << "\t\tSave file não encontrado ou inexistente" << endl;
        SetConsoleTextAttribute(hConsole, 9); cout << "\t   Um novo save file será criado para salvar os dados" << endl;
    }
    else {
        restoreBackup(&list, infile);
        SetConsoleTextAttribute(hConsole, 9); cout << "\t\t     Save recuperado com sucesso" << endl;
    }
    infile.close();

            
    while(true){
    do{
            SetConsoleTextAttribute(hConsole, 14); cout << "=-=-=-=-=-=-=-=--=-=-=-=-=-=";
            SetConsoleTextAttribute(hConsole, 10); cout << " Projeto PETS";
            SetConsoleTextAttribute(hConsole, 14); cout << " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
            SetConsoleTextAttribute(hConsole, 15); cout << "\t\t      Bem-vindo à lista de ";
            SetConsoleTextAttribute(hConsole, 11); cout << "Pets";
            SetConsoleTextAttribute(hConsole, 15); cout << "!\n";
            SetConsoleTextAttribute(hConsole, 15); cout << "\t\t   Escolha uma opção para continuar\n\n";
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t1 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Inserir na lista de pets" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t2 -"; 
            SetConsoleTextAttribute(hConsole, 15); cout << " Remover na lista de pets" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t3 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Alterar informação de um pet" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t4 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Buscar um pet por nome" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t5 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Filtrar a lista de pets por espécie" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t6 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Filtrar a lista de pets por espécie e raça" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t7 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Filtrar a lista de pets por espécie, raça e sexo" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t8 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Quantidade de pets na lista" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t9 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Quantidade de pets de uma espécie" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t10 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Imprimir a lista de pets" << endl;
            SetConsoleTextAttribute(hConsole, 2); cout << "\t\t0 -";
            SetConsoleTextAttribute(hConsole, 15); cout << " Sair e salvar" << endl;
            SetConsoleTextAttribute(hConsole, 14); cout << "=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=";
			SetConsoleTextAttribute(hConsole, 15); cout << "\nDigite a opção desejada: ";
            SetConsoleTextAttribute(hConsole, 2); cin >> option;
            cin.ignore(10000, '\n');
            if (option < 0 || option > 10){
				SetConsoleTextAttribute(hConsole, 12); cout << "Utilize valores entre 0 e 10\n";}
			if (cin.fail())
            {
                SetConsoleTextAttribute(hConsole, 12); cout << "Utilize somente números!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                option = 'E';
            }
        switch (option) {
            case 1: 
				createPet(&list);
                break;
            case 2: 
				removePet(&list);
                break;
            case 3: 
				changePet(&list);
                break;
            case 4: 
                SetConsoleTextAttribute(hConsole, 15); cout << "Digite o ";
                SetConsoleTextAttribute(hConsole, 13); cout << "nome " ; 
                SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscado: ";
                cin >> name;
                cin.ignore();
				printPetRec(searchByName(list, name));
                break;
            case 5: 
				searchByType(list);
                break;
            case 6: 
				searchByTypeAndBreed(list);
                break;
            case 7: 
				searchByTypeBreedAndGender(list);
                break;
            case 8: 
				SetConsoleTextAttribute(hConsole, 15); cout << "\nHá ["; 
                SetConsoleTextAttribute(hConsole, 10); cout << getCount(list); 
                SetConsoleTextAttribute(hConsole, 15); cout << "] pet(s) cadastrados" << endl;
                break;
            case 9: 
                SetConsoleTextAttribute(hConsole, 15); cout << "Digite a ";
                SetConsoleTextAttribute(hConsole, 13); cout << "espécie ";
                SetConsoleTextAttribute(hConsole, 15); cout << "do pet a ser buscada: ";
                cin >> type;
                cin.ignore();
				SetConsoleTextAttribute(hConsole, 15); cout << "\nHá ["; 
                SetConsoleTextAttribute(hConsole, 10); cout << getCountType(list, type);
                SetConsoleTextAttribute(hConsole, 15); cout << "] pet(s) cadastrados da espécie digitada" << endl;
                break;
            case 10:
            	if(list == NULL)
				{
                    SetConsoleTextAttribute(hConsole, 15); cout << "\nA lista está ";
                    SetConsoleTextAttribute(hConsole, 12); cout << "vazia.\n";
				}
				else
                    cout << endl;
					printPetRec(list);
                break;
        }
    }while (option != 0 && option != 1 && option != 2 && option != 3 && option != 4 && option != 5 && option != 6 && option != 7 && option != 8 && option != 9 && option != 10);
    outfile.open("pet_data.txt");

    if(list == NULL) outfile << "";
    else {
        pet *save = list;
        while(save != NULL) {
            outfile << save->code << " " << save->name << " " << save->type << " " << save->breed << " " << save->gender << " " << save->age << " "  << save->weight << endl;
            save = save->next;
        }
    }

    outfile.close();
    if (option == 0)
        return 0;
    }
}
