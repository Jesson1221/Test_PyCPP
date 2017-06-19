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

	// ������ʾ3��ҳ��
	m_blockSize = 3;

	// ���õ�ǰҳΪ��һҳ
	m_cur_page = 1;

	initialize();

	connect(action_copy, SIGNAL(triggered()), this, SLOT(copyChoosedContent()));
}

NewsSpider::~NewsSpider()
{

}

void NewsSpider::initialize()
{
	// ��ʼ�����Ŵ��ڽ���: 3�� 15��
	ui.newsTableWidget->setColumnCount(3);
	ui.newsTableWidget->setRowCount(NEWS_COUNT_PER_PAGE);

	// ���õ�һ�п�
	ui.newsTableWidget->setColumnWidth(0,300);  
	ui.newsTableWidget->setColumnWidth(1,150); 
	ui.newsTableWidget->setColumnWidth(2,300); 

	// �����б���
	QStringList headers;
	headers << "����" << "ʱ��" << "����";
	ui.newsTableWidget->setHorizontalHeaderLabels(headers);

	// ����������Ϣ���ɱ༭
	ui.newsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	// ���ñ�������ʾΪ����
	QFont font;
	font.setBold(true);
	ui.newsTableWidget->horizontalHeader()->setFont(font);

	// ��ʼ���Ҽ��˵�
	popMenu = new QMenu(ui.newsTableWidget);
	action_copy = new QAction("����", this);

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

	// ��ȡ���ţ���ȡ������
	readNews("news.txt");

	m_max_page = m_map_news.size() / NEWS_COUNT_PER_PAGE;
	if (0 != m_map_news.size() % NEWS_COUNT_PER_PAGE)
	{
		++m_max_page;
	}

	if (m_max_page <= m_blockSize * 3)
	{
		// ����..����
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

	//��ʾ��ʼҳ�漰����
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
		// ѭ����ȡ�ļ�����
		QString lineContent = fileContent.readLine();
		m_map_news.insert(iCount, lineContent);
		++iCount;
	}

	return true;
}

//************************************
// Method:    ���ڸ�������ҳ�漰��ǰҳ��
// FullName:  NewsSpider::showPageLabels
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void NewsSpider::showPageLabels() 
{
	// ��ʾ��ǰҳ��
	showPageNum();

	// ��ʾ��ǰҳ����
	showCurPageNews();

}

//************************************
// Method:    ���ڸ���ҳ�Ÿ���
// FullName:  NewsSpider::showPageNum
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void NewsSpider::showPageNum() 
{
	if ( m_max_page <= m_blockSize * 3)
	{
		// ����..����
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

	// �������ΪmaxPageNumber����blockSize * 3, ���е�ҳ��label��Ҫ��ʾ
	// c Ϊ currentPage
	// n Ϊ block size
	// m Ϊ maxPage

	// 1. c �� [1, n + n/2 + 1]: ��ʾǰ n * 2 ��, �� n ��: ֻ��ʾ�ұߵķָ���
	// 2. c �� [m - n - n/2, m]: ��ʾǰ n ��, �� n * 2 ��: ֻ��ʾ��ߵķָ���
	// 3. ��ʾ[1, n], [c - n/2, c + n/2], [m - 2*n + 1, m]: �����ָ�������ʾ

	int c = m_cur_page;
	int n = m_blockSize;
	int m = m_max_page;
	int centerStartPage = 0;

	if (c >= 1 && c <= n + n / 2 + 1)
	{
		// 1. c �� [1, n + n/2 + 1]: ��ʾǰ n * 2 ��, �� n ��: ֻ��ʾ�ұߵķָ���
		centerStartPage = n + 1;
		ui.rightSeparateLable->show();
	}
	else if (c >= m - n - n / 2 && c <= m) 
	{
		// 2. c �� [m - n - n/2, m]: ��ʾǰ n ��, �� n * 2 ��: ֻ��ʾ��ߵķָ���
		centerStartPage = m - n - n + 1;
		ui.leftSeparateLable->show();
	}
	else
	{
		// 3. ��ʾ[1, n], [c - n/2, c + n/2], [m - n + 1, m]: �����ָ�������ʾ
		centerStartPage = c - n / 2;
		ui.rightSeparateLable->show();
		ui.leftSeparateLable->show();
	}

	for(int i = 0; i < n; ++i)
	{
		// ǰ�� n ��
		pageLabels->at(i)->setText(QString::number(i + 1));         

		// �м� n ��
		pageLabels->at(n + i)->setText(QString::number(centerStartPage + i));   

		// ���� n ��
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
	// ��յ�ǰ������ʾ��
	ui.newsTableWidget->clear();

	int iStartNum = (m_cur_page - 1) * NEWS_COUNT_PER_PAGE;
	int iEndNum = iStartNum + NEWS_COUNT_PER_PAGE;

	// �����ǰҳ�Ѿ������һҳ�����Ҳ���20�����ţ���ȡ�����
	if (iEndNum > m_map_news.size())
	{
		iEndNum = m_map_news.size();
	}

	// ��ʾ��ǰҳ����
	for (int i = iStartNum; i < iEndNum; ++i)
	{
		// ���ű����ʽΪ�� ����;ʱ��;����
		QStringList strlist = m_map_news[i].split(";");

		// ����
		QString title = strlist[0];
		ui.newsTableWidget->setItem(i, 0, new QTableWidgetItem(title));

		// ʱ��
		QString time = strlist[1];
		ui.newsTableWidget->setItem(i, 1, new QTableWidgetItem(time));

		// ����
		QString url = strlist[2];
		ui.newsTableWidget->setItem(i, 2, new QTableWidgetItem(url));	
	}
}

bool NewsSpider::eventFilter(QObject *watched, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonRelease)
	{
		int page_temp = -1;
		
		// �����һҳ����һҳ 
		if (watched == ui.previousPageLable)
		{
			page_temp = getCurrentPage() - 1;
		}
		else if(watched == ui.nextPageLable)
		{
			page_temp = getCurrentPage() + 1;
		}

		// �������ҳ��
		for (int i = 0; i < pageLabels->size(); ++i)
		{
			if (watched == pageLabels->at(i))
			{
				page_temp = pageLabels->at(i)->text().toInt();
				break;
			}
		}

		// ���Ϊ��Чҳ�������õ�ǰҳ��
		if (page_temp > 0 && page_temp <= m_max_page)
		{
			setCurrentPage(page_temp);

			// ���µ�ǰҳ��
			showPageLabels();
		}

		return true;
	}

	// ͨ���༭�������ҳ��
	if (watched == ui.pageLineEdit && event->type() == QEvent::KeyRelease)
	{
		QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
		if (key_event->key() == Qt::Key_Enter || key_event->key() == Qt::Key_Return)
		{
			// �������Ϊ��Чҳ�ţ�������Ϊ��ǰҳ
			int a = ui.pageLineEdit->text().toInt();
			int b = pageLabels->count();
			if (0 < ui.pageLineEdit->text().toInt() && ui.pageLineEdit->text().toInt() <= pageLabels->count())
			{
				// ���õ�ǰҳ��
				setCurrentPage(ui.pageLineEdit->text().toInt());

				// ���µ�ǰҳ��
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
