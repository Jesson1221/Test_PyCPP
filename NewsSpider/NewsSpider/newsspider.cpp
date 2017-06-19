#include "newsspider.h"
#include "QFile"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTextStream>

NewsSpider::NewsSpider(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	// 设置显示3个页块
	m_blockSize = 3;

	// 设置当前页为第一页
	m_cur_page = 1;

	initialize();

	connect(action_copy, SIGNAL(triggered()), this, SLOT(copyChoosedContent()));
}

NewsSpider::~NewsSpider()
{

}

void NewsSpider::initialize()
{
	// 初始化新闻窗口界面: 3列 15行
	ui.newsTableWidget->setColumnCount(3);
	ui.newsTableWidget->setRowCount(NEWS_COUNT_PER_PAGE);

	// 设置第一列宽
	ui.newsTableWidget->setColumnWidth(0,300);  
	ui.newsTableWidget->setColumnWidth(1,150); 
	ui.newsTableWidget->setColumnWidth(2,300); 

	// 设置列标题
	QStringList headers;
	headers << "标题" << "时间" << "链接";
	ui.newsTableWidget->setHorizontalHeaderLabels(headers);

	// 设置新闻信息不可编辑
	ui.newsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	// 设置标题栏显示为粗体
	QFont font;
	font.setBold(true);
	ui.newsTableWidget->horizontalHeader()->setFont(font);

	// 初始化右键菜单
	popMenu = new QMenu(ui.newsTableWidget);
	action_copy = new QAction("复制", this);

	ui.pageLineEdit->installEventFilter(this);
	ui.pageLineEdit->setValidator(new QIntValidator(1, 10000000, this));

	ui.nextPageLable->setProperty("page", "true");
	ui.previousPageLable->setProperty("page", "true");
	ui.nextPageLable->installEventFilter(this);
	ui.previousPageLable->installEventFilter(this);

	pageLabels = new QList<QLabel *>();

	QHBoxLayout *leftLayout = new QHBoxLayout();
	QHBoxLayout *centerLayout = new QHBoxLayout();
	QHBoxLayout *rightLayout = new QHBoxLayout();
	leftLayout->setContentsMargins(0, 0, 0, 0);
	leftLayout->setSpacing(0);
	centerLayout->setContentsMargins(0, 0, 0, 0);
	centerLayout->setSpacing(0);
	rightLayout->setContentsMargins(0, 0, 0, 0);
	rightLayout->setSpacing(0);

	// 读取新闻，获取总条数
	readNews("news.txt");

	m_max_page = m_map_news.size() / NEWS_COUNT_PER_PAGE;
	if (0 != m_map_news.size() % NEWS_COUNT_PER_PAGE)
	{
		++m_max_page;
	}

	if (m_max_page <= m_blockSize * 3)
	{
		// 隐藏..符号
		ui.leftSeparateLable->hide();
		ui.rightSeparateLable->hide();
	}

	for (int i = 0; i < m_max_page; ++i) 
	{
		QLabel *label = new QLabel(QString::number(i + 1));
		label->setProperty("page", "true");
		label->installEventFilter(this);
		pageLabels->append(label);

		if (i < m_blockSize) 
		{
			leftLayout->addWidget(label);
		} 
		else if (i > (m_max_page / m_blockSize + m_blockSize) && i < (m_max_page / m_blockSize + m_blockSize * 2) + 1)
		{
			centerLayout->addWidget(label);
		} 
		else if (i > (m_max_page - m_blockSize))
		{
			rightLayout->addWidget(label);
		}
	}

	ui.leftPagesWidget->setLayout(leftLayout);
	ui.centerPagesWidget->setLayout(centerLayout);
	ui.rightPagesWidget->setLayout(rightLayout);

	//显示初始页面及新闻
	showPageLabels();
}

void NewsSpider::cutomContextMenuRequest(QPoint pos)
{
	popMenu->addAction(action_copy);
	popMenu->exec(QCursor::pos());
}

void NewsSpider::copyChoosedContent()
{

}

bool NewsSpider::readNews(const QString& filePath)
{
	QFile newsFile(filePath);
	if (!newsFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(this,"sdf","can't open file",QMessageBox::Yes);
		return false;
	}

	int iCount = 0;
	QTextStream fileContent(&newsFile);
	while(!fileContent.atEnd())
	{
		// 循环读取文件内容
		QString lineContent = fileContent.readLine();
		m_map_news.insert(iCount, lineContent);
		++iCount;
	}

	return true;
}

//************************************
// Method:    用于更新新闻页面及当前页号
// FullName:  NewsSpider::showPageLabels
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void NewsSpider::showPageLabels() 
{
	// 显示当前页号
	showPageNum();

	// 显示当前页新闻
	showCurPageNews();

}

//************************************
// Method:    用于更新页号更新
// FullName:  NewsSpider::showPageNum
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void NewsSpider::showPageNum() 
{
	if ( m_max_page <= m_blockSize * 3)
	{
		// 隐藏..符号
		ui.leftSeparateLable->hide();
		ui.rightSeparateLable->hide();

		for (int i = 0; i < m_max_page; i++)
		{
			QLabel *label = pageLabels->at(i);

			label->setText(QString::number(i + 1));
			label->show();

			if (m_cur_page - 1 == i)
			{
				label->setProperty("currentPage", "true");
			} 
			else 
			{
				label->setProperty("currentPage", "false");
			}

			label->setStyleSheet("/**/");
		}

		return;
	}

	// 以下情况为maxPageNumber大于blockSize * 3, 所有的页码label都要显示
	// c 为 currentPage
	// n 为 block size
	// m 为 maxPage

	// 1. c ∈ [1, n + n/2 + 1]: 显示前 n * 2 个, 后 n 个: 只显示右边的分隔符
	// 2. c ∈ [m - n - n/2, m]: 显示前 n 个, 后 n * 2 个: 只显示左边的分隔符
	// 3. 显示[1, n], [c - n/2, c + n/2], [m - 2*n + 1, m]: 两个分隔符都显示

	int c = m_cur_page;
	int n = m_blockSize;
	int m = m_max_page;
	int centerStartPage = 0;

	if (c >= 1 && c <= n + n / 2 + 1)
	{
		// 1. c ∈ [1, n + n/2 + 1]: 显示前 n * 2 个, 后 n 个: 只显示右边的分隔符
		centerStartPage = n + 1;
		ui.rightSeparateLable->show();
	}
	else if (c >= m - n - n / 2 && c <= m) 
	{
		// 2. c ∈ [m - n - n/2, m]: 显示前 n 个, 后 n * 2 个: 只显示左边的分隔符
		centerStartPage = m - n - n + 1;
		ui.leftSeparateLable->show();
	}
	else
	{
		// 3. 显示[1, n], [c - n/2, c + n/2], [m - n + 1, m]: 两个分隔符都显示
		centerStartPage = c - n / 2;
		ui.rightSeparateLable->show();
		ui.leftSeparateLable->show();
	}

	for(int i = 0; i < n; ++i)
	{
		// 前面 n 个
		pageLabels->at(i)->setText(QString::number(i + 1));         

		// 中间 n 个
		pageLabels->at(n + i)->setText(QString::number(centerStartPage + i));   

		// 后面 n 个
		pageLabels->at(3 * n - i - 1)->setText(QString::number(m - i));         
	}

	for (int i = 0; i < m_max_page; ++i) 
	{
		QLabel *label = pageLabels->at(i);
		int page = label->text().toInt();
		if (page == m_cur_page) 
		{
			label->setProperty("currentPage", "true");
		} 
		else
		{
			label->setProperty("currentPage", "false");
		}

		label->setStyleSheet("/**/");
		label->show();
	}

	emit currentPageChanged(m_cur_page);
}

void NewsSpider::showCurPageNews()
{
	// 清空当前新闻显示框
	ui.newsTableWidget->clear();

	int iStartNum = (m_cur_page - 1) * NEWS_COUNT_PER_PAGE;
	int iEndNum = iStartNum + NEWS_COUNT_PER_PAGE;

	// 如果当前页已经是最后一页，并且不足20条新闻，则取最大数
	if (iEndNum > m_map_news.size())
	{
		iEndNum = m_map_news.size();
	}

	// 显示当前页新闻
	for (int i = iStartNum; i < iEndNum; ++i)
	{
		// 新闻标题格式为： 标题;时间;链接
		QStringList strlist = m_map_news[i].split(";");

		// 标题
		QString title = strlist[0];
		ui.newsTableWidget->setItem(i, 0, new QTableWidgetItem(title));

		// 时间
		QString time = strlist[1];
		ui.newsTableWidget->setItem(i, 1, new QTableWidgetItem(time));

		// 链接
		QString url = strlist[2];
		ui.newsTableWidget->setItem(i, 2, new QTableWidgetItem(url));	
	}
}

bool NewsSpider::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonRelease)
	{
		int page_temp = -1;
		
		// 点击上一页、下一页 
		if (watched == ui.previousPageLable)
		{
			page_temp = getCurrentPage() - 1;
		}
		else if(watched == ui.nextPageLable)
		{
			page_temp = getCurrentPage() + 1;
		}

		// 点击具体页号
		for (int i = 0; i < pageLabels->size(); ++i)
		{
			if (watched == pageLabels->at(i))
			{
				page_temp = pageLabels->at(i)->text().toInt();
				break;
			}
		}

		// 如果为有效页，则设置当前页号
		if (page_temp > 0 && page_temp <= m_max_page)
		{
			setCurrentPage(page_temp);

			// 更新当前页面
			showPageLabels();
		}

		return true;
	}

	// 通过编辑框输入的页号
	if (watched == ui.pageLineEdit && event->type() == QEvent::KeyRelease)
	{
		QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
		if (key_event->key() == Qt::Key_Enter || key_event->key() == Qt::Key_Return)
		{
			// 如果输入为有效页号，则设置为当前页
			int a = ui.pageLineEdit->text().toInt();
			int b = pageLabels->count();
			if (0 < ui.pageLineEdit->text().toInt() && ui.pageLineEdit->text().toInt() <= pageLabels->count())
			{
				// 设置当前页号
				setCurrentPage(ui.pageLineEdit->text().toInt());

				// 更新当前页面
				showPageLabels();
				return true;
			}
			else
			{
				QMessageBox::warning(this,"sdf","It's not a valid page number",QMessageBox::Yes);
				return false;
			}
		}
	}

	return QMainWindow::eventFilter(watched, event);
}
