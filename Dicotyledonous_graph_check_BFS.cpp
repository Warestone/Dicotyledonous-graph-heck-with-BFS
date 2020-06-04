#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <list>
using namespace std;


bool isBipartiteUtil(int** Matrix, int src, int Color[], int Size_M)
{
    Color[src] = 1;
    queue <int> q;
    q.push(src);   
    while (!q.empty())
    {       
        int u = q.front();
        q.pop();        
        if (Matrix[u][u] == 1)
            return false;       
        for (int v = 0; v < Size_M; ++v)
        {            
            if (Matrix[u][v] && Color[v] == -1)
            {               
                Color[v] = 1 - Color[u];
                q.push(v);
            }            
            else if (Matrix[u][v] && Color[v] == Color[u])
                return false;
        }
    }    
    return true;
}

bool isBipartite(int** Matrix, int Size_M)
{    
    int* Color = new int [Size_M];
    for (int i = 0; i < Size_M; ++i)
        Color[i] = -1;
    for (int i = 0; i < Size_M; i++)
        if (Color[i] == -1)
            if (isBipartiteUtil(Matrix, i, Color, Size_M) == false)
                return false;
    return true;
}



int main()
{   
    int Size_M;
    bool From_File = false;
    list<string> Matrice_list;
    cout << "\n\t\tDicotyledonous graph check with BFS (breadth-first search). Timofeev E.V. 381708-2 ITMM 2020.\n\nPlease, select a type of input:\n\t1 - from file 'Adjacency_matrix.txt'\n\t2 - Console input\n";
    char Menu = getchar();
    switch (Menu)
    {
        case '1':    
            if (true)
            {
                ifstream file("Adjacency_matrix.txt");
                if (!file.is_open())
                {
                    cout << "\n\nFILE NOT FOUND!\n\n";
                    system("pause");
                    return 0;
                }
                else
                {
                    string String;
                    cout << "\n\nAdjacency matrix from file:\n\n";
                    while (getline(file, String)) 
                    { 

                        Matrice_list.push_back(String);
                        cout << "\t" << String << endl;
                    }                                          
                    file.close();                   
                    if (Size_M = Matrice_list.size()==0)
                    {
                        cout << "\n\nTHE FILE IS EMPTY!\n\n";
                        system("pause");
                        return 0;
                    }
                    if (Size_M = Matrice_list.size() == 1)
                    {
                        cout << "\n\nTHE FILE HAS ONLY ONE ROW! UNABLE TO COMPOSE MATRIX!\n\n";
                        system("pause");
                        return 0;
                    }                   
                    Size_M = Matrice_list.size();
                    From_File = true;
                }
            }           
            break;
        case '2':
            cout << "\n\nPlease, enter the size of square matrix: ";
            cin >> Size_M;
            if (Size_M < 2)
            {
                cout << "\n\n INCORRECT INPUT! THE SIZE OF MATRIX MUST BE GREATHER THAN 1!\n\n";
                system("pause");
                system("cls");
                return 0;
            }
            else
            {
                From_File = false;
            }
            break;
        default:
            cout << "\n\n INCORRECT INPUT!\n\n";
            system("pause");
            return 0;
    }
    
    int** Matrix = new int* [Size_M];       // Initialize matrix
    for (int i = 0; i < Size_M; ++i)
    {
        Matrix[i] = new int[Size_M];
    }
    
    if (From_File)                          // If input type - file
    {
        int Row = 0, Column = 0;
        for (string String : Matrice_list)
        {
            if (String.size() != Size_M)
            {
                cout << "\n\n INCORRECT MATRIX INPUT! THE MATRIX MUST BE SQUARE!\n\n";
                system("pause");
                return 0;
            }
            for (char Number : String)
            {
                if (Number != 48 && Number != 49)
                {
                    cout << "\n\n INCORRECT MATRIX INPUT! MATRIX MUST CONSIST OF ZEROS AND ONES\n\n";
                    system("pause");
                    return 0;
                }
                if (Number == 48)
                    Matrix[Row][Column] = 0;
                else
                    Matrix[Row][Column] = 1;
                Column++;
            }
            Column = 0;
            Row++;
        }
    }
    else                                    // If input type - console
    {
        string Row;
        cout << "\n\nPlease, enter " << Size_M*Size_M << " elements of square " << Size_M << "x" << Size_M << " adjacency matrix\n(Must be 0 or 1 without any symbols, only one row of matrix at time and press Enter-key)\n\n\t";
        for (int i = 0; i < Size_M; i++)
        {
            cin >> Row;
            if (Row.size()!=Size_M)
            {
                cout << "\n\n INCORRECT MATRIX! ROW SIZE MUST BE EQUAL " << Size_M << "!\n\n";
                system("pause");
                return 0;
            }
            int Column = 0;
            for (char Value : Row)
            {
                switch (Value)
                {
                    case '1':
                        Matrix[i][Column] = 1;
                        break;
                    case '0':
                        Matrix[i][Column] = 0;
                        break;
                    default:
                        cout << "\n\n INCORRECT MATRIX INPUT! MATRIX MUST CONSIST OF ZEROS AND ONES\n\n";
                        system("pause");
                        return 0;
                        break;
                }
                Column++;
            }
            cout << "\t";
        }

    }
    
    isBipartite(Matrix, Size_M) ? cout << "\n\n**************************\nGraph IS dicotyledonous! *\n**************************\n\n" : cout << "\n\n******************************\nGraph IS NOT dicotyledonous! *\n******************************\n\n";
    system("pause");
    return 0;
}
