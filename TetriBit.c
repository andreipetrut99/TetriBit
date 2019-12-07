#include <stdio.h>
#include <stdlib.h>

void printMap(unsigned long long harta)
{
    unsigned long long test;
    int i;
    test = 1;
    test = test << 63;
    for (i = 0; i < 64; i++)
    {
        if ((harta & (test >> i)) == 0)
            printf(".");
        else
            printf("#");
        if ((i + 1) % 8 == 0)
            printf("\n");
    }
}
void printBits(size_t const size, void const *const ptr)
{
    unsigned char *b = (unsigned char *)ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--)
    {
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int main()
{
    unsigned long long harta, mask, test = 1, piesa[100][9], aux;
    int i, j, m, p, q, coliziune;

    scanf("%llu", &harta);
    printMap(harta);
    printf("\n");
    //Citire piesa si mutari
    scanf("%d", &m);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < 9; j++)
            scanf("%llu", &piesa[i][j]);
    }
    /* for (j = 0; j < m; j++)
    {
        if (piesa[j][0] > 255)
        {
            p = 16;
            test = 1;
            test = test << 15;
        }
        else
        {
            p = 8;
            test = 1;
            test = test << 7;
        }
        for (i = 0; i < p; i++)
        {
            if ((piesa[j][0] & (test >> i)) == 0)
                printf(".");
            else
            {
                printf("#");
            }
            if ((i + 1) % 8 == 0)
                printf("\n");
        }
        if (p == 16)
            piesa[j][0] = piesa[j][0] << 48;
        else
            piesa[j][0] = piesa[j][0] << 56;
    }*/
    
    
    for (i = 0; i < m; i++)
    {
        coliziune = 0;
        p = 1;
        mask = piesa[i][0];
        if (mask < 255)
            mask = mask << 56;
        else
        {
            mask = mask << 48;
            q = 0;
        }
        //Printare piese de 8 biti pe mapa
        if (mask < 255)
        {
            while (coliziune == 0)
            {
                test = (harta & mask);
                if (test == 0)
                {
                    test = (harta | mask);
                    if (p < 7)
                    {
                        mask = (mask >> 8);
                        p++;
                        printMap(test);
                    }
                    else
                    {
                        coliziune = 1;
                        harta = (harta | mask);
                        printMap(test);
                    }
                }
                else
                {
                    coliziune = 1;
                    mask = mask << 8;
                    harta = (harta | mask);
                }

                printf("\n");
            }
        }
        else {      //Printare piese de 16 biti pe mapa
            test=1;
            test=test<<55;
            aux=0;
            for(j=0;j<8;j++)
            {
                if((mask & test)!=0)
                {
                    aux=(aux | (mask & test));
                }
                test=test>>1;
                
            }   
            aux=aux<<8;
            //DE ADAUGAT CONDITIE DE OPRIRE IN CAZUL IN CARE PIESA NU ARE LOC IN TOTALITATE PE HARTA
            if((harta & aux)==0)
            {
                test= (harta | aux);
                p++;
                printMap(test);
            }
            while (coliziune == 0)
            {
                test = (harta & mask);
                if (test == 0)
                {
                    test = (harta | mask);
                    if (p < 7)
                    {
                        mask = (mask >> 8);
                        p++;
                        printMap(test);
                    }
                    else
                    {
                        coliziune = 1;
                        harta = (harta | mask);
                        printMap(test);
                    }
                }
                else
                {
                    coliziune = 1;
                    mask = mask << 8;
                    harta = (harta | mask);
                }

                printf("\n");
            }
        }
    }
    printBits(sizeof(piesa[0][0]), &piesa[0][0]);
    piesa[0][0]=piesa[0][0]>>4;
    printBits(sizeof(piesa[0][0]), &piesa[0][0]);
    printMap(harta);
}
