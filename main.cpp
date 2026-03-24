#include <windows.h>
#include <iostream>

// Programın yönetici haklarıyla çalışıp çalışmadığını kontrol eden güvenlik önlemi
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

// Kayıt defterini güvenli bir şekilde değiştiren çekirdek fonksiyon
void SetRegistryValue(HKEY hKeyRoot, const char* subKey, const char* valueName, DWORD data) {
    HKEY hKey;
    if (RegOpenKeyExA(hKeyRoot, subKey, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        if (RegSetValueExA(hKey, valueName, 0, REG_DWORD, (const BYTE*)&data, sizeof(data)) == ERROR_SUCCESS) {
            std::cout << "[+] Basarili: " << valueName << " degeri guncellendi.\n";
        } else {
            std::cout << "[-] Hata: Deger atanamadi (" << valueName << ")\n";
        }
        RegCloseKey(hKey);
    } else {
        std::cout << "[-] Hata: Anahtar bulunamadi veya erisim reddedildi.\n";
    }
}

void OptimizeSystem() {
    std::cout << "\n--- Optimizasyon Basliyor ---\n";
    // Network Throttling Kapatma: Windows'un bant genişliği kısıtlamasını kaldırıp oyun paketlerine limitsiz geçiş sağlar.
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", "NetworkThrottlingIndex", 0xFFFFFFFF);
    
    // TCPNoDelay: Paketlerin biriktirilmeden anında gönderilmesini sağlar (MS düşüşü için kritik).
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\MSMQ\\Parameters", "TCPNoDelay", 1);
    
    std::cout << "\n[!] Optimizasyon tamamlandi. Sisteminizi yeniden baslatmaniz onerilir.\n";
}

void RevertSystem() {
    std::cout << "\n--- Varsayilana Donuluyor ---\n";
    // Windows varsayılan kısıtlama değerine (10) geri dönüş
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", "NetworkThrottlingIndex", 10); 
    SetRegistryValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\MSMQ\\Parameters", "TCPNoDelay", 0);
    std::cout << "\n[!] Windows varsayilan ayarlarina geri donuldu.\n";
}

int main() {
    system("color 0A"); // Terminali profesyonel yeşil/siyah hacker görünümüne alır
    
    if (!IsRunAsAdmin()) {
        std::cout << "[!] KRITIK HATA: Lutfen programi Sag Tik -> 'Yonetici Olarak Calistir' secenegi ile acin.\n";
        std::cout << "Ag ayarlari yonetici izni gerektirir.\n\n";
        system("pause");
        return 1;
    }

    int choice;
    std::cout << "=== QruxWare Network Optimizer ===\n";
    std::cout << "1. Sistemi Optimize Et (Oyun Gecikmesini Dusur)\n";
    std::cout << "2. Varsayilan Ayarlara Don (Degisiklikleri Geri Al)\n";
    std::cout << "3. Cikis\n";
    std::cout << "Seciminiz: ";
    std::cin >> choice;

    if (choice == 1) OptimizeSystem();
    else if (choice == 2) RevertSystem();
    
    std::cout << "\n";
    system("pause");
    return 0;
}
