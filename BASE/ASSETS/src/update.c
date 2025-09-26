#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	printf("Content-type:text/html; charset=utf-8\n\n");
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;

	int taille;
	char *code, *nom, *tel, *ville, *adresse, data[100];
    char *token, *genre;
	char *query_array;

	con = mysql_init(NULL);	
	const char *host = "localhost", *user = "root", *password = "", *dataBase = "musculation";
	
	printf("<!DOCTYPE html>\
<html>\
<head>\
	<title>617- MODIFICATION</title>\
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
			<p>&copy Copyright</p>\
		</div>\
		<div class='container container-form'>\
			<h1>UPDATE CLIENT</h1>\
			<form id='formulaire' method='post'>\
				<input type='number' placeholder='CODE' id='code' readonly name='code'>\
				<input type='text' placeholder='NAME' id='nom' required name='nom'>\
				<input type='text' placeholder='TEL' id='tel' required name='tel'>\
				<input type='text' placeholder='VILLE' id='ville' required name='ville'>\
				<input type='text' placeholder='ADRESSE' id='adresse' required name='adresse'>\
				<input type='submit' value='MODIFY' class='submit' name='modify'>\
				<input type='submit' value='DELETE' class='reset' name='del' style='visibility: hidden;'>\
			</form>");
			fscanf(stdin, "%s", &data);
			token = strtok(data, "=");
			token = strtok(NULL, "&");
			
			code = token;
			
			token = strtok(NULL,"=");
			token = strtok(NULL,"&");
			
			nom = token;
			
			token = strtok(NULL,"=");
			token = strtok(NULL,"&");
			
			tel = token;
			
			token = strtok(NULL,"=");
			token = strtok(NULL,"&");
			
			ville = token;
		
			token = strtok(NULL,"=");
			token = strtok(NULL,"&");
			
			adresse = token;
			
			if(con == NULL)
		    {
		    	printf("<script type='text/javascript'>alert('Connection failed')</script>");
				return 1;
		    }
			if(mysql_real_connect(con,host,user,password,dataBase,3306,NULL,0) == NULL)	{
				printf("<script type='text/javascript'>alert('Connection failed')</script>");
				mysql_close(con);
				return 1;
			}	
			
		    taille = sizeof("UPDATE tclient SET NOM_C = '', TEL_C = '', VILLE_C = '', ADRESSE_C = '' WHERE CODE_C =  ;") + 30 + 12 + 20 + 20;
		    query_array = malloc(taille + 1);
		    
		  
//			sprintf(query_array, "DELETE FROM tclient  WHERE CODE_C = %s ;", code);
			
			sprintf(query_array, "UPDATE tclient SET NOM_C = '%s', TEL_C = '%s', VILLE_C = '%s', ADRESSE_C = '%s' WHERE CODE_C = %s ;", nom, tel, ville, adresse, code);
		    
	    	
	    
			mysql_query(con, query_array);
		    if(mysql_query(con, query_array) != 0 ){
				printf("<script type='text/javascript'>alert('Erreur d' Ajout);</script>");
				free(query_array);
				mysql_close(con);
				return 1;
			}	

	printf("</div>\
	</div>\
	<script src='BASE/ASSETS/js/actions.js'></script>\
</html>");
	free(query_array);
	mysql_close(con);
	return 0;
}