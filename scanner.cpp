#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <string>

bool check_port(const std::string& ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &target.sin_addr);
    
    int result = connect(sock, (struct sockaddr*)&target, sizeof(target));
    
    close(sock);
    
    return result == 0;
}

int main() {
    std::string target_ip;
    
    std::cout << "Введите IP адрес для сканирования: ";
    std::cin >> target_ip;
    
    // Список популярных портов и их названий
    std::vector<std::pair<int, std::string>> popular_ports = {
        {21, "FTP"},
        {22, "SSH"},
        {23, "Telnet"},
        {25, "SMTP"},
        {53, "DNS"},
        {80, "HTTP"},
        {110, "POP3"},
        {143, "IMAP"},
        {443, "HTTPS"},
        {445, "SMB"},
        {3306, "MySQL"},
        {3389, "RDP"},
        {5432, "PostgreSQL"},
        {8080, "HTTP-Alt"}
    };
    
    std::cout << "\nСканирую " << target_ip << " (популярные порты)..." << std::endl;
    
    int found = 0;
    
    for (const auto& port_info : popular_ports) {
        int port = port_info.first;
        std::string service = port_info.second;
        
        if (check_port(target_ip, port)) {
            std::cout << "Порт " << port << " (" << service << ") ОТКРЫТ!" << std::endl;
            found++;
        }
    }
    
    std::cout << "\nВсего открыто портов: " << found << std::endl;
    
    return 0;
}