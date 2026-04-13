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
    char buffer[1000];
    char packet[1024];
    string filename;
    char ip[64];
    char port[16];

    struct sockaddr_in ServerAddr, ClientAddr;
    socklen_t addr_size = sizeof(ServerAddr);

    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (udpSocket < 0) {
        cerr << "Socket creation failed. \n";
        return 1;
    }

    memset(&ClientAddr, 0, sizeof(ClientAddr));

    ClientAddr.sin_family = AF_INET;
    ClientAddr.sin_port = htons(0);
    ClientAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(udpSocket,  (sockaddr*)&ClientAddr, sizeof(ClientAddr)) < 0) {
        cerr << "Bind failed. \n";
        return 1;
    }
    //cout << "Client bound to port 12345. \n";

    cout << "Please enter server IP: ";
    cin >> ip;

    cout << "Please enter your server port: ";
    cin >> port;

    cout << "Please enter the filename: ";
    cin >> filename;

    memset(&ServerAddr, 0, sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(atoi(port));
    ServerAddr.sin_addr.s_addr=inet_addr(ip);

    ifstream infile(filename, ios::binary);

    if (!infile.is_open()) {
        cerr << "Could not open file. \n";
        return 1;
    }

    sendto(udpSocket, filename.c_str(), filename.size(), 0, (sockaddr*)&ServerAddr, addr_size);

    while (!infile.eof()) {
        infile.read(buffer, sizeof(buffer));
        size_t bytesRead = infile.gcount();

        if (bytesRead > 0) {
            memcpy(packet, "Data", 4);
            memcpy(packet + 4, buffer, bytesRead);
            sendto(udpSocket, packet, bytesRead + 4, 0, (sockaddr*)&ServerAddr, addr_size);

            cout << "Received " << (bytesRead + 4) << " bytes\n";

            char ack[5] = {0};
            recvfrom(udpSocket, ack, sizeof(ack), 0, nullptr, nullptr);
        }
    }

    memcpy(packet, "Done", 4);
    sendto(udpSocket, packet, 4, 0, (sockaddr*)&ServerAddr, addr_size);

    cout << "File sent successfully." << endl;
    infile.close();
    close(udpSocket);
    return 0;
}
