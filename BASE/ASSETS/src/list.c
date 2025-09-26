#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;

    printf("Content-type:text/html; Charset=Utf8\n\n");
	
	const char *host = "localhost", *user = "root", *password = "", *dataBase = "musculation";
	int taille;
	
	char *query_array;
	printf("<!DOCTYPE html>\
<html>\
<head>\
	<title>617- LIST</title>\
	<meta charset='utf-8'>\
	<link rel='stylesheet' type='text/css' href='BASE/ASSETS/CSS/style.css'>\
	<link rel='shortcut icon' href='BASE/ASSETS/img/logo/favicon.ico' type='image/x-icon'>\
	<link rel='stylesheet' href='BASE/ASSETS/css/tableau.css'>\
	<link rel='stylesheet' href='BASE/ASSETS/css/fontawesome.css'>\
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
		<div class='container'>\
			<table id='dataTable'>\
				<tr>\
					<td>code</td>\
					<td>nom</td>\
					<td>tel</td>\
					<td>ville</td>\
					<td>adresse</td>\
				</tr>");
				
		con = mysql_init(NULL);
        if(!con)
        {
            printf("<script type='text/javascript'>alert('FAILURE INITIALISATION')</script>");
            return 0;
        } else {
            con = mysql_real_connect(con,host,user,password,dataBase,3306,NULL,0);
            taille = sizeof("SELECT * FROM tclient");
            query_array = malloc(taille + 1);
            sprintf(query_array, "SELECT * FROM tclient");
            mysql_query(con, query_array);
            if (!mysql_query(con, query_array))
            {
                printf("<script type='text/javascript'>alert('FAILURE TRANSACTION')</script>; ");
                return 0;
            } else {
                res = mysql_use_result(con);
                while(row= mysql_fetch_row(res))
                {	
	                	printf("<tr class='row'>\
	                    <td>%s</td>\
	                    <td>%s</td>\
	                    <td>%s</td>\
	                    <td>%s</td>\
	                    <td>%s</td>\
	               		</tr>", row[0], row[1], row[2], row[3], row[4]);
                }
        printf("</table>\
		</div>\
	</div>\
	<script src='BASE/ASSETS/js/scripts.js''></script>\
</html>");
    }
	}
	free(query_array);
	mysql_close(con);
	return 0;
}