//
// Created by wrc on 22-12-6.
//
#include "utils.h"
#include <QMessageBox>
#include <QString>

bool dirExists(const std::string &folderpath) {
    if (access(folderpath.c_str(), 0)) {
        std::cout << "folder does not exist! Will create a new one!" << std::endl;
        return false;
    }
    return true;
}

size_t getFileSize(const char *fileName) {

    if (fileName == NULL) {
        return 0;
    }

    // 这是一个存储文件(夹)信息的结构体，其中有文件大小和创建时间、访问时间、修改时间等
    struct stat statbuf;

    // 提供文件名字符串，获得文件属性结构体
    stat(fileName, &statbuf);

    // 获取文件大小
    size_t filesize = statbuf.st_size;

    return filesize;
}

void setIconToLabel(QLabel *label, const QString &file) {
    auto label1_pix = QPixmap(file);
    label1_pix.scaled(label->size());
    label->setScaledContents(true);
    label->setPixmap(label1_pix);
}

void showMessageBox(QWidget *parent, const char *title) {
    QMessageBox::warning(parent, QStringLiteral("提示"), title, QMessageBox::Abort, QMessageBox::Abort);

}

pair<bool, string> showInputBox(QWidget *parent, const char *title, const char *label) {
    bool ok;

    QString text = QInputDialog::getText(parent, QString(title), QString(label), QLineEdit::Normal, 0, &ok);
    return make_pair(ok, text.toStdString());
}

vector<int> splitStringToInt(string s) {
    vector<int> res;
//    s.find(",");
    std::regex regex(",|，");  // 使用逗号或全角逗号作为分隔符
    std::sregex_token_iterator iter(s.begin(), s.end(), regex, -1);
    std::sregex_token_iterator end;
    while (iter != end) {
        float value = std::stof(iter->str());
        res.push_back(value);
        ++iter;
    }
    return res;
};

vector<float> splitStringToFloat(string s) {
    vector<float> res;
//    s.find(",");
    std::regex regex(",|，");  // 使用逗号或全角逗号作为分隔符
    std::sregex_token_iterator iter(s.begin(), s.end(), regex, -1);
    std::sregex_token_iterator end;
    while (iter != end) {
        float value = std::stof(iter->str());
        res.push_back(value);
        ++iter;
    }
    return res;
};