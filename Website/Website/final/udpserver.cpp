#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>

using namespace std;

int main()
{
    int udpSocket;
    //char buffer[1000]={0};
    char packet[1024];
    struct sockaddr_in ServerAddr, ClientAddr;
    socklen_t client_len = sizeof(ClientAddr);

    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

    if(udpSocket < 0) {
        cerr << "Socket creation failed." << endl;
        return 1;
    }

    memset(&ServerAddr, 0, sizeof(ServerAddr));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(12345);
    ServerAddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(udpSocket, (sockaddr*)&ServerAddr, sizeof(ServerAddr)) < 0) {
        cerr << "Bind failed." << endl;
        return 1;
    }

    cout << "Server running... Waiting for data. \n";

    char filename[256] = {0};
    ssize_t nBytes = recvfrom(udpSocket, filename, sizeof(filename), 0, (sockaddr*)&ClientAddr, &client_len);
    filename[nBytes] = '\0';

    ofstream outfile("output.txt", ios::binary);

    if(!outfile.is_open()) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    while(true)
    {
        nBytes = recvfrom(udpSocket, packet, sizeof(packet), 0, (sockaddr*)&ClientAddr, &client_len);
        
        if(nBytes <= 0) {
            cerr << "Error receiving data." << endl;
            break;
        }

        char packetType[5] = {0};
        memcpy(packetType, packet, 4);

        cout << "Received " << packetType << endl;
        
        if(nBytes >= 4 && strncmp(packetType, "Data", 4) == 0) {
            outfile.write(packet + 4, nBytes -4);
            sendto(udpSocket, "Data", 4, 0, (sockaddr*)&ClientAddr, client_len);
        } else if(nBytes >= 4 && strncmp(packetType, "Done", 4) == 0) {
            sendto(udpSocket, "Done", 4, 0, (sockaddr*)&ClientAddr, client_len);
            cout << "File transfer complete.\n";
            break;
        }
    }

    outfile.close();
    close(udpSocket);
    return 0;
}
