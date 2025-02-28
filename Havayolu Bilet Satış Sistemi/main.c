#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bilgi{
    int numara;
    char kalkisYeri[21];
    char varisYeri[21];
    int kalkisSaati;
    int kalkisDakikasi;
    int koltukKapasitesi;
    int bosKoltukSayisi;
    float biletFiyati;
};

struct bilet{
    int ucus_no;
    char TCno[11];
    float bilet_fiyati;
};

void KucuktenBuyuge(int diziUzunluk,float sayiDizisi[])//YuzdeElliAlti fonksiyonunda calistirmak icin kullanilmistir.
{
    int i,j;
    float *sirala=sayiDizisi,gecici;
    for(i=0;i<diziUzunluk;i++)
    {
        for(j=i+1;j<diziUzunluk;j++)
        {
            if(*(sirala+i)>*(sirala+j))
            {
                gecici=*(sirala+i);
                *(sirala+i)=*(sirala+j);
                *(sirala+j)=gecici;
            }
        }
    }
}

void UcusveBiletListele(FILE *dosya,FILE *dosya2,int no,int secim2)
{
    int bilet_sayisi=0;
    struct bilgi liste;
    struct bilet musteri;
    float doluluk,toplam_kazanc=0,ort_bilet_fiyati=0;
    fseek(dosya,((no-1)*sizeof(liste)),SEEK_SET);
    fread(&liste,sizeof(liste),1,dosya);
    if(liste.numara==0)
    {
        printf("\n\n%d numarali bir ucus bulunmamaktadir.",no);
    }
    else
    {
        doluluk=(float)((liste.koltukKapasitesi)-(liste.bosKoltukSayisi))*100/(liste.koltukKapasitesi);
        printf("\n\nUcus No     \tKalkis Yeri     Varis Yeri     \tZamani     \tKapasite     \tBos Koltuk     \tDoluluk %%\n-------     \t-----------     ----------     \t------     \t--------     \t----------     \t---------\n%d\t\t%s\t\t%s\t\t%.2d.%.2d\t\t%d\t\t%d\t\t%.2f\n",liste.numara,liste.kalkisYeri,liste.varisYeri,liste.kalkisSaati,liste.kalkisDakikasi,liste.koltukKapasitesi,liste.bosKoltukSayisi,doluluk);

    }
    if(secim2==2)//Fonksiyon sayisini azaltmak icin sorgulama programindaki 1 ve 2. madde birlestirilmistir.
    {
        for(;;)
        {
            fscanf(dosya2,"%d%s%f",&musteri.ucus_no,&musteri.TCno,&musteri.bilet_fiyati);
            if(feof(dosya2))
            {
                break;
            }
            if(musteri.ucus_no==no)
            {
                toplam_kazanc+=musteri.bilet_fiyati;
                bilet_sayisi++;
                if(bilet_sayisi==1)
                {
                    printf("\nSatilan Biletler:\nTC Kimlik No\tFiyati:\n-------------\t----------\n");
                }
                printf("%s\t%.2f TL\n",musteri.TCno,musteri.bilet_fiyati);
            }
        }
        if(bilet_sayisi>0)
        {
            ort_bilet_fiyati=(float)toplam_kazanc/bilet_sayisi;
            printf("--------------------------\n\nToplam bilet sayisi:%d\nToplam kazanc:%.2lf TL\nOrtalama bilet fiyati:%.2f TL\n",bilet_sayisi,toplam_kazanc,ort_bilet_fiyati);
        }
        else
        {
            printf("Girdiginiz ucus numarasina iliskin satilan bilet yoktur.\n");
        }
    }
}

void KalkisYeriAra(FILE *dosya)
{
    int sonuc,kayit=0;
    char sehir[21];
    float doluluk;
    struct bilgi liste;
    printf("\n\nAramak istediginiz sehri giriniz:");
    scanf("%s",sehir);
    while(!feof(dosya))
    {
        sonuc=fread(&liste,sizeof(liste),1,dosya);
        if(sonuc!=0&&liste.numara!=0)
        {
            if((strcmp(liste.kalkisYeri,sehir))==0)
            {
                kayit++;
                if(kayit==1)
                {
                    printf("\n\nUcus No     \tKalkis Yeri     Varis Yeri     \tZamani     \tKapasite     \tBos Koltuk     \tDoluluk %%\n-------     \t-----------     ----------     \t------     \t--------     \t----------     \t---------\n");
                }
                doluluk=(float)((liste.koltukKapasitesi)-(liste.bosKoltukSayisi))*100/(liste.koltukKapasitesi);
                printf("%d\t\t%s\t\t%s\t\t%.2d.%.2d\t\t%d\t\t%d\t\t%.2f\n",liste.numara,liste.kalkisYeri,liste.varisYeri,liste.kalkisSaati,liste.kalkisDakikasi,liste.koltukKapasitesi,liste.bosKoltukSayisi,doluluk);
            }
        }
    }
    rewind(dosya);
    if(kayit==0)
    {
        printf("Aradiginiz sehirden kalkan ucus bulunamadi.\n");
    }
}

void YuzdeElliAlti(FILE *dosya)
{
    int bosKoltuk[50],*sirala=bosKoltuk,gecici,i,j,sonuc,sayi=0;
    struct bilgi ucus;
    float yuzde[50],*sirala2=yuzde,gecici2,doluluk;
    while(!feof(dosya))
    {
        sonuc=fread(&ucus,sizeof(ucus),1,dosya);
        if(sonuc!=0&&ucus.numara!=0)
        {
            doluluk=(float)((ucus.koltukKapasitesi)-(ucus.bosKoltukSayisi))*100/(ucus.koltukKapasitesi);
            if(doluluk<50)
            {
                bosKoltuk[sayi]=ucus.bosKoltukSayisi;
                yuzde[sayi]=doluluk;
                sayi++;
            }
        }
    }
    KucuktenBuyuge(sayi+1,yuzde);
    rewind(dosya);
    if(sayi>=1)
    {
        printf("\n\nUcus No     \tKalkis Yeri     Varis Yeri     \tZamani     \tKapasite     \tBos Koltuk     \tDoluluk %%\n-------     \t-----------     ----------     \t------     \t--------     \t----------     \t---------\n");
    }
    for(i=0;i<sayi+1;i++)
    {
        while(!feof(dosya))
        {
            sonuc=fread(&ucus,sizeof(ucus),1,dosya);
            if(sonuc!=0&&ucus.numara!=0)
            {
                doluluk=(float)((ucus.koltukKapasitesi)-(ucus.bosKoltukSayisi))*100/(ucus.koltukKapasitesi);
                if(doluluk==yuzde[i])
                {
                    for(j=0;j<sayi+1;j++)
                    {
                        if(bosKoltuk[j]==ucus.bosKoltukSayisi)
                        {
                            printf("%d\t\t%s\t\t%s\t\t%.2d.%.2d\t\t%d\t\t%d\t\t%.2f\n",ucus.numara,ucus.kalkisYeri,ucus.varisYeri,ucus.kalkisSaati,ucus.kalkisDakikasi,ucus.koltukKapasitesi,ucus.bosKoltukSayisi,doluluk);
                            bosKoltuk[j]=0;
                        }
                    }
                }
            }
        }
        rewind(dosya);
    }
}

void YolcuBilgileri(FILE *dosya,FILE *dosya2)
{
    struct bilgi liste;
    struct bilet musteri;
    int bilet_sayisi=0;
    int no,ucuslar;
    char tcNo[13];
    printf("\nTC numarasini giriniz:");
    scanf("%s",tcNo);
    for(;;)
    {
        fscanf(dosya2,"%d\t\t%s\t\t%f",&musteri.ucus_no,&musteri.TCno,&musteri.bilet_fiyati);
        if(feof(dosya2))
        {
            break;
        }
        if(strcmp(tcNo,musteri.TCno)==0)
        {
            bilet_sayisi++;
            if(bilet_sayisi==1)
            {
                printf("\n\nUcus No     \tKalkis Yeri     Varis Yeri     \tZamani     \tFiyati\n-------     \t-----------     ----------     \t------     \t------\n");
            }
                ucuslar=musteri.ucus_no;
                fseek(dosya,((ucuslar-1)*sizeof(liste)),SEEK_SET);
                fread(&liste,sizeof(liste),1,dosya);
                printf("%d\t\t%s\t\t%s\t\t%.2d.%.2d\t\t%.2f TL\n",liste.numara,liste.kalkisYeri,liste.varisYeri,liste.kalkisSaati,liste.kalkisDakikasi,musteri.bilet_fiyati);
        }
    }
    if(bilet_sayisi==0)
    {
        printf("\n\nAradiginiz numaraya kayitli bir bilet bulunmamaktadir.");
    }
}

void UcusEkle(FILE *dosya,int no)
{
    struct bilgi ucus;
    fseek(dosya,(no-1)*sizeof(ucus),SEEK_SET),
    fread(&ucus,sizeof(ucus),1,dosya);
    if(ucus.numara!=0)
    {
        printf("\n%d numarali ucus bulunmaktadir.",no);
    }
    else
    {
        printf("\nEklemek istediginiz bilgileri giriniz: \n\n");
        printf("Kalkis Yeri: ");
        scanf("%s",ucus.kalkisYeri);
        printf("Varis Yeri: ");
        scanf("%s",ucus.varisYeri);
        printf("Kalkis Saati: ");
        scanf("%d",&ucus.kalkisSaati);
        printf("Kalkis Dakikasi: ");
        scanf("%d",&ucus.kalkisDakikasi);
        printf("Koltuk Kapasitesi: ");
        scanf("%d",&ucus.koltukKapasitesi);
        printf("Baslangic bilet fiyati:");
        scanf("%f",&ucus.biletFiyati);
        ucus.numara=no;
        ucus.bosKoltukSayisi=ucus.koltukKapasitesi;
        fseek(dosya,((no-1)*sizeof(ucus)),SEEK_SET),
        fwrite(&ucus,sizeof(ucus),1,dosya);
        printf("\n\n%d numarali ucus asagidaki bilgilerle kaydedilmistir.\n\nUcus No     \tKalkis Yeri     Varis Yeri     \tZamani     \tKapasite     \tBilet Fiyati\n-------     \t-----------     ----------     \t------     \t----------    \t------------\n%d\t\t%s\t\t%s\t\t%.2d.%.2d\t\t%d\t\t%.2f%\n",no,ucus.numara,ucus.kalkisYeri,ucus.varisYeri,ucus.kalkisSaati,ucus.kalkisDakikasi,ucus.koltukKapasitesi,ucus.biletFiyati);
    }
}

void KayitSil(FILE *dosya,FILE *dosya2,int no)
{
    FILE *dosya3;
    struct bilgi liste;
    struct bilgi bos={0,"","",0,0,0,0,0.0};
    struct bilet musteri;
    fseek(dosya,((no-1)*sizeof(liste)), SEEK_SET);
    fread(&liste,sizeof(liste),1,dosya);
    if(liste.numara == 0)
    {
        printf("\nSilmek istediginiz %d numarali ucus zaten bulunmamaktadir.", no);
    }
    else
    {
        fseek(dosya, (no -1) * sizeof(struct bilgi), SEEK_SET);
        fwrite (&bos, sizeof(struct bilgi), 1, dosya);
        printf("\n\n%d numarali ucus silinmistir.\n\n",no);
        dosya3=fopen("biletyedek.txt","w");
        while(fscanf(dosya2,"%d\t%s\t%f\n",&musteri.ucus_no,musteri.TCno,&musteri.bilet_fiyati,&no)!=EOF)
        {
            if(musteri.ucus_no != no)
            {
                fprintf(dosya3,"%d\t%s\t%.2f\n",musteri.ucus_no,musteri.TCno,musteri.bilet_fiyati);
            }
        }
        fclose(dosya);
        fclose(dosya2);
        fclose(dosya3);
        remove("bilet.txt");
        rename("biletyedek.txt","bilet.txt");
    }
}

void ZamanDegistir(FILE *dosya,int no)
{
    struct bilgi liste;
    int kalkisSaatiGuncel,kalkisDakikasiGuncel;
    fseek(dosya,((no-1)*sizeof(liste)), SEEK_SET);
    fread(&liste,sizeof(liste),1,dosya);
    if(liste.numara == 0)
    {
        printf("\nGuncellemek istediginiz %d numarali ucus bulunmamaktadir.", no);
    }
    printf("\nUcus numarasina ait bilgiler su sekildedir:\n\nKalkis Yeri\t Varis Yeri\t Kalkis Zamani\t Koltuk Kapasitesi\n-----------\t ----------\t -------------\t -----------------\n");
    printf("%-20s%-20s%.2d:%-4.2d\t\t%-6d",liste.kalkisYeri,liste.varisYeri,liste.kalkisSaati,liste.kalkisDakikasi,liste.koltukKapasitesi);
    printf("\n\n\nYeni kalkis zamanini giriniz (saat ve dakika arasina : koyunuz): ");
    scanf("%d:%d",&kalkisSaatiGuncel,&kalkisDakikasiGuncel);
    liste.kalkisSaati=kalkisSaatiGuncel;
    liste.kalkisDakikasi=kalkisDakikasiGuncel;
    fseek(dosya,((no-1)*sizeof(liste)), SEEK_SET);
    fwrite(&liste,sizeof(liste),1,dosya);
    printf("\nYeni bilgiler su sekildedir:\n\n");
    printf("Kalkis Yeri\t Varis Yeri\t Kalkis Zamani\t Koltuk Kapasitesi\n");
    printf("-----------\t ----------\t -------------\t -----------------\n");
    printf("%-20s%-20s%.2d:%-4.2d\t\t%-6d",liste.kalkisYeri,liste.varisYeri,liste.kalkisSaati,liste.kalkisDakikasi,liste.koltukKapasitesi);
    printf("\n\n%d numarali ucusun kalkis zamani guncellenmistir.\n\n",no);
}

void BiletSatilmasi(FILE *dosya,FILE *dosya2,int no)
{
    struct bilet musteri;
    struct bilgi liste;
    int bilet_sayisi,a,i=100,j,m,o;
    float k=0.9,toplamFiyat,doluluk,bosKoltukOrani,ucret[100];
    char odemeKabul;
    fseek(dosya, (no -1) * sizeof(struct bilgi), SEEK_SET);
    fread(&liste, sizeof(struct bilgi), 1, dosya);
    if(liste.numara == 0)
    {
        printf("\nSatin almak istediginiz %d numarali ucus bulunmamaktadir.", no);
    }
    else
    {
        printf("\nUcus numarasina ait bilgiler su sekildedir:\n\n\nKalkis Yeri\t Varis Yeri\t Kalkis Zamani\t Koltuk Kapasitesi\t Bos Koltuk Sayisi\n-----------\t ----------\t -------------\t -----------------\t -----------------\n");
        printf("%-20s%-20s%.2d:%-4.2d\t\t%-6d\t\t\t%d\n",liste.kalkisYeri,liste.varisYeri,liste.kalkisSaati,liste.kalkisDakikasi,liste.koltukKapasitesi,liste.bosKoltukSayisi);
        printf("\n\nSatin almak istediginiz bilet sayisini giriniz:");
        scanf("%d",&bilet_sayisi);
        if(bilet_sayisi<= liste.bosKoltukSayisi)
        {
            for(j=1;j<=bilet_sayisi;j++)
            {
                doluluk=(float)((liste.koltukKapasitesi)-(liste.bosKoltukSayisi))*100/(liste.koltukKapasitesi);
                bosKoltukOrani=100-doluluk;
                for(i=100;i>=0;i-=10)
                {
                    a=i-10;
                    k=k+0.1;
                    if(i>=bosKoltukOrani && a<bosKoltukOrani)
                    {
                        ucret[j]=liste.biletFiyati*k;
                        printf("\n%d. kisinin odeyecegi ucret: %.2f TL",j,ucret[j]);
                        toplamFiyat+=ucret[j];
                    }
                }
                ucret[j+1]=toplamFiyat-ucret[j];
                liste.bosKoltukSayisi--;
            }
            printf("\n\nOdemeniz gereken toplam bilet fiyati:%.2f TL\n",toplamFiyat);
            printf("\nOdemeyi kabul ediyor musunuz? (kabul ediyorsaniz e yaziniz): ");
            scanf("%s",&odemeKabul);
            printf("\n");
            if(odemeKabul=='e'){
                for(m=1;m<=bilet_sayisi;m++){
                    printf("%d. bilet sahibinin tc kimlik numarasini giriniz: ",m);
                    scanf("%s",musteri.TCno);
                    fprintf(dosya2,"%d ",no);
                    fputs(musteri.TCno,dosya2);
                    fprintf(dosya2," %.2f\n",ucret[m]);
                }
                fseek(dosya,((no-1)*sizeof(liste)),SEEK_SET);
                fwrite(&liste,sizeof(liste),1,dosya);
                printf("\nBilet satin alma islemi basariyla gerceklesti.\n");
                printf("\n\nBos koltuk sayisinin guncellenmis hali su sekildedir:\n\n\nKalkis Yeri\t Varis Yeri\t Kalkis Zamani\t Koltuk Kapasitesi\t Bos Koltuk Sayisi\n-----------\t ----------\t -------------\t -----------------\t -----------------\n");
                printf("%-20s%-20s%.2d:%-4.2d\t\t%-6d\t\t\t%d\n",liste.kalkisYeri,liste.varisYeri,liste.kalkisSaati,liste.kalkisDakikasi,liste.koltukKapasitesi,liste.bosKoltukSayisi);
                printf("\n\nBos koltuk sayisi guncellenmistir.\n");
            }
            else
            {
                printf("\nBilet satin alma islemi iptal edildi.\n");
            }
        }
        else
        {
            printf("\n%d numarali ucusta yeterince bos koltuk bulunmamaktadir.\n",no);
        }
    }

}

int main()
{
    FILE *dosya;
    FILE *dosya2;
    char devam;
    int secim1,secim2,no;
    printf("Havayolu Bilet Satis Sistemine Hos Geldiniz!\n");
    do
    {
        if((dosya=fopen("ucus.dat","rb+"))==NULL||(dosya2=fopen("bilet.txt","a+"))==NULL)
        {
            printf("Dosya yok.");
            return 0;
        }
        printf("1.Sorgulama Programi\n2.Guncelleme Programi\n:");
        scanf("%d",&secim1);
        if(secim1==1)
        {
            printf("\n1.Bir ucusa ait bilgileri listele\n2.Bir ucusa ait bilgileri ve satilan biletleri listele\n3.Bir yerden kalkan ucuslari listele\n4.Koltuk doluluk orani %%50 altindaki ucuslari listele\n5.Bir yolcuya ait biletleri listele\n:");
            scanf("%d",&secim2);
            if(secim2==1||secim2==2)
            {
                printf("\nUcus numarasi giriniz:");
                scanf("%d",&no);
                while(no<1||no>1000)
                {
                    printf("Ucus numarasi 1-1000 arasi bir tam sayi olmalidir, lutfen tekrar deneyiniz:");
                    scanf("%d",&no);
                }
            }
            switch(secim2)
            {
                case 1:
                    UcusveBiletListele(dosya,dosya2,no,secim2);
                    break;

                case 2:
                    UcusveBiletListele(dosya,dosya2,no,secim2);
                    break;

                case 3:
                    KalkisYeriAra(dosya);
                    break;

                case 4:
                    YuzdeElliAlti(dosya);
                    break;

                case 5:
                    YolcuBilgileri(dosya,dosya2);
                    break;
            }
        }
        else
        {
            printf("\n1.Yeni ucus ekle\n2.Ucus kaydi sil\n3.Ucus kalkis zamanini degistir\n4.Bilet satin al\n:");
            scanf("%d",&secim2);
            printf("\nUcus numarasi giriniz:");
            scanf("%d",&no);
            while(no<1||no>1000)
            {
                printf("Ucus numarasi 1-1000 arasi bir tam sayi olmalidir, lutfen tekrar deneyiniz:");
                scanf("%d",&no);
            }
            switch(secim2)
            {
                case 1:
                    UcusEkle(dosya,no);
                    break;

                case 2:
                    KayitSil(dosya,dosya2,no);
                    break;

                case 3:
                    ZamanDegistir(dosya,no);
                    break;

                case 4:
                    BiletSatilmasi(dosya,dosya2,no);
                    break;
            }
        }
        fclose(dosya);
        fclose(dosya2);
        printf("\n\n\nPrograma devam etmek icin 'e'yi, cikis yapmak icin herhangi bir tusu tuslayiniz.");
        scanf(" %c",&devam);
    }while((devam)=='e'||(devam)=='E');
    printf("\n\n\n\t\tTesekkur ederiz!");
    return 0;
}

