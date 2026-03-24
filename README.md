# Qrux-Network-Optimizera

Piyasada "Pinginizi 0'a indirir", "FPS'inizi 5 kat artırır" gibi asılsız vaatlerde bulunan kapalı kaynaklı ve ne yaptığı belirsiz yazılımlara karşı geliştirilmiş, **tamamen şeffaf ve açık kaynaklı** bir sistem & ağ optimizasyon aracıdır.

Bu araç sihir yapmaz. Sadece Windows işletim sisteminin varsayılan ağ kısıtlamalarını kaldırır, gereksiz arka plan servislerini durdurur ve donanım gücünüzü oyunlara odaklar. Ne eksik, ne fazla.

## ⚙️ Temel Özellikler

* **🌐 Maksimum Ağ Optimizasyonu:** Windows Network Throttling (Ağ Darboğazı) kısıtlamalarını kaldırır. QoS bant genişliği rezervini (%20) sıfırlar. PowerShell kullanarak aktif ağ bağdaştırıcınızı dinamik olarak tespit eder ve en düşük gecikmeli Cloudflare (1.1.1.1) DNS sunucularına yönlendirir.
* **⚡ Sistem ve FPS Optimizasyonu:** Arka planda işlemciyi ve diski yoran Windows Telemetri (`DiagTrack`) ve Arama Dizin (`WSearch`) servislerini durdurur. İşletim sisteminin donanım önceliğini (CPU/GPU) oyunlara tahsis eder.
* **📊 Gerçek Zamanlı Ping Testi:** Yaptığınız ağ optimizasyonunun işe yarayıp yaramadığını sistem içinden canlı olarak test edebilmenizi sağlayan şeffaf doğrulama modülü.
* **🛡️ %100 Geri Dönülebilirlik:** Programda yapılan tüm değişiklikler tek bir tuşla ("Güvenli Moda Dön") Windows'un varsayılan fabrika ayarlarına geri döndürülebilir. Sistemde kalıcı bir hasar veya geri alınamaz bir kayıt bırakmaz.

## 🚀 Nasıl Kullanılır?

Kod derlemekle uğraşmak istemeyen son kullanıcılar için:

1.  Bu sayfanın sağ tarafındaki **[Releases]** sekmesine tıklayın.
2.  En son sürüme ait `QruxOptimizer-Release.zip` dosyasını indirin ve klasöre çıkartın.
3.  `.exe` dosyasına sağ tıklayıp **"Yönetici Olarak Çalıştır"** seçeneğini seçin. *(Sistem çekirdeğine ve DNS ayarlarına müdahale edildiği için yönetici izni zorunludur).*
4.  Açılan menüden yapmak istediğiniz işlemi seçin ve arkanıza yaslanın.

## 👨‍💻 Geliştiriciler İçin (Şeffaflık Raporu)

Aracın arka planda ne yaptığını merak edenler `main.cpp` dosyasını inceleyebilir. Uygulamanın müdahale ettiği temel kayıt defteri (Registry) anahtarları şunlardır:
* `NetworkThrottlingIndex` -> `0xFFFFFFFF`
* `TCPNoDelay` -> `1`
* `SystemResponsiveness` -> `0`
* `GPU Priority` -> `8`
* `Priority` -> `6`

> **⚠️ SmartScreen Uyarısı Hakkında:**
> Bu proje bağımsız bir açık kaynak yazılımı olduğu ve ücretli bir dijital imza sertifikasına (Code Signing) sahip olmadığı için, Windows Defender veya SmartScreen indirirken "Bilinmeyen Yayıncı" uyarısı verebilir. Bu uyarıyı geçmek için **"Ek Bilgi" -> "Yine de Çalıştır"** diyebilirsiniz. Koda güvenmiyorsanız, projeyi indirip kendi derleyicinizle (g++) derlemekte özgürsünüz.

--- | Trust and Freedom.
