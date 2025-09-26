#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>


/* Fonction d'arrêt en cas d'erreur MySQL */
void finish_with_error(MYSQL *con) {
    printf("<script type='text/javascript'>alert('Erreur MySQL : %s');</script>", mysql_error(con));
    mysql_close(con);
    exit(1);        
}

int main(int argc, char *argv[]) {
    printf("Content-type:text/html; charset=utf-8\n\n");

    MYSQL *con;
   	MYSQL_RES *res;
	MYSQL_ROW row;

    con = mysql_init(NULL);	
    const char *host = "localhost", *user = "root", *password = "", *dataBase = "musculation";
    char *code = NULL, *nom = NULL, *tel = NULL, *ville = NULL, *adresse = NULL;
    char data[1000];  // Taille augmentée pour gérer les entrées plus grandes
    char *token;
    // En-tête HTML et formulaire
    printf("<!DOCTYPE html>\
<html>\
<head>\
    <title>617- REGISTRER</title>\
    <meta charset='utf-8'>\
    <link rel='stylesheet' type='text/css' href='BASE/ASSETS/CSS/style.css'>\
    <link rel='shortcut icon' href='BASE/ASSETS/img/logo/favicon.ico' type='image/x-icon'>\
    <link rel='stylesheet' href='BASE/ASSETS/css/fontawesome.css'>\
    <link rel='stylesheet' href='BASE/ASSETS/css/form.css'>\
    <link rel='stylesheet' href='BASE/ASSETS/css/all.css'>\
</head>\
<body>\
    <div class='header'>\
        <h1>\
            <span>617 </span>Gym\
        </h1>\
    </div>\
    <div class='main'>\
        <div class='nav'>\
            <ul>\
				<li><a href='index.exe'><i class='fas fa-home '></i> HOME</a></li>\
				<li><a href='new.exe'><i class='fas fa-plus '></i> NEW CLIENT</a></li>\
				<li><a href='list.exe'><i class='fas fa-list '></i> CLIENT LIST</a></li>\
				<li><a href='search.exe'><i class='fas fa-search '></i> SEARCH</a></li>\
			</ul>\
            <p>&copy; Copyright</p>\
        </div>\
        <div class='container container-form'>");
    printf("<h1>NEW CLIENT</h1>\
        <form action='' method='post'>\
            <input type='text' placeholder='NOM' id='nom' required name='nom' style='width: 36.8%;'>\
            <input type='text' placeholder='TÉL' id='tel' required name='tel'>\
            <input type='text' placeholder='VILLE' id='ville' required name='ville'>\
            <input type='text' placeholder='ADRESSE' id='adresse' required name='adresse'>\
            <input type='submit' value='ENREGISTRER' class='submit'>\
        </form>\
    </div>\
    </div>\
</body>\
</html>");

    

    if (fgets(data, sizeof(data), stdin) != NULL) {
        token = strtok(data, "&");
        while (token != NULL) {
            if (strncmp(token, "code=", 5) == 0) {
                code = token + 5;
            } else if (strncmp(token, "nom=", 4) == 0) {
                nom = token + 4;
            } else if (strncmp(token, "tel=", 4) == 0) {
                tel = token + 4;
            } else if (strncmp(token, "ville=", 6) == 0) {
                ville = token + 6;
            } else if (strncmp(token, "adresse=", 8) == 0) {
                adresse = token + 8;
            }
            token = strtok(NULL, "&");
        }
    }

    // Vérification des entrées
    if (nom == NULL || tel == NULL || ville == NULL || adresse == NULL) {
        return 1;
    }

    if(con == NULL) {
        printf("<script type='text/javascript'>alert('Échec de l'initialisation de MySQL');</script>");
        return 1;
    }

    if(mysql_real_connect(con, host, user, password, dataBase, 3306, NULL, 0) == NULL) {
        finish_with_error(con);
    }

    // Vérification de l'existence de l'utilisateur avant insertion
    char check_query[512];
    snprintf(check_query, sizeof(check_query), "SELECT COUNT(*) FROM tclient WHERE NOM_C='%s' AND TEL_C='%s' AND VILLE_C='%s' AND ADRESSE_C='%s'", nom, tel, ville, adresse);
    if (mysql_query(con, check_query)) {
        finish_with_error(con);
    }
    res = mysql_store_result(con);
    if (res == NULL) {
        finish_with_error(con);
    }

    row = mysql_fetch_row(res);
    int exists = atoi(row[0]);
    mysql_free_result(res);

    if (exists > 0) {
    } else {
        // Taille maximale de la requête d'insertion
        int taille = strlen("INSERT INTO tclient (NOM_C, TEL_C, VILLE_C, ADRESSE_C) VALUES ('','','','');") + 
                     strlen(nom) + strlen(tel) + strlen(ville) + strlen(adresse);

        char *query_array = malloc(taille + 1);

        if (query_array == NULL) {
            printf("<script type='text/javascript'>alert('Échec de l'allocation mémoire');</script>");
            mysql_close(con);
            return 1;
        }

        sprintf(query_array, "INSERT INTO tclient (NOM_C, TEL_C, VILLE_C, ADRESSE_C) VALUES ('%s', '%s', '%s', '%s');", 
                nom, tel, ville, adresse);

        if (mysql_query(con, query_array) != 0) {
            finish_with_error(con);
        }

        printf("<script type='text/javascript'>alert('Client enregistré avec succès');</script>");

        free(query_array);
    }

    mysql_close(con);
    return 0;
}
