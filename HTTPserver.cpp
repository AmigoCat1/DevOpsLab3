#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <errno.h>

#include "FuncCosh.h"
#include "calculateTime.h"
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

#define PORT 8081

void sendGETresponse(int fd, char strFilePath[], char strResponse[]);
void sendPUTresponse(int fd, char strFilePath[], char strBody[], char strResponse[]);
void sendHEADresponse(int fd, char strFilePath[], char strResponse[]);

char HTTP_200HEADER[] = "HTTP/1.1 200 Ok\r\n";
char HTTP_201HEADER[] = "HTTP/1.1 201 CREATED\r\n";
char HTTP_404HEADER[] = "HTTP/1.1 404 Not Found\r\n";
char HTTP_400HEADER[] = "HTTP/1.1 400 Bad request\r\n";

int CreateHTTPserver()
{
    int connectionSocket, clientSocket, pid; 
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((connectionSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket open failed\n");
        exit(EXIT_FAILURE);
    }

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(connectionSocket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("socket bind failed\n");
        close(connectionSocket);
        exit(EXIT_FAILURE);
    }

    if (listen(connectionSocket, 10) < 0)
    {
        perror("socket listen failed\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("\n+++++++ Waiting for a new connection ++++++++\n\n");

        if ((clientSocket = accept(connectionSocket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("Error accept()");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid < 0)
        {
            perror("Error on fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            char buffer[30000] = {0};
            char *ptrBuffer = &buffer[0];

            int iBytesRead = read(clientSocket, ptrBuffer, 30000);
            printf("\nClient message of %d bytes:\n%s\n", iBytesRead, buffer);

            if (iBytesRead == 0)
            {
                printf("Client closed connection prematurely\n");
                close(clientSocket);
                continue;
            }

            printf("\nParsing request...\n");

            char strHTTP_requestMethod[10] = {0};
            char *pch = strchr(ptrBuffer, ' ');
            strncpy(strHTTP_requestMethod, ptrBuffer, pch - ptrBuffer);
            printf("Client method: %s\n", strHTTP_requestMethod);

            ptrBuffer = pch + 1;

            char strHTTP_requestPath[200] = {0};
            pch = strchr(ptrBuffer, ' ');
            strncpy(strHTTP_requestPath, ptrBuffer, pch - ptrBuffer);
            printf("Client asked for path: %s\n", strHTTP_requestPath);

            char strHTTPreqExt[200] = {0};
            pch = strrchr(strHTTP_requestPath, '.');
            if (pch != NULL)
                strcpy(strHTTPreqExt, pch + 1);

            char strFilePath[500] = {0};
            char strResponse[500] = {0};

            if (!strcmp(strHTTP_requestMethod, "GET"))
            {
                if (!strcmp(strHTTP_requestPath, "/"))
                {
                    sprintf(strFilePath, "./index.html");
                    sprintf(strResponse, "%s%s", HTTP_200HEADER, "Content-Type: text/html\r\n");
                    sendGETresponse(clientSocket, strFilePath, strResponse);
                }
                else if (!strcmp(strHTTP_requestPath, "/compute"))
                {
                    int iMS = calculateTime();
                    char strTimeEllapsed[20];
                    sprintf(strTimeEllapsed, "%i", iMS);
                    sprintf(strResponse, "%sContent-type: text/html\r\nContent-Length: %ld\r\n\r\n", HTTP_200HEADER, strlen(strTimeEllapsed));

                    ssize_t bytes_written = write(clientSocket, strResponse, strlen(strResponse));
                    if (bytes_written == -1)
                    {
                        perror("Error writing response header to client socket");
                        close(clientSocket);
                        return 0;
                    }

                    printf("\nResponse: \n%s\n", strResponse);

                    bytes_written = write(clientSocket, strTimeEllapsed, strlen(strTimeEllapsed));
                    if (bytes_written == -1)
                    {
                        perror("Error writing time elapsed to client socket");
                        close(clientSocket);
                        return 0;
                    }

                    printf("%s\n", strTimeEllapsed);
                }
                else
                {
                    sprintf(strFilePath, ".%s", strHTTP_requestPath);
                    sprintf(strResponse, "%s%s", HTTP_200HEADER, "Content-Type: text/plain\r\n");
                    sendGETresponse(clientSocket, strFilePath, strResponse);
                }
            }
            else if (!strcmp(strHTTP_requestMethod, "PUT"))
            {
                ptrBuffer = strstr(buffer, "\r\n\r\n");
                ptrBuffer += 4;
                if (ptrBuffer)
                {
                    sprintf(strFilePath, ".%s", strHTTP_requestPath);
                    sprintf(strResponse, "%s", HTTP_201HEADER);
                    sendPUTresponse(clientSocket, strFilePath, ptrBuffer, strResponse);
                }
            }
            close(clientSocket);
            return 0;
        }
        else
        {
            printf(">>>>>>>> Forked a child with pid: %d <<<<<<<<<<\n", pid);
            close(clientSocket);
        }
    }

    close(connectionSocket);
    return 0;
}

void sendGETresponse(int fdSocket, char strFilePath[], char strResponse[])
{
    int fdFile = open(strFilePath, O_RDONLY);
    if (fdFile < 0)
    {
        perror("Error opening file");
        sprintf(strResponse, "%s%s", HTTP_404HEADER, "Content-Type: text/plain\r\n\r\nFile not found");
        ssize_t bytes_written = write(fdSocket, strResponse, strlen(strResponse));
        if (bytes_written == -1)
        {
            perror("Error writing response to client socket");
        }
        return;
    }

    struct stat stat_buf;
    fstat(fdFile, &stat_buf);
    int file_total_size = stat_buf.st_size;
    int block_size = stat_buf.st_blksize;

    sprintf(strResponse + strlen(strResponse), "Content-Length: %d\r\n\r\n", file_total_size);

    ssize_t bytes_written = write(fdSocket, strResponse, strlen(strResponse));
    if (bytes_written == -1)
    {
        perror("Error writing response header to client socket");
        close(fdFile);
        return;
    }

    while (file_total_size > 0)
    {
        int iToSend = (file_total_size < block_size) ? file_total_size : block_size;
        ssize_t sent = sendfile(fdSocket, fdFile, NULL, iToSend);
        if (sent == -1)
        {
            perror("Error sending file data to client");
            break;
        }
        file_total_size -= sent;
    }

    close(fdFile);
}

void sendPUTresponse(int fdSocket, char strFilePath[], char strBody[], char strResponse[])
{
    int fdFile = open(strFilePath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fdFile < 0)
    {
        sprintf(strResponse, "%s", HTTP_400HEADER);
        ssize_t bytes_written = write(fdSocket, strResponse, strlen(strResponse));
        if (bytes_written == -1)
        {
            perror("Error writing response to client socket");
        }
        return;
    }

    ssize_t bytes_written = write(fdSocket, strResponse, strlen(strResponse));
    if (bytes_written == -1)
    {
        perror("Error writing response header to client socket");
        close(fdFile);
        return;
    }

    bytes_written = write(fdFile, strBody, strlen(strBody));
    if (bytes_written == -1)
    {
        perror("Error writing body to file");
    }

    close(fdFile);
}

