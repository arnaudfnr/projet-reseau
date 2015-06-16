#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <crypt.h>
char *crypt(const char *key, const char *salt);

void generate_md5_salt(char buf[13])
{
int i;
//on initialse le générateur de nombre aléatoire
srand(time(NULL));
//un salt pour MD5 a le format : $1$<chaine de 8 caractères>$
//les huits caractères sont à choisir parmi [a-zA-Z0-9./]
buf[0]='$';
buf[1]='1';
buf[2]='$';
for (i=3; i < 11;i++)
{
do{
buf[i]=rand() % 128;
}while(
   (buf[i] < 'a' || buf[i] > 'z') 
&& (buf[i] < 'A' || buf[i] > 'Z') 
&& (buf[i] < '0' || buf[i] > '9')
&& (buf[i] != '.')
&& (buf[i] != '/')
);
}
buf[11]='$';
buf[12]='\0';
}

int main()
{
	char pass[256];
	printf("\nRentrez votre mot de passe : ");
	fflush(stdin);
	scanf("%s", pass);
	
	FILE *ptr; 
	ptr=fopen("tmp","w");
	char salt[13];
	generate_md5_salt(salt);
	fprintf(ptr, "%s", crypt(pass, salt));
	
	return 0;
}
