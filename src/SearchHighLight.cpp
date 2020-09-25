#include <QTextCharFormat>

#include "SearchHighLight.h"

SearchHighLight::SearchHighLight(QTextDocument* parent) : BaseClass(parent)
{
    // Set the backlight color
    m_format.setBackground(Qt::green);
}

void SearchHighLight::highlightBlock(const QString& text)
{
    if(m_highlightedString.isEmpty()) {
        return;
    }

    const int LEN = m_highlightedString.length();
    for(auto index :KMPSearch(text, m_highlightedString)) {
        setFormat(index, LEN, m_format);
    }
}

void SearchHighLight::prefixFunc(const QString &str, QVector<int> &z)
{
    z.resize(str.size());
    z[0] = 0;
    for (int i=1;i<z.size();++i) {
        int pos = z[i-1];
        while (pos > 0 && str[pos] != str[i])
            pos = z[pos-1];
        z[i] = pos + (str[pos] == str[i] ? 1 : 0);
    }
}

QVector<int> SearchHighLight::KMPSearch(const QString &text, const QString &str)
{
    QVector<int> z;
    QVector<int> positions;
    prefixFunc(str, z);
    int pos = 0;
    for (int i=0; i<text.size(); ++i) {
        while (pos > 0 && (pos >= str.size() || str[pos] != text[i]) )
          pos = z[pos-1];
        if (text[i] == str[pos]) pos++;
        if (pos == str.size())
            positions.push_back(i - pos + 1);
    }
    return positions;
}

void SearchHighLight::searchText(const QString& text)
{
    // Set the text as a regular expression.
    m_highlightedString = text;
    rehighlight();
}
