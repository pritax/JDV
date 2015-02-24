#include "define_res.h"

#define REMPLIR_EN_TETE__ p_chaine_complete+(controleur_des_flags--);

PAQUET* decoupeMsg(char* p_chaine_complete)
    {
        int
            controleur_des_flags=15,
            controleur_de_donnees=16,
            i=0;
        char caractere_actuel='';
        
        HEADER en_tete;
        DATA donnees;
        
            en_tete.F_HELLOMESSAGE          = REMPLIR_EN_TETE__
            en_tete.F_HELLOREPLY            = REMPLIR_EN_TETE__
            en_tete.F_CHANGEOWNERREQUEST    = REMPLIR_EN_TETE__
            en_tete.F_CHANGEOWNERREPLY      = REMPLIR_EN_TETE__
            en_tete.F_CHANGEOWNERORDER      = REMPLIR_EN_TETE__
            en_tete.F_GLOBALUPDATEREQUEST   = REMPLIR_EN_TETE__
            en_tete.F_GLOBALUPDATEREPLY     = REMPLIR_EN_TETE__
            en_tete.F_GLOBALUPDATECHALLENGE = REMPLIR_EN_TETE__
            en_tete.F_GLOBALUPDATEORDER     = REMPLIR_EN_TETE__
            en_tete.F_DELETEUSER            = REMPLIR_EN_TETE__
            en_tete.F_MOVEPECHEUR           = REMPLIR_EN_TETE__
            en_tete.F_MOVERESSOURCE         = REMPLIR_EN_TETE__
            en_tete.F_ADDRESSOURCE          = REMPLIR_EN_TETE__
            en_tete.F_RESERVEE1             = REMPLIR_EN_TETE__
            en_tete.F_RESERVEE2             = REMPLIR_EN_TETE__
            en_tete.F_RESERVEE3             = REMPLIR_EN_TETE__
            
            
            if ( controleur_des_flags != __VALEUR_ERROR__)
                    perror("Erreur chargement en-tête");
                    
            for(i=0,controleur_de_donnees;(caractere_actuel = *(p_chaine_complete+controleur_de_donnees)) != __FIN_CHAINE__;i++,controleur_de_donnees++)
                    donneees.message[i]=caractere_actuel;
            
            
            donnees.message[i]=__FIN_CHAINE__;
            
            return remplirPaquet(en_tete, donnees);
    }
    
PAQUET* remplirPaquet(HEADER en_tete, DATA donnees)
    {
        PAQUET* p_paquet = NULL;
        
        
        if ( (p_paquet = malloc(sizeof(PAQUET))) == NULL ) { perror("Malloc fail"); return NULL; }
        
        p_paquet->header        = en_tete;
        p_paquet->data          = donnees;
        p_paquet->position_read = __HEADERSIZE__;
        
        return p_paquet;
    }
    
int isSet(char Flag)
    {
        return (Flag == F_SET);
        
    }

void apduControlleur(PAQUET* p_paquet,MODE mode_actuel)
{
    
    int i=0;
    for(i=0;i<__HEADERSIZE__;++i)
    {
        switch(i)
        {
            case T_HELLOMESSAGE:
                if(mode_actuel==M_reception && isSet(F_HELLOMESSAGE));
                {
                            printf(" F_HELLOMESSAGE PACKET RECEIVED ! ");
                            //on_helloMessage(p_pqauet,mode_actuel);
                            // Si M_envoi alors hello ENCAPSULE le paquet
                            // Sinon (M_reception) DESENCAPSULE le paquet
                }
                if(mode_actuel==M_envoi && !isSet(F_HELLOMESSAGE));
                {
                    //on met à F_SET le flag F_HELLOMESSAGE via la fonction F_set(flag)

                }
            break;
            case T_HELLOREPLY:
                if(isSet(F_HELLOREPLY);
            break;
            case T_CHANGEOWNERREQUEST:
                if(isSet(F_CHANGEOWNERREQUEST));
            break;
            case T_CHANGEOWNERREPLY:
                if(isSet(F_CHANGEOWNERREPLY));
            break;
            case T_CHANGEOWNERORDER:
                if(isSet(F_CHANGEOWNERORDER));
            break;
            case T_GLOBALUPDATEREQUEST:
                if(isSet(F_GLOBALUPDATEREQUEST));
            break;
            case T_GLOBALUPDATEREPLY:
                if(isSet(F_GLOBALUPDATEREPLY));
            break;
            case T_GLOBALUPDATEORDER:
                if(isSet(F_GLOBALUPDATEORDER));
            break;
            case T_GLOBALUPDATECHALLENGE:
                if(isSet(F_GLOBALUPDATECHALLENGE));
            break;
            case T_DELETEUSER:
                if(isSet(F_DELETEUSER));
            break;
            case T_MOVEPECHEUR:
                if(isSet(F_MOVEPECHEUR));
            break;
            case T_MOVERESSOURCE:
                if(isSet(F_MOVERESSOURCE));
            break;
            case T_ADDRESSOURCE:
                if(isSet(F_ADDRESSOURCE));
            break;
            case T_RESERVEE1:
                if(isSet(F_RESERVEE1));
            break;
            case T_RESERVEE2:
                if(isSet(F_RESERVEE2));
            break;
            case T_RESERVEE3:
                if(isSet(F_RESERVEE3));
            break;
            default:
            break;
        } 
    }   
}
