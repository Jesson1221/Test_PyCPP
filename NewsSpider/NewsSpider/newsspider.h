#ifndef NEWSSPIDER_H
#define NEWSSPIDER_H

#include <QtGui/QMainWindow>
#include <QList>
#include "ui_mainwindow.h"
class PageWidget;

// 设置每页显示多少条新闻
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

	// 读取新闻
	bool readNews(const QString& filePath);

	// 更新新闻页
	void showPageLabels();

	// 更新页号显示
	void showPageNum();

	// 新闻显示当前页
	void showCurPageNews();

	// 获取当前页号
	inline int getCurrentPage() const
	{
		return m_cur_page;
	}

	// 设置当前页号
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

	// 新闻显示框中添加右键菜单
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
