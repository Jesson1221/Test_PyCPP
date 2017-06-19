#ifndef NEWSSPIDER_H
#define NEWSSPIDER_H

#include <QtGui/QMainWindow>
#include <QList>
#include "ui_mainwindow.h"
class PageWidget;

// ����ÿҳ��ʾ����������
#define NEWS_COUNT_PER_PAGE 15

class NewsSpider : public QMainWindow
{
	Q_OBJECT

public:
	NewsSpider(QWidget *parent = 0, Qt::WFlags flags = 0);
	~NewsSpider();

protected:
	virtual bool eventFilter(QObject *watched, QEvent *event);

private:
	void initialize();

	// ��ȡ����
	bool readNews(const QString& filePath);

	// ��������ҳ
	void showPageLabels();

	// ����ҳ����ʾ
	void showPageNum();

	// ������ʾ��ǰҳ
	void showCurPageNews();

	// ��ȡ��ǰҳ��
	inline int getCurrentPage() const
	{
		return m_cur_page;
	}

	// ���õ�ǰҳ��
	inline void setCurrentPage(const int curPage)
	{
		m_cur_page = curPage;
	}

private slots:
	void cutomContextMenuRequest(QPoint pos);
	void copyChoosedContent();

signals:
	void currentPageChanged(int page);

private:
	Ui::NewsSpiderClass ui;

	// ������ʾ��������Ҽ��˵�
	QMenu *popMenu;
	QAction *action_copy;

	PageWidget *pageWidget;
	QList<QLabel *> *pageLabels;
	int m_blockSize;
	QMap<int, QString> m_map_news;
	int m_cur_page;
	int m_max_page;
};

#endif // NEWSSPIDER_H
