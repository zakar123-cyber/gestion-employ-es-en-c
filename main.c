#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date {
    int j, m, a, h, min;
} Date;
typedef struct Time {
    int h, min;
} Time;
typedef struct horaire {
    Date j_ferier, m_ferier, a_ferier;
    char type[20], desc[20], status[20], motif[20];
    Date j_cong, m_cong, a_cong, fin_j_cong, fin_m_cong, fin_a_cong;
    Date j_trav, m_trav, a_trav, h_trav, min_trav;
    struct horaire *suivant;
} Horaire;

typedef struct Employee {
    char nom[20], prenom[20];
    int jn, mn, an, num_telephone;
    Horaire *horair;
    char adresse[20], email[20];
    struct Employee *suivant;
} Employee;

//typedef Employee* list

Employee *ajout_debut(Employee *tete) {
    Employee *nv = (Employee *)malloc(sizeof(Employee));

    printf("Donner le nom et le prenom: ");
    scanf("%s %s", nv->nom, nv->prenom);
    printf("Donner la date de naissance (j/m/a): ");
    scanf("%d %d %d", &nv->jn, &nv->mn, &nv->an);
    printf("Donner l'adresse: ");
    scanf("%s", nv->adresse);
    printf("Donner l'email: ");
    scanf("%s", nv->email);
    printf("Numero de telephone: ");
    scanf("%d", &nv->num_telephone);
    nv->suivant = tete;
    nv->horair = NULL;

    return nv;
}

Employee *ajout_fin(Employee *tete) {
    Employee *nv = (Employee *)malloc(sizeof(Employee));
    Employee *p = tete;

    printf("Donner le nom et le prenom: ");
    scanf("%s %s", nv->nom, nv->prenom);
    printf("Donner la date de naissance (j/m/a): ");
    scanf("%d %d %d", &nv->jn, &nv->mn, &nv->an);
    printf("Donner l'adresse: ");
    scanf("%s", nv->adresse);
    printf("Donner l'email: ");
    scanf("%s", nv->email);
    printf("Numero de telephone: ");
    scanf("%d", &nv->num_telephone);
    nv->suivant = NULL;
    nv->horair = NULL;

    if (tete == NULL) {
        return nv;
    }

    while (p->suivant != NULL) {
        p = p->suivant;
    }
    p->suivant = nv;

    return tete;
}

Employee *ajout_apres_un_employee(Employee *tete) {
    char nom[20], prenom[20];
    Employee *nv = (Employee *)malloc(sizeof(Employee));
    Employee *p = tete;

    printf("Donner le nom et prenom de l'employe specifique: ");
    scanf("%s %s", nom, prenom);

    while (p != NULL && (strcmp(p->nom, nom) != 0 || strcmp(p->prenom, prenom) != 0)) {
        p = p->suivant;
    }

    if (p == NULL) {
        printf("L'employe est introuvable.\n");
        free(nv);
    } else {
        printf("Employe trouve!\n");
        printf("Donner le nom et le prenom: ");
        scanf("%s %s", nv->nom, nv->prenom);
        printf("Donner la date de naissance (j/m/a): ");
        scanf("%d %d %d", &nv->jn, &nv->mn, &nv->an);
        printf("Donner l'adresse: ");
        scanf("%s", nv->adresse);
        printf("Donner l'email: ");
        scanf("%s", nv->email);
        printf("Numero de telephone: ");
        scanf("%d", &nv->num_telephone);
        nv->suivant = p->suivant;
        nv->horair = NULL;
        p->suivant = nv;
    }

    return tete;
}

Employee *SuppDeb(Employee *tete) {
    if (tete == NULL) {
        printf("Liste vide!\n");
        return tete;
    }

    Employee *p = tete;
    tete = tete->suivant;
    free(p);
    return tete;
}

Employee *SuppFin(Employee *tete) {
    if (tete == NULL) {
        printf("Liste vide!\n");
        return tete;
    }

    if (tete->suivant == NULL) {
        free(tete);
        return NULL;
    }

    Employee *p = tete;
    Employee *prec = NULL;

    while (p->suivant != NULL) {
        prec = p;
        p = p->suivant;
    }

    free(p);
    prec->suivant = NULL;

    return tete;
}

Employee *SuppPos(Employee *tete, char *noms, char *prenoms) {
    if (tete == NULL) {
        printf("Liste vide!\n");
        return tete;
    }

    Employee *p = tete;
    Employee *prec = NULL;

    while (p != NULL && (strcmp(p->nom, noms) != 0 || strcmp(p->prenom, prenoms) != 0)) {
        prec = p;
        p = p->suivant;
    }

    if (p == NULL) {
        printf("Employe introuvable.\n");
    } else {
        if (prec == NULL) {
            tete = p->suivant;
        } else {
            prec->suivant = p->suivant;
        }
        free(p);
    }

    return tete;
}

void modification_profile_employes(Employee *tete) {
    char nom_v[20];
    int tel;

    printf("Saisir le nom et le numero de telephone: ");
    scanf("%s %d", nom_v, &tel);

    Employee *p = tete;

    while (p != NULL && (strcmp(p->nom, nom_v) != 0 || p->num_telephone != tel)) {
        p = p->suivant;
    }

    if (p == NULL) {
        printf("L'employe n'existe pas.\n");
    } else {
        printf("Saisir l'adresse: ");
        scanf("%s", p->adresse);
        printf("Saisir le numero de telephone: ");
        scanf("%d", &p->num_telephone);
        printf("Saisir l'adresse e-mail: ");
        scanf("%s", p->email);
        printf("Profil modifie avec succes.\n");
    }
}

void cherche_par_nom(Employee *tete) {
    char nom[20];

    printf("Donner le nom de l'employe cherche: ");
    scanf("%s", nom);

    Employee *p = tete;

    while (p != NULL && strcmp(p->nom, nom) != 0) {
        p = p->suivant;
    }

    if (p == NULL) {
        printf("Employe introuvable.\n");
    } else {
        printf("Nom: %s\nPrenom: %s\n", p->nom, p->prenom);
        printf("Date de naissance: %d/%d/%d\n", p->jn, p->mn, p->an);
        printf("Adresse: %s\n", p->adresse);
        printf("Email: %s\n", p->email);
        printf("Numero de telephone: %d\n", p->num_telephone);
    }
}

void cherche_par_telephone(Employee *tete) {
    int telephone_ch;

    printf("Donner le numero de telephone cherche: ");
    scanf("%d", &telephone_ch);

    Employee *p = tete;

    while (p != NULL && telephone_ch != p->num_telephone) {
        p = p->suivant;
    }

    if (p == NULL) {
        printf("Employe introuvable.\n");
    } else {
        printf("Nom: %s\nPrenom: %s\n", p->nom, p->prenom);
        printf("Date de naissance: %d/%d/%d\n", p->jn, p->mn, p->an);
        printf("Adresse: %s\n", p->adresse);
        printf("Email: %s\n", p->email);
        printf("Numero de telephone: %d\n", p->num_telephone);
    }
}

void cherche_par_adresse(Employee *tete) {
    char adresse[20];

    printf("Donner l'adresse de l'employe cherche: ");
    scanf("%s", adresse);

    Employee *p = tete;

    while (p != NULL && strcmp(p->adresse, adresse) != 0) {
        p = p->suivant;
    }

    if (p == NULL) {
        printf("Employe introuvable.\n");
    } else {
        printf("Nom: %s\nPrenom: %s\n", p->nom, p->prenom);
        printf("Date de naissance: %d/%d/%d\n", p->jn, p->mn, p->an);
        printf("Adresse: %s\n", p->adresse);
        printf("Email: %s\n", p->email);
        printf("Numero de telephone: %d\n", p->num_telephone);
    }
}

void cherche_par_email(Employee *tete) {
    char email[100];

    printf("Donner l'email de l'employe cherche: ");
    scanf("%s", email);

    Employee *p = tete;

    while (p != NULL && strcmp(p->email, email) != 0) {
        p = p->suivant;
    }

    if (p == NULL) {
        printf("Employe introuvable.\n");
    } else {
        printf("Nom: %s\nPrenom: %s\n", p->nom, p->prenom);
        printf("Date de naissance: %d/%d/%d\n", p->jn, p->mn, p->an);
        printf("Adresse: %s\n", p->adresse);
        printf("Email: %s\n", p->email);
        printf("Numero de telephone: %d\n", p->num_telephone);
    }
}
Horaire *creation_liste_trav(Horaire *tete) {
    Horaire *p = (Horaire*)malloc(sizeof(Horaire));
    if (p == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        return tete;
    }

    printf("Entrer l'horaire de travail:\n");
    printf("Saisir l'heure et les minutes de travail (h min): ");
    scanf("%d %d", &p->h_trav.h, &p->min_trav.min);
    printf("Saisir la date (j/m/a): ");
    scanf("%d %d %d", &p->j_trav.j, &p->j_trav.m, &p->j_trav.a);

    p->suivant = tete;
    return p;
}

Employee* Recherche_et_saisie_horaire_de_profil(Employee *tete) {
    Employee *p = tete;
    int choix;
    char nom[20], prenom[20], email[20];
    int numero;

    printf("Recherche un profil d'employé par:\n1. Nom et prénom\n2. Email\n3. Numéro de téléphone\n");
    scanf("%d", &choix);
    switch (choix) {
        case 1:
            printf("Donner le nom et prénom recherchés: ");
            scanf("%s %s", nom, prenom);
            while (p != NULL) {
                if (strcmp(nom, p->nom) == 0 && strcmp(prenom, p->prenom) == 0) {
                    printf("Ajout des horaires pour l'employé %s %s\n", p->nom, p->prenom);
                    p->horair = creation_liste_trav(p->horair);
                    return tete;
                }
                p = p->suivant;
            }
            printf("Employé introuvable.\n");
            break;
        case 2:
            printf("Donner l'email: ");
            scanf("%s", email);
            while (p != NULL) {
                if (strcmp(email, p->email) == 0) {
                    printf("Ajout des horaires pour l'employé avec l'email %s\n", p->email);
                    p->horair = creation_liste_trav(p->horair);
                    return tete;
                }
                p = p->suivant;
            }
            printf("Employé introuvable.\n");
            break;
        case 3:
            printf("Donner le numéro de téléphone: ");
            scanf("%d", &numero);
            while (p != NULL) {
                if (numero == p->num_telephone) {
                    printf("Ajout des horaires pour l'employé avec le numéro %d\n", p->num_telephone);
                    p->horair = creation_liste_trav(p->horair);
                    return tete;
                }
                p = p->suivant;
            }
            printf("Employé introuvable.\n");
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }

    return tete;
}

Employee* ajuster_horaires(Employee *employe) {
    int choix;
    Horaire *nouvelHoraire = malloc(sizeof(Horaire));
    if (nouvelHoraire == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        return employe;
    }

    printf("Choisissez le type d'horaire:\n1. Jour férié\n2. Congé\n3. Travail\n");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            printf("Entrez la date du jour férié (j/m/a): ");
            scanf("%d %d %d", &nouvelHoraire->j_ferier.j, &nouvelHoraire->j_ferier.m, &nouvelHoraire->j_ferier.a);
            printf("Entrez le type du jour férié et une description: ");
            scanf("%s %s", nouvelHoraire->type, nouvelHoraire->desc);
            break;
        case 2:
            printf("Entrez la date de début de congé (j/m/a): ");
            scanf("%d %d %d", &nouvelHoraire->j_cong.j, &nouvelHoraire->j_cong.m, &nouvelHoraire->j_cong.a);
            printf("Entrez la date de fin de congé (j/m/a): ");
            scanf("%d %d %d", &nouvelHoraire->fin_j_cong.j, &nouvelHoraire->fin_j_cong.m, &nouvelHoraire->fin_j_cong.a);
            printf("Saisir le motif du congé: ");
            scanf("%s", nouvelHoraire->motif);
            break;
        case 3:
            printf("Entrez la date de travail (j/m/a): ");
            scanf("%d %d %d", &nouvelHoraire->j_trav.j, &nouvelHoraire->j_trav.m, &nouvelHoraire->j_trav.a);
            printf("Entrez l'heure de travail (h): ");
            scanf("%d", &nouvelHoraire->h_trav.h);
            printf("Entrez les minutes de travail (min): ");
            scanf("%d", &nouvelHoraire->min_trav.min);
            break;
        default:
            printf("Choix invalide.\n");
            free(nouvelHoraire);
            return employe;
    }

    nouvelHoraire->suivant = NULL;

    if (employe->horair == NULL) {
        employe->horair = nouvelHoraire;
    } else {
        Horaire *p = employe->horair;
        while (p->suivant != NULL) {
            p = p->suivant;
        }
        p->suivant = nouvelHoraire;
    }
    printf("Horaire ajouté avec succès.\n");
    return employe;
}

void stat_conj_etJferier(Employee *employee) {
    Employee *p = employee;
    int i = 1;

    while (p != NULL) {
        printf("Entrez le status du jour férié : %s\n", p->horair->type);
        scanf("%s", p->horair->status);
        printf("Congé de l'employé n:%d\n", i);
        printf("Nom: %s\nPrénom: %s\nMotif: %s\n", p->nom, p->prenom, p->horair->motif);
        printf("Saisir le statut du congé: ");
        scanf("%s", p->horair->status);
        p = p->suivant;
    }
}

void affichage_joursferier_etcong_approuve(Employee *emp) {
    Employee *p = emp;

    printf("Liste des Jours Fériés et Congés Approuvés :\n");
    printf("┌────────────┬──────────┬────────────────┬────────────┐\n");
    printf("│ Date       │ Type     │ Description    │ Statut     │\n");
    printf("├────────────┼──────────┼────────────────┼────────────┤\n");
    while (p != NULL) {
        Horaire *h = p->horair;
        while (h != NULL) {
            if (strcmp(h->status, "approuve") == 0) {
                printf("│ %02d/%02d/%d │ %-8s │ %-14s │ %-10s │\n",
                       h->j_ferier.j, h->j_ferier.m, h->j_ferier.a,
                       h->type, h->desc, h->status);
            }
            h = h->suivant;
        }
        p = p->suivant;
    }
    printf("└────────────┴──────────┴────────────────┴────────────┘\n");
}

void affich_autre_status(Employee *emp) {
    Employee *p = emp;

    printf("Demandes de Congés en attente ou rejetées :\n");
    printf("┌────────────┬──────────┬─────────┬────────────┬───────────┐\n");
    printf("│ Employé    │ Date     │ Date Fin│ Motif      │ Statut    │\n");
    printf("├────────────┼──────────┼─────────┼────────────┼───────────┤\n");
    while (p != NULL) {
        Horaire *h = p->horair;
        while (h != NULL) {
            if (strcmp(h->status, "approuve") != 0) {
                printf("│ %-10s │ %02d/%02d/%d │ %02d/%02d/%d │ %-10s │ %-9s │\n",
                       p->nom, h->j_cong.j, h->j_cong.m, h->j_cong.a,
                       h->fin_j_cong.j, h->fin_j_cong.m, h->fin_j_cong.a,
                       h->motif, h->status);
            }
            h = h->suivant;
        }
        p = p->suivant;
    }
    printf("└────────────┴──────────┴─────────┴────────────┴───────────┘\n");
}

void affich_horaire(Employee *emp) {
    Employee *p = emp;

    printf("Planning des Horaires de Travail :\n");
    printf("┌────────────┬──────────┬───────────────────┬───────┐\n");
    printf("│ Employé    │ Date     │ Horaire de Travail│ Motif │\n");
    printf("├────────────┼──────────┼───────────────────┼───────┤\n");
    while (p != NULL) {
        Horaire *h = p->horair;
        while (h != NULL) {
            if (strcmp(h->status, "approuve") == 0) {
                printf("│ %-10s │ %02d/%02d/%d │ %02d:%02d             │ %-5s │\n",
                       p->nom, h->j_trav.j, h->j_trav.m, h->j_trav.a,
                       h->h_trav.h, h->min_trav.min, h->motif);
            }
            h = h->suivant;
        }
        p = p->suivant;
    }
    printf("└────────────┴──────────┴───────────────────┴───────┘\n");
}
void afficher_menu_horaire() {
    printf("\n=== MENU Gestion des Horaires ===\n");
    printf("1. Recherche et saisie d'horaire pour un profil\n");
    printf("2. Ajuster les horaires\n");
    printf("3. Statistiques sur les congés et jours fériés\n");
    printf("4. Afficher les jours fériés et congés approuvés\n");
    printf("5. Afficher les autres statuts de congé\n");
    printf("6. Afficher les horaires de travail\n");
    printf("77. Création liste de travail\n");
    printf("0. Quitter\n");
    printf("=================================\n");
}


int main() {
    Employee *liste = NULL;
    int choix;
    printf("------------------------------ MENU PRINCIPAL --------------------------\n");
        printf("1. Gestion des Profils Employes\n");
        printf("2. Gestion des horaires de travail\n");
        printf("3. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);
    do {
        printf("\nMENU\n");
        printf("1. Ajouter au debut\n");
        printf("2. Ajouter a la fin\n");
        printf("3. Ajouter apres un employe\n");
        printf("4. Supprimer au debut\n");
        printf("5. Supprimer a la fin\n");
        printf("6. Supprimer un employe\n");
        printf("7. Modifier le profil d'un employe\n");
        printf("8. Chercher par nom\n");
        printf("9. Chercher par telephone\n");
        printf("10. Chercher par adresse\n");
        printf("11. Chercher par email\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                liste = ajout_debut(liste);
                break;
            case 2:
                liste = ajout_fin(liste);
                break;
            case 3:
                liste = ajout_apres_un_employee(liste);
                break;
            case 4:
                liste = SuppDeb(liste);
                break;
            case 5:
                liste = SuppFin(liste);
                break;
            case 6: {
                char nom[20], prenom[20];
                printf("Donner le nom et le prenom de l'employe a supprimer: ");
                scanf("%s %s", nom, prenom);
                liste = SuppPos(liste, nom, prenom);
                break;
            }
            case 7:
                modification_profile_employes(liste);
                break;
            case 8:
                cherche_par_nom(liste);
                break;
            case 9:
                cherche_par_telephone(liste);
                break;
            case 10:
                cherche_par_adresse(liste);
                break;
            case 11:
                cherche_par_email(liste);
                break;
            case 0:
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
      } while (choix != 0);

      do {
        afficher_menu_horaire();
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        switch (choix) {

            case 77:liste->horair=creation_liste_trav(liste->horair);
                break;

            case 1:
                liste = Recherche_et_saisie_horaire_de_profil(liste);
                break;
            case 2:
                liste = ajuster_horaires(liste);
                break;
            case 3:
                stat_conj_etJferier(liste);
                break;
            case 4:
                affichage_joursferier_etcong_approuve(liste);
                break;
            case 5:
                affich_autre_status(liste);
                break;
            case 6:
                affich_horaire(liste);
                break;
            case 0:
                printf("Programme terminé.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choix != 0);

    // Libérer la mémoire utilisée par les employés et les horaires avant de quitter le programme

    return 0;
}

