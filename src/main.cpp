/* TUGAS KECIL 1 IF2211 - STRATEGI ALGORITMA */
/* Penyelesaian Persoalan Convex Hull dengan Algoritma Brute Force */
/* NIM  : 13518045 */
/* Nama : Anna Elvira Hartoyo*/
/* Kelas: K-03 */

/*Cara compile : g++ array.h point.h main.cpp -o main -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 */


#include <stdio.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <graphics.h>
#include "boolean.h"
#include "array.h"

/*======================= DEFINISI DAN SPESIFIKASI FUNGSI ==================== */
void MakeEmpty (TabInt * T);
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */

boolean IsMember (TabInt T, ElType X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */

ElType ValMin (TabInt T);
/* Mengirimkan nilai minimum tabel */

ElType ValMax (TabInt T);
/* Mengirimkan nilai maksimum tabel */

void SortDesc (TabInt * T);
/* I.S. T terdefinisi */
/* F.S. T elemennya terurut menurun */

int whichSideOfLine (Point p1, Point p2, Point p3);
/* Menentukan apakah point p3 berada di sebelah kanan, kiri, atau tepat pada
garis yang dibentuk oleh point p1 dan p2. fungsi akan menghasilkan nilai positif
yang artinya point p3 berada di sebelah kanan garis, nol yang artinya point p3
berada tepat di garis, dan negatif yang artinya point p3 berada di sebelah kiri
garis*/

/*====================== REALISASI FUNGSI ================================== */
int whichSideOfLine (Point p1, Point p2, Point p3){
    return (Absis(p3) - Absis(p1)) * (Ordinat(p2) - Ordinat(p1)) - (Ordinat(p3) - Ordinat(p1)) * (Absis(p2) - Absis(p1));
}

void MakeEmpty (TabInt * T)
{ 
    /* KAMUS */
    int i;

    /* ALGORITMA */
    for (i=IdxMin; i<=IdxMax; i++){
        Absis(Elmt(*T,i)) = 0;
        Ordinat(Elmt(*T,i)) = 0;
    }

    Neff(*T) = 0;

}

boolean IsMember (TabInt T, ElType X){
    boolean found;
    IdxType i;

    found = false;
    if ((Neff(T)==0)) {
		return false;
	} 
    
    else {
        
        i = 1;
		while ((i<=Neff(T))&&(!found)) {
        if (Absis(Elmt(T,i)) == Absis(X) && Ordinat(Elmt(T,i)) == Ordinat(X)){
            found = true;
        }
        else{
            i++;
        }
	    }
    }

  return(found);

}

ElType ValMax (TabInt T)
{
    int i;
    ElType max;

    for (i=IdxMin; i<=Neff(T); i++){
        if (i==IdxMin||Absis(Elmt(T,i))>Absis(max)){
            max= (Elmt(T,i));
        }
        }
    
    return (max);
}

ElType ValMin (TabInt T)
{
    int i;
    ElType min;

    for (i=IdxMin; i<=Neff(T); i++){
        if (i==IdxMin||Absis(Elmt(T,i))<Absis(min)){
            min = (Elmt(T,i));
        }
    }
    
    return(min);
}

void SortDesc (TabInt * T)
{
    int i,j;
    ElType temp;

    if (Neff(*T) != 0){
        
        for(i=IdxMin;i<=Neff(*T);i++)
        {
            temp=Elmt(*T,i);
            j=i-1;

            while(Absis(Elmt(*T,j))<Absis(temp) && j>0)
            {
                Elmt(*T,j+1) = Elmt(*T,j);
                j--;
            }
            Elmt(*T,j+1) = temp;
        }
    
    }
}

/*=============================== KAMUS GLOBAL ================================= */
int N, i, j, k, d, maxOrdinat;
Point p, q, maxAbsis, minAbsis;
TabInt TabTitikAwal, TabConvexHull, TempAbove, TempBelow;
boolean allOnRight, quit;
char choice;
clock_t start, end;
double cputime;

/*========================= ALGORTIMA PROGRAM UTAMA ============================= */
int main(){
    printf("====================================================================\n");
    printf(".d88b .d88b. 8b  8 Yb    dP 8888 Yb  dP    8   8 8    8 8    8\n");    
    printf("8P    8P  Y8 8Ybm8  Yb  dP  8www  YbdP     8www8 8    8 8    8\n");   
    printf("8b    8b  d8 8  '8   YbdP   8     dPYb     8   8 8b..d8 8    8\n");   
    printf("`Y88P `Y88P' 8   8    YP    8888 dP  Yb    8   8 `Y88P' 8888 8888\n");
    printf("====================================================================\n");
    printf("\n");
    
    quit = false;
    while (!quit){
        printf("Masukkan jumlah titik yang diinginkan : ");
        scanf("%d", &N);
        printf("\n");
        if(N > 100 || N<0){
            printf("Masukan tidak valid. Nilai harus antara 1 hingga 100.\n");
            printf("Masukkan jumlah titik yang diinginkan :");
            scanf("%d", &N);
            printf("\n");
        }
    
        /*Inisialisasi tabel TabTitikAwal kosong*/
        MakeEmpty(&TabTitikAwal);
        Neff(TabTitikAwal) = N;

        /* Melakukan random pada N titik lalu menyimpannya dalam array TabTitikAwal */
        srand(time(0));
        for(i = 1; i <= N; i++) {
            int x = rand() % 500;
            int y = rand() % 400;

            Absis(Elmt(TabTitikAwal,i)) = x;
            Ordinat(Elmt(TabTitikAwal,i)) = y;
        }

        /*Tampilkan N titik yang telah dibangkitkan secara acak*/
        printf("Berikut titik yang dibangkitkan\n");
        for (i=1; i<=Neff(TabTitikAwal); i++){
            printf("(%d, %d)\n", Absis(Elmt(TabTitikAwal,i)), Ordinat(Elmt(TabTitikAwal,i)));
        }
        printf("\n");

        /*Inisialisasi grafik untuk menampilkan seluruh titik*/
        int gd = DETECT, gm, color; 
        initgraph(&gd, &gm, ""); 
  
        for (i = 1; i<=N; i++){
            setfillstyle(SOLID_FILL,10);
            circle(Absis(Elmt(TabTitikAwal,i)), Ordinat(Elmt(TabTitikAwal,i)), 5);
            floodfill(Absis(Elmt(TabTitikAwal,i)), Ordinat(Elmt(TabTitikAwal,i)), 15);
        }

        /*Inisialisasi tabel TabConvexHull kosong*/
        MakeEmpty(&TabConvexHull);

        /*Algoritma brute force untuk mencari convex hull*/
        start = clock();    /*mulai menghitung waktu*/
        if(N > 1){
            for(i=1; i<=N; i++) {
                for(j=1; j<=N; j++) {
                    if(i != j) {                
                        p = Elmt(TabTitikAwal,i);
                        q = Elmt(TabTitikAwal,j);

                        // Do all other Points lie within the half-plane to the right
                        allOnRight = true;
                        for(k=1; k<=N; k++) {
                            if(k != i && k != j) {
                            
                                d = whichSideOfLine(p, q, Elmt(TabTitikAwal,k));
                                if(d < 0) {
                                    allOnRight = false;
                                    break;
                                }
                            }                          
                        }
            
                        if(allOnRight) {
                            line(Absis(p), Ordinat(p), Absis(q), Ordinat(q));
                            if(!IsMember(TabConvexHull,p)){
                                Neff(TabConvexHull)++;
                                Elmt(TabConvexHull,Neff(TabConvexHull)) = p;
                            }
                            if(!IsMember(TabConvexHull,q)){
                                Neff(TabConvexHull)++;
                                Elmt(TabConvexHull,Neff(TabConvexHull)) = q;
                            }
                        }
                    }
            
                }
            }
        }

        else{
            Neff(TabConvexHull)++;
            Elmt(TabConvexHull,1) = Elmt(TabTitikAwal,1);
        }
        end = clock();  /* Selesai menghitung waktu*/

        /* Mengurutkan himpunan titik pada TabConvexHull */
        maxAbsis = ValMax(TabConvexHull);
        minAbsis = ValMin(TabConvexHull);
        if(Ordinat(maxAbsis)>Ordinat(minAbsis)){
            maxOrdinat = Ordinat(maxAbsis);
        }
        else{
            maxOrdinat = Ordinat(minAbsis);
        }

        MakeEmpty(&TempAbove);
        MakeEmpty(&TempBelow);

        j = 1;
        k = 1;
        for(i=1; i<=Neff(TabConvexHull); i++){
            if(Ordinat(Elmt(TabConvexHull,i)) >= maxOrdinat){
                Neff(TempAbove)++;
                Absis(Elmt(TempAbove, j)) = Absis(Elmt(TabConvexHull,i));
                Ordinat(Elmt(TempAbove, j)) = Ordinat(Elmt(TabConvexHull,i));
                j++;
            }
            else{
                Neff(TempBelow)++;
                Absis(Elmt(TempBelow, k)) = Absis(Elmt(TabConvexHull,i));
                Ordinat(Elmt(TempBelow, k)) = Ordinat(Elmt(TabConvexHull,i));
                k++;
            }
        }

        SortDesc(&TempAbove);
        SortDesc(&TempBelow);

        j = 1;
        for(i=Neff(TempAbove);i>=1; i--){
            Elmt(TabConvexHull, j) = Elmt(TempAbove, i);
            j++;
        }
        for(i=1; i<=Neff(TempBelow); i++){
            Elmt(TabConvexHull, j) = Elmt(TempBelow,i);
            j++;
        }

        /* Menampilkan waktu eksekusi dan himpunan titik yang membentuk convex hull*/
        cputime = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Waktu eksekusi adalah %f detik\n", cputime);
        printf("Himpunan titik yang membentuk convex hull\n");
        printf("[");
        for (i = 1; i<=Neff(TabConvexHull); i++){
            printf("(%d, %d)", Absis(Elmt(TabConvexHull,i)), Ordinat(Elmt(TabConvexHull,i)));
        }
        if(N>1){
            printf("(%d,%d)]\n", Elmt(TabConvexHull,1), Ordinat(Elmt(TabConvexHull,1)));
        }
        else{
            printf("]\n");
        }

        getch();
        closegraph();

        printf("Apakah masih ada convex hull yang ingin dicari? (Y/N)\n");
        scanf("%s", &choice);
        printf("\n");
        if (choice == 'N'){
            quit = true;
        }

    }

}