#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 24

struct Ucak //ucak yapisi olusturuldu
{
    int oncelik_id;
    int ucak_id;
    int talep_edilen_inis_saati;
    struct Ucak* Sonraki;
};


struct Ucak* front = NULL; //kuyruk bas ve son icin olusturuldu
struct Ucak* rear = NULL;


void inis_pisti_kullanim_sirasi() //ucaklarin inis saatleri hesaplanir
{
    FILE *dosya=fopen("input.txt", "r"); //dosya uzerinde islem yapilmadigi icin only read modu kullanildi
    struct Ucak u1, *dugum;
    while(fscanf(dosya, "%d %d %d\n", &u1.oncelik_id, &u1.ucak_id, &u1.talep_edilen_inis_saati)!=EOF) //dosyanin sonuna kadar okur
    {
        dugum=(struct Ucak*)malloc(sizeof(struct Ucak));
        //dosyadan cekilen veriler dugum struct yapisina aktarildi (dugum==ucak)
        dugum->oncelik_id=u1.oncelik_id;
        dugum->ucak_id=u1.ucak_id;
        dugum->talep_edilen_inis_saati=u1.talep_edilen_inis_saati;
        dugum->Sonraki=NULL;

        struct Ucak* temp=front;

        if(front==NULL) //kuyrukta hicbir eleman yoksa ilk gelen eleman oncelikli olur, bu yüzden karsilastirma yapilmamistir
        {
            front=dugum;
            rear=dugum;
        }

        else
        {
            if(dugum->talep_edilen_inis_saati < front->talep_edilen_inis_saati) //eklenecek ucagin önceligi ilk siradaki ucaktan daha fazlaysa eklenecek ucak front hale getirilir
            {

                if(dugum->oncelik_id == front->oncelik_id)
                {
                    if(dugum->ucak_id < front->ucak_id)
                    {
                        temp=temp->Sonraki;

                    }
                    else if(dugum->ucak_id > front->ucak_id)
                    {
                        struct Ucak* Ikinci = front;
                        front=dugum;
                        front->Sonraki=Ikinci;
                    }

                    else
                    {
                        struct Ucak* Ikinci = front;
                        front=dugum;
                        front->Sonraki=Ikinci;
                    }
                }

                else if(dugum->oncelik_id < front->oncelik_id)
                {
                    temp=temp->Sonraki;

                }

                else
                {
                    struct Ucak* Ikinci = front;
                    front=dugum;
                    front->Sonraki=Ikinci;
                }
            }


            else //arama yapilacak
            {
                struct Ucak* temp=front;

                //dongunun kapsami kuyruktaki her elemanin önceligine teker teker bakilmasidir
                while(temp->Sonraki != NULL && dugum->talep_edilen_inis_saati > temp->Sonraki->talep_edilen_inis_saati) //yeni eklenen eleman kendisinden dusuk oncelikli eleman gordugunde onune gececek
                {
                    temp=temp->Sonraki;
                }

                if(temp->Sonraki==NULL)
                {
                    rear->Sonraki=dugum;
                    rear=dugum;
                }
                else //araya eleman ekleme islemi
                {
                    struct Ucak* Sonraki=temp->Sonraki;
                    temp->Sonraki=dugum;
                    dugum->Sonraki=Sonraki;
                }
            }

        }
    }



    fclose(dosya);
}


void ucakYazdirma() //elde edilen verileri ekrana yazdirma fonksiyonu
{
    if(front==NULL)
    {
        printf("\n Kuyruk bostur.");
        return;
    }

    struct Ucak* temp=front;
    int sayac=1;

    while(temp!=NULL)
    {
        if(sayac<=SIZE)
        {
            printf("***** Ucus Sira Numarasi %d ***** \n", sayac);
            printf("Oncelik ID: %d\n", temp->oncelik_id);
            printf("Ucak ID: %d\n", temp->ucak_id);
            printf("Talep Edilen Inis Saati: %d\n", temp->talep_edilen_inis_saati);
            printf("\n");
        }

        else
        {
            printf("%d id'li ucak pist dolulugundan inis yapamamistir.\n", temp->ucak_id);
            printf("\n");
        }

        temp=temp->Sonraki;
        sayac++;
    }

    printf("-----------------------------------\n");


}

void outputYazdirma() //elde edilen verileri dosyaya yazdirma fonksiyonu
{
    system("cls");
    FILE *dosya2;
    dosya2=fopen("output.txt", "w");

    struct Ucak* temp=front;
    int sayac=1;

    while(temp!=NULL)
    {
        fprintf(dosya2, "%d %d %d \n", temp->oncelik_id, temp->ucak_id, temp->talep_edilen_inis_saati);

        temp=temp->Sonraki;
        sayac++;
    }

    fclose(dosya2);

}

int main()
{
    while(1)
    {
        int secim;
        printf("Havalimani sistemine hosgeldiniz...\n");
        printf("-----------------------------------\n");
        //secim menusu bilgilerine gecis:

        printf("Var olan ucak bilgilerinin siraya dizilmis bir halde okunmasi icin= 1\n");
        printf("Ucaklarin siraya dizilmis halinin output dosyasina yazilmasi= 2\n");
        printf("Programdan cikis yapmak icin= 3\n");
        printf("-----------------------------------\n");
        scanf("%d", &secim);

        switch(secim)
        {
        case 1:
            printf("Ucak bilgileri listelenmis bir  sekilde gosteriliyor...\n");
            printf("-----------------------------------\n");
            inis_pisti_kullanim_sirasi();
            ucakYazdirma();
            break;

        case 2:
            outputYazdirma();
            printf("Bilgiler output.txt dosyasina yazilmistir... \n");
            printf("-----------------------------------\n");
            break;

        case 3:
            system("cls");
            printf("Programdan cikis yapiliyor...\n");
            printf("-----------------------------------\n");
            return 0;

        }

    }
}
