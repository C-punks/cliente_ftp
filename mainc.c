#include "cliente.h"


int main (int argc, char **argv)
{
	int c,s,bytes,fd;
	char buf[BUF_SIZE];
	struct hostent *h;
	struct sockaddr_in dir_origen,dir_destino;
	char nombre_opcion[100];

	
	
	if (argc != 5)
	{
		fatal("Usar : cliente nombre-servidor puerto-servidor opcion nombre-archivo");
		
	}

	strcpy(nombre_opcion,argv[4]);
	strcat(nombre_opcion,":");
	strcat(nombre_opcion,argv[3]);

	 s = socket(PF_INET,SOCK_STREAM,0);

	if (s < 0 )
	{
		fatal("Socket");
	}

	dir_origen.sin_family = AF_INET;
	dir_origen.sin_port = htons(0);
	dir_origen.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s,(struct sockaddr*)&dir_origen,sizeof(dir_origen)) == 1)
	{
		fatal("Error en bind");
	}

	dir_destino.sin_family = AF_INET;
	dir_destino.sin_addr.s_addr = inet_addr(argv[1]);
	dir_destino.sin_port = htons(atoi(argv[2]));

	c = connect(s, (struct sockaddr *)&dir_destino,sizeof(dir_destino));

	if (c < 0)
	{
		fatal ("Falla en conexion");
	}

	write (s,nombre_opcion,strlen(nombre_opcion) +1 );
	if (strcmp(argv[3],"recibir")!=0 && strcmp(argv[3],"enviar")!=0)
	{
		close(s);
		fatal("la Opcion Ingresada no es valida !!\n Opcion : enviar , recibir\n");
	}
	
	if (strcmp(argv[3],"recibir")==0)
	{
		remove(argv[4]);
		read(s,buf,BUF_SIZE);

		if(strcmp(buf,"Error") == 0)
		{
			fatal("El Archivo no existe en el Servidor");
		}
		if(strcmp(buf,"Existe") == 0)
		{
			write(s,buf,BUF_SIZE);

			fd = open(argv[4],O_WRONLY |O_CREAT, S_IRUSR|S_IWUSR);

			while (1)
			{	
				bytes = read (s, buf,BUF_SIZE);
				if (bytes<=0)
				{
					exit(0);
				}
				write(fd,buf,bytes);
			}
			close(fd);	
		}
	}

	if (strcmp(argv[3],"enviar")==0)
	{

		read(s,buf,BUF_SIZE);

		printf("\n%s\n",buf);

		fd = open(argv[4], O_RDONLY);  

      		if (fd < 0) fatal("falla en open");
      		
      		memset( buf, '\0', sizeof(buf) );

      		while (1) {
				bytes = read(fd, buf, BUF_SIZE);
				if (bytes <= 0)
				{
					break;  
				}
				write(s, buf, bytes);
				memset( buf, '\0', sizeof(buf) );  
			}
			close(fd);  
			//read(s,buf,BUF_SIZE);
			//printf("\n%s\n",buf);
						
			close(s);
	}

	

	
}
