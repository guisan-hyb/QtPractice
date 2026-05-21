#include "mysyntaxhighlighter.h"
#include <QTextCharFormat>
#include <QFont>
#include <QString>
#include <QRegularExpression>

MySyntaxHighlighter::MySyntaxHighlighter(QObject *parent) : QSyntaxHighlighter(parent) {}

MySyntaxHighlighter::~MySyntaxHighlighter()
{

}

void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat myFormat;
    myFormat.setFont(QFont("微软雅黑"));
    myFormat.setFontWeight(QFont::Bold);
    myFormat.setForeground(Qt::green);

    QString pattern = "\\bchar\\b";
    QRegularExpression express(pattern);

    int index = text.indexOf(express);
    while (index >= 0) { // 注意：索引0也是合法的，所以应该是 >= 0
        QRegularExpressionMatch match = express.match(text, index);
        int matchLen = match.capturedLength(); // 获取匹配长度

        setFormat(index, matchLen, myFormat); // 设置格式

        // 移动到下一个位置，防止死循环
        index = text.indexOf(express, index + matchLen);
    }
}