#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")
void SetConsoleOutputCP() {

    SetConsoleOutputCP(CP_UTF8);
}

void DownloadFile(const std::string& url, const std::string& outputPath) {
    HRESULT result = URLDownloadToFileA(NULL, url.c_str(), outputPath.c_str(), 0, NULL);
    if (SUCCEEDED(result)) {
        std::cout << "Файл загружен: " << outputPath << std::endl;
    }
    else {
        std::cerr << "Ошибка загрузки файла: " << url << std::endl;
    }
}

void LaunchFile(const std::string& filePath) {
    ShellExecuteA(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOW);
}

int main() {

    SetConsoleOutputCP();
    setlocale(LC_ALL, "Russian");


    std::vector<std::string> fileUrls = {
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
        "https://dl.ocbase.com/per/stable/OCCT.exe"
    };

    std::vector<std::string> fileNames = {
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
        "OCCT"
    };


    std::string downloadFolder;
    char* buffer = nullptr;
    size_t size;


    if (_dupenv_s(&buffer, &size, "USERPROFILE") == 0) {
        downloadFolder = std::string(buffer) + "\\Documents\\DownloadedFiles";
        free(buffer);
    }
    else {
        std::cerr << "Не удалось получить путь к папке пользователя." << std::endl;
        return 1;
    }

    CreateDirectoryA(downloadFolder.c_str(), NULL);

    std::cout << "Выберите программы для загрузки (введите номера через пробел):" << std::endl;
    for (size_t i = 0; i < fileNames.size(); ++i) {
        std::cout << i + 1 << ". " << fileNames[i] << std::endl;
    }

    std::string input;
    std::getline(std::cin, input);


    std::vector<int> selectedFiles;
    size_t pos = 0;
    while ((pos = input.find(' ')) != std::string::npos) {
        selectedFiles.push_back(std::stoi(input.substr(0, pos)) - 1);
        input.erase(0, pos + 1);
    }
    selectedFiles.push_back(std::stoi(input) - 1); 

    for (int index : selectedFiles) {
        if (index >= 0 && index < fileUrls.size()) {
            std::string fileName = fileUrls[index].substr(fileUrls[index].find_last_of('/') + 1);
            std::string filePath = downloadFolder + "\\" + fileName;


            DownloadFile(fileUrls[index], filePath);

            LaunchFile(filePath);
        }
        else {
            std::cerr << "Некорректный номер: " << index + 1 << std::endl;
        }
    }
    std::cout << "Нажмите Enter для выхода..." << std::endl;
    std::cin.get();
    return 0;
}