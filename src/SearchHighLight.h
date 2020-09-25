#ifndef SEARCHHIGHLIGHT_H
#define SEARCHHIGHLIGHT_H

#include <QSyntaxHighlighter>

class SearchHighLight : public QSyntaxHighlighter
{
    Q_OBJECT
    using BaseClass = QSyntaxHighlighter;
public:
    explicit SearchHighLight(QTextDocument* parent = nullptr);

    void searchText(const QString& text);

protected:
    virtual void highlightBlock(const QString &text) override;

    void prefixFunc(const QString& str, QVector<int> &z);

    QVector<int> KMPSearch(const QString &text, const QString &str);

private:
    QString m_highlightedString;
    QTextCharFormat m_format; // Text formatting, highlighting
};

#endif // SEARCHHIGHLIGHT_H
