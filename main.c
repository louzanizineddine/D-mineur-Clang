#include <stdio.h>

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

int main() {
    int t[8] = {1 , 3 , 0 , 2 , 5 , -1 , -1 , -1};
    show_tab(t , 8);
    ajouter(t , 8 , 17);
    show_tab(t , 8);
    int frist_elem = retire(t , 8);
    show_tab(t , 8);
    printf("fist_elemt = %d \n" , frist_elem);
    return 0;
}