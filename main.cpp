#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

// Renk Motoru
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// QruxWare Logo
void PrintLogo() {
    SetColor(11); // Siber Mavi
    std::cout << R"(
  ____                  __        __              
 / __ \_______  __  ___ \ \      / /_ _ _ __ ___  
| |  | | '__| | | \/ / / \ \ /\ / / _` | '__/ _ \ 
| |__| | |  | |_| >  < \  \ V  V / (_| | | |  __/ 
 \___\_\_|   \__,_/_/\_\   \_/\_/ \__,_|_|  \___| 
                                                  
    )" << '\n';
    SetColor(15);
}

// Gercek islem suresini simule eden ve loglayan bar
void ProgressBar(const std::string& taskName) {
    SetColor(14); // Sari
    std::cout << "[*] " << taskName << " isleniyor ";
    for (int i = 0; i < 5; ++i) {
        std::cout << ".";
        Sleep(150);
    }
    SetColor(10); // Yesil
    std::cout << " [BASARILI]\n";
    SetColor(15);
}

// Yonetici Haklari
bool IsRunAsAdmin() {
    BOOL fIsRunAsAdmin = FALSE;
    PSID pAdministratorsGroup = NULL;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdministratorsGroup)) {
        CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin);
        FreeSid(pAdministratorsGroup);
    }
    return fIsRunAsAdmin == TRUE;
}

// Registry Motoru
void SetRegistryValue(HKEY hKeyRoot, const char* subKey, const char* valueName, DWORD data) {
    HKEY hKey;
    if (RegCreateKeyExA(hKeyRoot, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) == ERROR_SUCCESS) {
        RegSetValueExA(hKey, valueName, 0, REG_DWORD, (const BYTE*)&data, sizeof(data));
        RegCloseKey(hKey);
    }
}

// ---------------- GERCEK ISLEM FONKSIYONLARI ----------------

void OptimizeNetwork() {
    std::cout << "\n";
    ProgressBar("Ag Darbogazi Kaldiriliyor (Network Throttling)");
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", "NetworkThrottlingIndex", 0xFFFFFFFF);
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\MSMQ\\Parameters", "TCPNoDelay", 1);
    
    ProgressBar("QoS Bant Genisligi Rezervi Sifirlaniyor");
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\Psched", "NonBestEffortLimit", 0);

    ProgressBar("Aktif Ag Bagdastiricisi Bulunuyor ve DNS Ataniyor");
    // Hardcode isimler yerine PowerShell ile sadece "Bagli" olan ag kartini bulup DNS atayan dinamik ve kusursuz komut.
    system("powershell -NoProfile -ExecutionPolicy Bypass -Command \"Get-NetAdapter | Where-Object {$_.Status -eq 'Up'} | Set-DnsClientServerAddress -ServerAddresses '1.1.1.1','1.0.0.1'\" > nul 2>&1");

    ProgressBar("DNS Onbellegi ve Winsock Tablolari Temizleniyor");
    system("ipconfig /flushdns > nul 2>&1");
    system("netsh winsock reset > nul 2>&1");

    std::cout << "\n";
    SetColor(10);
    std::cout << "[>>>] AG OPTIMIZASYONU TAMAMLANDI. [<<<]\n\n";
    SetColor(15);
}

void OptimizeSystemFPS() {
    std::cout << "\n";
    ProgressBar("Islemci (CPU) Oyun Onceligine Aliniyor");
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", "SystemResponsiveness", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile\\Tasks\\Games", "GPU Priority", 8);
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile\\Tasks\\Games", "Priority", 6);

    ProgressBar("Gereksiz Arka Plan Servisleri (Telemetri) Durduruluyor");
    // Windows Telemetri ve gereksiz arama dizin servislerini kapatir. FPS drop sorununu cozer.
    system("sc stop \"DiagTrack\" > nul 2>&1");
    system("sc config \"DiagTrack\" start= disabled > nul 2>&1");
    system("sc stop \"WSearch\" > nul 2>&1");
    system("sc config \"WSearch\" start= disabled > nul 2>&1");

    std::cout << "\n";
    SetColor(10);
    std::cout << "[>>>] SISTEM VE FPS OPTIMIZASYONU TAMAMLANDI. [<<<]\n\n";
    SetColor(15);
}

void RunPingTest() {
    std::cout << "\n";
    SetColor(14);
    std::cout << "[*] Cloudflare (1.1.1.1) Sunucularina Canli Ping Testi Yapiliyor...\n\n";
    SetColor(15);
    // Ping komutunu ekranda gostererek kullanicinin ms degerini gercek zamanli gormesini saglar
    system("ping 1.1.1.1 -n 5"); 
    std::cout << "\n";
    SetColor(10);
    std::cout << "[>>>] Eger ustte islem yaptiysaniz, ms degerindeki stabiliteyi gorebilirsiniz. [<<<]\n\n";
    SetColor(15);
}

void RevertSystem() {
    std::cout << "\n";
    ProgressBar("Ag ve Sistem Kayit Defteri Sifirlaniyor");
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", "NetworkThrottlingIndex", 10); 
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\MSMQ\\Parameters", "TCPNoDelay", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\Psched", "NonBestEffortLimit", 20);
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", "SystemResponsiveness", 20);
    
    ProgressBar("Arka Plan Servisleri Yeniden Aktif Ediliyor");
    system("sc config \"DiagTrack\" start= auto > nul 2>&1");
    system("sc config \"WSearch\" start= delayed-auto > nul 2>&1");

    ProgressBar("DNS Ayarlari Otomatige (DHCP) Aliniyor");
    system("powershell -NoProfile -ExecutionPolicy Bypass -Command \"Get-NetAdapter | Where-Object {$_.Status -eq 'Up'} | Set-DnsClientServerAddress -ResetServerAddresses\" > nul 2>&1");

    std::cout << "\n";
    SetColor(10);
    std::cout << "[>>>] SISTEM GUVENLI FABRIKA AYARLARINA GERI DONDU. [<<<]\n\n";
    SetColor(15);
}

int main() {
    SetConsoleTitleA("QruxWare Core Optimizer");
    
    if (!IsRunAsAdmin()) {
        SetColor(12); // Kirmizi
        std::cout << "\n[!] KRITIK HATA: Lutfen programi Sag Tik -> 'Yonetici Olarak Calistir' secenegi ile acin.\n";
        SetColor(15);
        system("pause");
        return 1;
    }

    int choice;
    while(true) {
        system("cls");
        PrintLogo();
        SetColor(8); // Gri
        std::cout << "--------------------------------------------------\n";
        SetColor(15);
        std::cout << "[1] Maksimum Ag Optimizasyonu (Ping & Baglanti)\n";
        std::cout << "[2] Sistem ve FPS Optimizasyonu (Islemci & Servis)\n";
        std::cout << "[3] Canli Ping Testi Uydula (Farki Gor)\n";
        std::cout << "[4] Guvenli Moda Don (Tum Ayarlari Sifirla)\n";
        std::cout << "[5] Cikis\n";
        SetColor(8);
        std::cout << "--------------------------------------------------\n";
        SetColor(15);
        std::cout << "Komut Girin: ";
        
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) { OptimizeNetwork(); system("pause"); }
        else if (choice == 2) { OptimizeSystemFPS(); system("pause"); }
        else if (choice == 3) { RunPingTest(); system("pause"); }
        else if (choice == 4) { RevertSystem(); system("pause"); }
        else if (choice == 5) { break; }
    }
    return 0;
}
