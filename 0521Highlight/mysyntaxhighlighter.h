#ifndef MYSYNTAXHIGHLIGHTER_H
#define MYSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QObject>

class MySyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit MySyntaxHighlighter(QObject* parent = nullptr);
    ~MySyntaxHighlighter();
    //重新实现高亮
protected:
    virtual void highlightBlock(const QString& text);
};

#endif // MYSYNTAXHIGHLIGHTER_H
