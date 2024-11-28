#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")
using namespace std;

void SetConsoleOutputCP() {
    SetConsoleOutputCP(CP_UTF8);
}

void OpenWebsite(const string& url) {
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void DownloadFile(const string& url, const string& outputPath) {
    HRESULT result = URLDownloadToFileA(NULL, url.c_str(), outputPath.c_str(), 0, NULL);
    if (SUCCEEDED(result)) {
        cout << "Файл загружен: " << outputPath << endl;
    }
    else {
        cerr << "Ошибка загрузки файла: " << url << endl;
    }
}

void LaunchFile(const string& filePath) {
    ShellExecuteA(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOW);
}

int main() {
    SetConsoleOutputCP();
    setlocale(LC_ALL, "Russian");

    vector<string> fileUrls = {
        "https://www.7-zip.org/a/7z2408-x64.exe",
        "https://github.com/ShareX/ShareX/releases/download/v16.1.0/ShareX-16.1.0-setup.exe",
        "https://github.com/notepad-plus-plus/notepad-plus-plus/releases/download/v8.7.2/npp.8.7.2.Installer.exe",
        "https://github.com/benbuck/rbtray/releases/download/v4.14/x64.zip",
        "https://github.com/microsoft/PowerToys/releases/download/v0.86.0/PowerToysUserSetup-0.86.0-x64.exe",
        "https://github.com/TranslucentTB/TranslucentTB/releases/download/2024.1/TranslucentTB-portable-x64.zip",
        "https://ru.download.nvidia.com/nvapp/client/11.0.1.163/NVIDIA_app_v11.0.1.163.exe",
        "https://engine.steelseriescdn.com/SteelSeriesGG75.1.0Setup.exe",
        "https://github.com/Codeusa/Borderless-Gaming/releases/download/9.5.6/BorderlessGaming9.5.6_admin_setup.exe",
        "https://files.multimc.org/downloads/mmc-develop-win32.zip",
        "https://download.radmin-vpn.com/download/files/Radmin_VPN_1.4.4642.1.exe",
        "https://github.com/Windows200000/TwitchDropsMiner-updated/releases/download/v15.9.1/Twitch.Drops.Miner.Windows.zip",
        "https://github.com/windirstat/windirstat/releases/download/release%2Fv2.0.3/WinDirStat-x64.msi",
        "https://download01.logi.com/web/ftp/pub/techsupport/gaming/lghub_installer.exe",
        "https://vscode.download.prss.microsoft.com/dbazure/download/stable/f1a4fb101478ce6ec82fe9627c43efbf9e98c813/VSCodeUserSetup-x64-1.95.3.exe",
        "https://dl.ocbase.com/per/stable/OCCT.exe",
        "https://cdn.fastly.steamstatic.com/client/installer/SteamSetup.exe",
        "https://www.fosshub.com/qBittorrent.html",
        "https://dl.google.com/tag/s/appguid%3D%7B8A69D345-D564-463C-AFF1-A69D9E530F96%7D%26iid%3D%7BFD415EAD-8A45-A037-D5CB-E8CB4B8AA2A9%7D%26lang%3Dru%26browser%3D4%26usagestats%3D1%26appname%3DGoogle%2520Chrome%26needsadmin%3Dprefers%26ap%3Dx64-statsdef_1%26installdataindex%3Dempty/update2/installers/ChromeSetup.exe",
        "https://download.mozilla.org/?product=firefox-stub&os=win&lang=ru&attribution_code=c291cmNlPXd3dy5nb29nbGUuY29tJm1lZGl1bT1yZWZlcnJhbCZjYW1wYWlnbj0obm90IHNldCkmY29udGVudD0obm90IHNldCkmZXhwZXJpbWVudD0obm90IHNldCkmdmFyaWF0aW9uPShub3Qgc2V0KSZ1YT1jaHJvbWUmY2xpZW50X2lkX2dhND0xMzAxNTYzNzYwLjE3MzI4MjE3NDcmc2Vzc2lvbl9pZD03NDA1NjA5Nzg5JmRsc291cmNlPW1vem9yZw..&attribution_sig=53c5b8d75e5107175afc41c725dd3ab315e1a513d25dd8a74684a14f49b816f9&_gl=1*2icvem*_ga*MTMwMTU2Mzc2MC4xNzMyODIxNzQ3*_ga_MQ7767QQQW*MTczMjgyMTc0Ni4xLjEuMTczMjgyMTc1MC4wLjAuMA..",

    };

    vector<string> fileNames = {
        "7-zip",
        "ShareX",
        "Notepad++",
        "RBtray",
        "PowerToys",
        "TranslucentTB",
        "Nvidia app",
        "SteelSeries app",
        "Borderless-Gaming",
        "multimc",
        "RadminVPN",
        "TwitchDropsMiner",
        "WinDirStat",
        "Logitech G HUB",
        "Visual Studio Code",
        "OCCT",
        "Steam",
        "qbittorrent",
        "Google Chrome"
        "FireFox"
    };

    string downloadFolder;
    char* buffer = nullptr;
    size_t size;

    if (_dupenv_s(&buffer, &size, "USERPROFILE") == 0) {
        downloadFolder = string(buffer) + "\\Documents\\DownloadedFiles";
        free(buffer);
    }
    else {
        cerr << "Не удалось получить путь к папке пользователя." << endl;
        return 1;
    }

    CreateDirectoryA(downloadFolder.c_str(), NULL);

    cout << "Выберите программы для загрузки (введите номера через пробел):" << endl;
    for (size_t i = 0; i < fileNames.size(); ++i) {
        cout << i + 1 << ". " << fileNames[i] << endl;
    }

    string input;
    getline(cin, input);

    vector<int> selectedFiles;
    size_t pos = 0;
    while ((pos = input.find(' ')) != string::npos) {
        selectedFiles.push_back(stoi(input.substr(0, pos)) - 1);
        input.erase(0, pos + 1);
    }
    selectedFiles.push_back(stoi(input) - 1);

    for (int index : selectedFiles) {
        if (index >= 0 && index < fileUrls.size()) {
            string fileName = fileUrls[index].substr(fileUrls[index].find_last_of('/') + 1);
            string filePath = downloadFolder + "\\" + fileName;


            if (fileUrls[index].substr(fileUrls[index].find_last_of('.') + 1) == "exe" ||
                fileUrls[index].substr(fileUrls[index].find_last_of('.') + 1) == "zip") {
                DownloadFile(fileUrls[index], filePath);
                LaunchFile(filePath);
            }
            else {
                OpenWebsite(fileUrls[index]); 
            }
        }
        else {
            cerr << "Некорректный номер: " << index + 1 << endl;
        }
    }
    cout << "Нажмите Enter для выхода..." << endl;
    cin.get();
    return 0;
}