#include <stdio.h>
#include <stdlib.h>

struct Case
{
    // X:non devoile et non marque,
    // F non devoile et marque 
    // V : devoile et vide , 
    // I: devoilee et indiquant le nombre de mine 
    char etat;
    int nmbr_mines_adjacentes; // pour indiquer le nombre de mines sur les cases adjacentes
    int contient_mine; // pour indiquer si la case elle meme une mine
};

struct Grille {
    struct Case grille[20][20];
    int nmbre_mines_decouvertes; // indiqur le nombre totales des mines decouvertes par joueur;
    int nmbre_totales_mines; // indique le nombre totales des mines
};

// declaration des fonctions;
void ajouter (int tab[] , int size, int num); 
int retire(int tab[] , int size); 
void show_tab(int tab[] , int size);
int rand_number(int min , int max);
void update_cases_adja(struct Grille *grille , int ligne , int colonne);
struct Grille cree(int nmbr_totales_mines);
void afficher(struct Grille grille);


int main() {
    int t[8] = {1 , 3 , 0 , 2 , 5 , -1 , -1 , -1};
    // show_tab(t , 8);
    // ajouter(t , 8 , 17);
    // show_tab(t , 8);
    // int frist_elem = retire(t , 8);
    // show_tab(t , 8);
    // printf("fist_elemt = %d \n" , frist_elem);
    struct Grille demineur = cree(10);
    afficher(demineur);
    printf("\n");
    printf("%c" , demineur.grille[0][1].etat);
    // printf("mines totales =  %d et decouvertes %d \n" , demineur.nmbre_totales_mines , demineur.nmbre_mines_decouvertes);
    return 0;
}


void ajouter(int tab[] , int size, int num) {
    // the first element with -1 we change it's value to num
    int i = 0;
    int end = 0;
    while (!end)
    {
        if(tab[i] == -1) {
            tab[i] = num;
            end = 1;
        }
        i++;
    }
}

int retire(int tab[] , int size) {
    int first_elem = tab[0];
    for (int i = 0; i < size; i++)
    {
        if (tab[i] != -1) {
            tab[i] = tab[i + 1];
        }

    }
    return first_elem;

}

void show_tab(int tab[] , int size) {


    for (int i = 0; i < size; i++)
    {
        printf("tab[%d]=%d |" , i , tab[i]);
    }
    printf("\n");
    
}

int rand_number(int min , int max) {
    return rand() % (max + 1);
}

struct Grille cree(int nmbre_totales_mines){
    struct Grille grille;
    grille.nmbre_mines_decouvertes = 0;
    grille.nmbre_totales_mines = nmbre_totales_mines;

    // on va cree les cases 

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            struct Case cs;
            cs.etat = 'X';
            cs.nmbr_mines_adjacentes = 0;
            cs.contient_mine = 0;
            grille.grille[i][j] = cs;
        }        
    }
    

   // on va cree les mines
    
    int nombre_currents_mines = 0;

    while (nombre_currents_mines != nmbre_totales_mines)
    {
        int ligne = rand_number(0 , 20);
        int colonne = rand_number(0 , 20);
        if (!grille.grille[ligne][colonne].contient_mine) {
            grille.grille[ligne][colonne].contient_mine = 1;
            // mise a jour des les cases adjacent 
            update_cases_adja(&grille , ligne , colonne);
            nombre_currents_mines += 1;;
        }
    }
    
    
    return grille;
}

void afficher(struct Grille grille) {
    for (int i = -1; i <= 20; i++)
    {
        for (int j = -1 ; j <= 20; j++)
        {
            // si la premiere ligne ou la derniere ligne 
            if ((i == -1 )|| (i == 20)) {
                printf(" # ");
                continue;
            }
            // si la premiere colonne ou la derniere colonne
            if ((j == -1) || (j == 20))
            {
                printf(" # ");
                continue;
            }

            else {

                if (grille.grille[i][j].contient_mine)
                {
                    printf(" M ");
                    continue;
                }
                

                if (grille.grille[i][j].etat == 'X')
                {
                    printf(" %d " , grille.grille[i][j].nmbr_mines_adjacentes);
                    // printf(" X ");
                }
                else if (grille.grille[i][j].etat == 'F') {
                    printf(" F ");
                }
                else if (grille.grille[i][j].etat == 'V') {
                    printf("   ");
                }
                else {
                    // on indique le nombre de mines adjacentes
                }
                
            }
            
       
        }
        printf("\n");
    }
    
}

void update_cases_adja(struct Grille *grille , int ligne , int colonne) {
    
    if (ligne == 0 ) {
        if (colonne == 0) {
            grille->grille[ligne + 1][colonne].nmbr_mines_adjacentes++;  
            grille->grille[ligne][colonne + 1].nmbr_mines_adjacentes++;  
            grille->grille[ligne + 1][colonne + 1].nmbr_mines_adjacentes++;  
            return;
        } else if (colonne == 19) {
            grille->grille[ligne + 1][colonne].nmbr_mines_adjacentes++;  
            grille->grille[ligne][colonne - 1].nmbr_mines_adjacentes++;  
            grille->grille[ligne - 1][colonne - 1].nmbr_mines_adjacentes++; 
            return;
        }

    }

    else if (ligne == 19) {
        if (colonne == 0) {
            grille->grille[ligne - 1][colonne].nmbr_mines_adjacentes ++;  
            grille->grille[ligne][colonne + 1].nmbr_mines_adjacentes ++;  
            grille->grille[ligne - 1][colonne + 1].nmbr_mines_adjacentes ++;
            return ;

        } else if (colonne == 19) {
            grille->grille[ligne - 1][colonne].nmbr_mines_adjacentes ++;  
            grille->grille[ligne][colonne - 1].nmbr_mines_adjacentes ++;  
            grille->grille[ligne - 1][colonne - 1].nmbr_mines_adjacentes ++;  
            return;

        }
    }
    else {
            if (colonne == 19)
            {
                grille->grille[ligne - 1][colonne].nmbr_mines_adjacentes++;
                grille->grille[ligne + 1][colonne].nmbr_mines_adjacentes++;

                grille->grille[ligne - 1][colonne-1].nmbr_mines_adjacentes++;
                grille->grille[ligne][colonne-1].nmbr_mines_adjacentes++;
                grille->grille[ligne + 1][colonne-1].nmbr_mines_adjacentes++;
                return;

            } 
            if (colonne == 0) {
                grille->grille[ligne - 1][colonne].nmbr_mines_adjacentes++;
                grille->grille[ligne + 1][colonne].nmbr_mines_adjacentes++;

                grille->grille[ligne - 1][colonne+1].nmbr_mines_adjacentes++;
                grille->grille[ligne][colonne+1].nmbr_mines_adjacentes++;
                grille->grille[ligne + 1][colonne+1].nmbr_mines_adjacentes++;
                return;
            }
            
            grille->grille[ligne - 1][colonne - 1].nmbr_mines_adjacentes ++;  
            grille->grille[ligne ][colonne -1].nmbr_mines_adjacentes ++;  
            grille->grille[ligne + 1][colonne -1].nmbr_mines_adjacentes ++;
            grille->grille[ligne - 1][colonne].nmbr_mines_adjacentes ++;

            grille->grille[ligne + 1][colonne].nmbr_mines_adjacentes ++;
            grille->grille[ligne - 1][colonne + 1].nmbr_mines_adjacentes ++;  
            grille->grille[ligne][colonne + 1].nmbr_mines_adjacentes ++;
            grille->grille[ligne + 1][colonne + 1].nmbr_mines_adjacentes ++;  
        }
}