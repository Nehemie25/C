#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Noeud Noeud;
struct Noeud
{
char libele[50];
double ordre;
int quantite;
float prix;
Noeud *gauche;
Noeud *droit;
};

typedef struct Arbre Arbre;
struct Arbre{
Noeud *racine;
};





    void afficher(Noeud *racine)
    {
        if( racine->gauche!=NULL)
        {
            afficher(racine->gauche);
        }
        if( racine->droit!=NULL)
        {
            afficher(racine->droit );
        }
        if(racine->quantite !=0)
        {

        printf("le medicament %s a pour odre %f et est au nombre de %d dans le stock   et au prix de %f \n",racine->libele , racine->ordre, racine->quantite, racine->prix);
        }
    }

    void  remplir(Noeud *racine ,Noeud *nouveau)
    {
       if(nouveau->ordre < racine->ordre && racine->gauche !=NULL)
       {
           remplir(racine->gauche , nouveau);

       }
       if(nouveau->ordre > racine->ordre && racine->droit !=NULL)
       {
           remplir(racine->droit , nouveau);

       }

       if(racine->ordre > nouveau->ordre && racine->gauche==NULL)
       {

           racine->gauche =nouveau;

       }
        if(racine->ordre < nouveau->ordre && racine->droit==NULL)
       {
           racine->droit = nouveau;

       }


    }


double hachage(char libele[50])
{
char lettres[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
double numero[26]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
int longueur = strlen(libele);


double mothache=0;
  int k=1;



    for(int i=0 ; i< longueur ; i++)
    {
        for(int j = 0 ; j< 26 ; j++)
        {
          if(lettres[j]== libele[i])
          {



         mothache   +=(numero[j])/(10*k);
         k++;

        }
        }

    }

      return mothache;
}

Arbre *initialisation()
{
    Arbre *new = malloc(sizeof(Arbre));
    Noeud *nouveau = malloc(sizeof(Noeud));

    printf("entrer le libele du premier medicament\n");
    scanf("%s",nouveau->libele);
    printf("entrer la quantite du premier medicament \n");
    scanf("%d",&nouveau->quantite);
    printf("entrer le prix du premier medicament \n");
    scanf("%f",&nouveau->prix);
    nouveau->droit = NULL;
    nouveau->gauche =  NULL;
    nouveau->ordre = hachage(nouveau->libele);
    printf(" l'ordre du medicament  %s apres hachage de son libele est %f \n", nouveau->libele, nouveau->ordre);


    new->racine= nouveau;

    return new;
}


void  vente(Noeud *racine ,Noeud *nouveau)
    {



        if(nouveau->ordre < racine->ordre && racine->gauche == NULL)
        {
            printf("le produit n'existe pas\n");
        }


        if(nouveau->ordre >racine->ordre && racine->droit == NULL)
        {
            printf("le produit n'existe pas\n");
        }



    if(racine->ordre == nouveau->ordre && racine->quantite< nouveau->quantite)
    {
        printf("le  stock est insuffisant \n");

    }


    if(racine->ordre == nouveau->ordre && racine->quantite>= nouveau->quantite)
    {
        racine->quantite -= nouveau->quantite;
        if(racine->quantite == 0)
        {
            nettoyer(racine);
        }
    }
    else
    {
        if(nouveau->ordre < racine->ordre)
        {
            vente(racine->gauche , nouveau);
        }
        if(nouveau->ordre > racine->ordre)
        {
            vente(racine->droit,nouveau);
        }
    }



    }




void  achat(Noeud *racine ,Noeud *nouveau)
    {

        if(nouveau->ordre < racine->ordre && racine->gauche == NULL)
        {
            racine->gauche = nouveau;
        }


        if(nouveau->ordre >racine->ordre && racine->droit == NULL)
        {
            racine->droit = nouveau;
        }






    if(racine->ordre == nouveau->ordre)
    {
        racine->quantite += nouveau->quantite;
        racine->prix = nouveau->prix;
    }
    else
    {
        if(nouveau->ordre < racine->ordre)
        {
            achat(racine->gauche , nouveau);
        }
        if(nouveau->ordre > racine->ordre)
        {
            achat(racine->droit,nouveau);
        }
    }



    }


    Noeud *rechercheMax( Noeud *A)
{
    if(A->droit == NULL)
    {
Noeud *arenvoyer = malloc(sizeof(Noeud));
     arenvoyer = A;
     A = A->gauche;
     return arenvoyer;
    }
    else{
        rechercheMax(A->droit);
    }
}



void nettoyer(Noeud *racine)
{
    if(racine->droit == NULL && racine->gauche == NULL)
    {
        free(racine);
    }
    if(racine->droit !=NULL && racine->gauche== NULL)
    {
        Noeud *assuprimer = malloc(sizeof(Noeud));
        assuprimer = racine;
        racine = racine->droit;
        free(assuprimer);
    }
    if(racine->gauche !=NULL && racine->droit== NULL)
    {
        Noeud *assuprimer = malloc(sizeof(Noeud));
        assuprimer = racine;
        racine = racine->gauche;
        free(assuprimer);
    }
    if(racine->gauche != NULL && racine->droit != NULL)
    {
         Noeud *assuprimer = malloc(sizeof(Noeud));
         assuprimer = racine;
         racine = rechercheMax(racine->gauche);
         free(assuprimer);

    }


}




//representation d'un medicament
typedef struct medicament
{
char libelle[30];
int qtedispo;
int prix_unitaire;
}medicament;

//representtion d"un stcck de madicament
typedef struct stock
{
medicament Mede;
struct stock* next;
}stock;

//procedure permettant de vendre(med, NbBoitees)

void vendre(stock* st, char Med[30], int NbBoites)
   {
     stock* st1=st;
     while(st1!=NULL && strcmp(st1->Mede.libelle,Med)!=0)
         {
           st1=st1->next;
         }

      if(st1==NULL)
       {
        printf("le medicament %s n'existe pas",Med);
       }
      else //sinon on a trouve le medicament
       {
           if(st1->Mede.qtedispo < NbBoites)
            {
               printf("le stock est insuffisant\n");
            }

            else //on sostraire lenombre de boites
            {
               st1->Mede.qtedispo-=NbBoites;
               printf("il vous reste %d boites de %s dans le stock de medicament\n",st1->Mede.qtedispo,st1->Mede.libelle);
               printf("et le client doit payer %d FCFA",NbBoites*st1->Mede.prix_unitaire);

               if(st1->Mede.qtedispo==0)
                {
                  stock* se=st1;
                    st1=st1->next;
                   se->next=NULL;
                    free(se);
                }
            }
        }
    }

//procedure acheter(Med, NBboites,prix permettant d'alimenter le stock de medicament

void acheter( stock* s, char Med[30], int NbBoites, int prise)
    {
      stock* st1=s;
      stock* st3=NULL;
      while(st1!= NULL && strcmp(st1->Mede.libelle,Med)!=0)
          {
           st3=st1;
           st1=st1->next;
          }

         if(st1!=NULL)//LE MEDICAMENT EXISTE DEJA
          {
           st1->Mede.qtedispo +=NbBoites;
           st1->Mede.prix_unitaire=prise;
           printf("votre stock contient a present %d %s\n",st1->Mede.qtedispo,st1->Mede.libelle);
           printf("le nouveau prix est de %d FCFA\n",st1->Mede.prix_unitaire);
           printf("Et vous devez payer %d FCFA a votre fourniseur\n",NbBoites*st1->Mede.prix_unitaire);
          }

         else
          {
            stock* new=malloc(sizeof(stock*));
            new->next=NULL;
            strcpy(new->Mede.libelle, Med);
            new->Mede.qtedispo=NbBoites;
            new->Mede.prix_unitaire=prise;
//insertion du nouvea medicament dans la liste
            st3->next=new;
            printf("bravo vous avez acheter un nouveau medicament, il a deja ete inserer dans le stock\n");
         }
   }



//fonction prixstock permettant bde calcler le total des medicaments

 int prix_stock(stock* S)
    {
         int total=0;
         stock* st1= S;
         while(st1 !=NULL)
        {
         total +=st1->Mede.qtedispo*st1->Mede.prix_unitaire;
         st1=st1->next;
        }

         return total;
    }

//fontion remplissage permt de remplir et renvoyer la liste de medicament

stock* remplissage(stock* stocke)
    {
     int choix=0;
      stock* st2;
      stocke=NULL;
      st2=stocke;

    do
     {
      stock* new;
      new=malloc(sizeof(stock));
      printf("entrer le nom du medicament\n");
      scanf("%s",new->Mede.libelle);
      printf("entrer la quantite du medicament\n");
      scanf("%d",&new->Mede.qtedispo);
      printf("entrer le prix unitaire du medicament\n");
      scanf("%d",&new->Mede.prix_unitaire);
//insertion en tete
      new->next=st2;
      st2=new;
     // st2->next=NULL;
      printf("\n\n");
      printf("voulez-vous continuer?\n");
     printf("entrer 1 pour 'oui' et n'importe quel caractere pour dire 'non'\n");
     scanf("%d",&choix);
     printf("\n");

    }while(choix==1);

return st2;
}

void Affichestock(stock* st1 )
{
    stock* st2=st1;
    while(st2!=NULL)
        {
        printf("nom:%s   quantite:%d      prix:%d FCFA\n", st2->Mede.libelle, st2->Mede.qtedispo, st2->Mede.prix_unitaire);
        st2=st2->next;
        }
}







int main()
  {
       int l;
       stock* stocke;
       stock* stockes;
       int ange;
        printf("          BIENVENUE DANS LA GESTION DE LA PHARMACIE DU GROUPE 14\n\n");
        printf("              MEMBRE DU GROUPE \n");
        printf("\n");
        printf("  NGOUMTSA  TEFOUEGUE KEVIN                     18S07997\n");
        printf("  NGUEMENI SILIENOU MBEUME DOMINIQUE            18S07776\n");
        printf("  NGUETCHO NGUEDJA ANGE MARTINET                18S07837\n");
        printf("  NGUIMBOUS NEHEMIE                             18S07998\n");
        printf("  NJICHEKOUOP  NOURDINE                         18S08037\n");
        printf("\n");

    int saisie =1;
    do
    {
    int partie=0;


    printf("CE PROGRAMME COMPORTE 2 PARTIES \n");
    printf("LA PARTIE 1 BASEE SUR LES LISTES CHAINEES SIMPLES \n");
    printf("LA PARTIE 2 BASEE SUR LES ARBRES BINAIRES DE RECHERCHE \n");
    printf("TAPER 0 POUR ACCEDER A LA PREMIERE PARTIE  1 POUR ACCEDER A LA DEUXIEME PARTIE \n");
    scanf("%d" , &partie);



    if(partie == 0)
    {



        printf("POUR VOTRE PREMIERE UTILISATION VOUS DEVEZ D'ABORS CHARGER VOTRE STOCK DE MEDICAMENTS\n\n ");



       //REMPLISAGE D STOCT D MDICAMENT PAR L'APPEL DE LAFONCTION REMPLISSAGE

         stocke=remplissage(stockes);
         printf("\n");

          do
            {
              printf("\n");
              printf("choissisez\n 1-si vous voulez VENDRE\n");
              printf(" 2-si vous voulez ACHETER \n ");
              printf(" 3- si vous voulez consulter votre stock de medicament\n");
              printf("4-si vous voulez connaitre le prix total des medicaments disponible\n");

             int a;
             scanf("%d",&a);

             if(a==1)
               {
                 char medoc[30];
                 int b;
                 printf("\n");
                 printf("quel medicament voulez-vous vendre ?\n");
                 scanf("%s", medoc);
                 printf("combien de boites en voulez vous?\n");
                 scanf("%d", &b);
                 vendre(stocke, medoc, b);
                 printf("\n");
               }

              else if(a==2)
               {
                char medi[30];
                int nb;
                int prise;
                printf("\n");
                printf("quel medicament voulez-vous acheter? \n");
                scanf("%s",medi);
                printf("combien de boites voulez-vous acheter ?\n");
                scanf("%d",&nb);
                printf("entrer le nouveau prix\n");
                scanf("%d",&prise);
                acheter(stocke, medi, nb, prise);
                printf("\n");
               }

              else if(a==3)
              {
                  Affichestock(stocke);
              }

              else if(a==4)
               {
               int tot=0;
                tot=prix_stock(stocke);
                printf("\n");
                printf("le prix total des medicaments est de %d FCFA\n",tot);
                printf("\n");
               }

              else
               {
                 printf("\n");
                 printf("vous ne voulez rien? vous etes certainement un visiteur\n");
                 printf("\n");
               }
                 printf("\n");
                 printf("voulez-vous revernir au menu?\n entrez'1' pour oui et n'importe quel autre chiffre pour non\n");

                 scanf("%d",&ange);
                 printf("\n");

                 }while(ange==1);


    }
   else if(partie == 1)
    {





    int test;
 int test1;
 int test2;
 int reponse;

printf("Bienvenu sur la pharmacie du groupe 14 base sur les arbres binaires de recherche \n");
Arbre *arbre1 = malloc(sizeof(Arbre));
arbre1= initialisation();


do
{
Noeud *nouveau = malloc(sizeof(Noeud));
printf("Notez que l'insertion des medicaments dans le stock se fait conformement a l'insertion de noeuds dans un arbre binaire de recherche \n");

printf("entrer le libele du medicament que vous souhaitez ajouter dans le stock\n");
scanf("%s",nouveau->libele);
printf("entrer le nombre de boites \n");
scanf("%d",&nouveau->quantite);
printf("entrer le prix de ce medicament\n");
scanf("%f",&nouveau->prix);
nouveau->ordre = hachage(nouveau->libele);
printf(" l'ordre du medicament  %s apres hachage de son libele est %f \n", nouveau->libele, nouveau->ordre);

nouveau->gauche=NULL;
nouveau->droit =NULL;
remplir(arbre1->racine , nouveau);


printf("voulez vous encore inserer un element dans larbre de recherche ? si oui taper 1 sinon tapez 0 \n");
scanf("%d",&test);

}while(test==1);




printf("Quel action souhaitez vous effectuer maintenant?\n");
printf("Tapez 1  pour Vendre 2 pour Acheter \n");
scanf("%d",&reponse);

if(reponse ==1)
{
    do
    {

Noeud *nouveau = malloc(sizeof(Noeud));
printf("Entrer le libele du  medicament que vous souhaitez vendre\n");
scanf("%s",nouveau->libele);
printf("Entrer le nombre de boites que vous souhaitez vendre \n");
scanf("%d",&nouveau->quantite);
nouveau->ordre = hachage(nouveau->libele);

nouveau->gauche=NULL;
nouveau->droit =NULL;
vente(arbre1->racine , nouveau);

printf("voulez vous encore vendre un medicament  ? si oui taper 1 sinon tapez 0 \n");
scanf("%d",&test1);

}while(test1 == 1);
}


if(reponse ==2)
{
    do
    {

Noeud *nouveau = malloc(sizeof(Noeud));
printf("Entrer le libele du medicament que vous souhaitez acheter\n");
scanf("%s",nouveau->libele);
printf("Entrer le nombre de boites \n");
scanf("%d",&nouveau->quantite);
printf("Entrer le nouveau prix du medicament \n");
scanf("%f",&nouveau->prix);

nouveau->ordre = hachage(nouveau->libele);
printf("%f \n", nouveau->ordre);
nouveau->gauche=NULL;
nouveau->droit =NULL;
achat(arbre1->racine , nouveau);
printf("voulez vous encore acheter un medicament  ? si oui taper 1 sinon tapez 0 \n");
scanf("%d",&test2);


    }while(test2 == 1);
}

 printf("Notez que cet affichage se fait par parcours Postfixe de l'arbre binaire de recherche \n");

afficher(arbre1->racine);





}
else
{
    printf("DESOLE VOUS N'AVEZ SAISI NI 0 NI 1 CE CHOIX NEST PAS PRI EN COMPTE \n");
}





   printf("SOUHAITEZ VOUS REVENIR AU DEBUT DU PROGRAMME ?  SI OUI TAPEZ 1 SI NON TAPEZ AUTRE CHOSE  \n");
scanf("%d" ,&saisie);

}while( saisie == 1);


    return 0;
}
