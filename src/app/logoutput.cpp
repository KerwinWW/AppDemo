#include "logoutput.h"
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDateTime>
#include <QMutex>
#include <QFileInfo>
#include <QMetaEnum>
#include <QSettings>
#include <QDir>

LogOutput *LogOutput::ins = nullptr;
QMutex LogOutput::m_mutex;

LogOutput::LogOutput(QObject *parent)
    : QObject(parent)
{
}

LogOutput::~LogOutput()
{
    if (m_curLogFile.isOpen())
        m_curLogFile.close();

    qInfo() << "日志输出模块释放";
}

//安装日志函数
void LogOutput::install()
{
    //创建log文件夹
    QString logPath = QCoreApplication::applicationDirPath() + "/log";
    QDir dir(logPath);
    if (!dir.exists()) {
        dir.mkdir(logPath);
        qDebug() << QString("运行日志文件夹创建成功：%1").arg(logPath);
    }

    // 打开日志输出文件（不存在则创建并打开）
    openTheLogFile();

    //安装消息处理函数
    qInstallMessageHandler(LogOutput::customMessageHandler); // 此句执行后，qDebug,qInfo等才会输出到文件

    qInfo() << "-------------------日志输出模块创建成功-------------------";
    deleteLog(); //删除过期日志
}

//卸载日志函数
void LogOutput::uninstall()
{
    qInstallMessageHandler(nullptr);
}

//日志信息处理函数
void LogOutput::outPutMsg(QtMsgType msgType, const QMessageLogContext &context, const QString &msg)
{
    //判断信息类型
    QString type;
    switch (msgType) {
    case QtDebugMsg:
        type = QString("Debug");
        break;
    case QtWarningMsg:
        type = QString("Warning");
        break;
    case QtCriticalMsg:
        type = QString("Critical");
        break;
    case QtFatalMsg:
        type = QString("Fatal");
        break;
    case QtInfoMsg:
        type = QString("Info");
    }

    m_mutex.lock(); //互斥关锁

    //文件名和行数以及函数
    //    QString contextInfo = QString("[File:(%1), Line:(%2), Funtion(%3)]:").arg(context.file).arg(context.line).arg(context.function);

    //获取当前时间，精确到秒
    QDateTime curdatetime = QDateTime::currentDateTime();
    QString currentDate = curdatetime.date().toString("yyyy-MM-dd");
    QString currentTime = curdatetime.time().toString("hh:mm:ss");

    if (m_curLogFile.isOpen()) {
        bool bFileSizeLarge = (m_curLogFile.size() >= LOG_MAXSIZE) ? true : false;
        bool bNextDate = (currentDate.compare(m_curLogFileDate, Qt::CaseInsensitive) == 0) ? false : true;

        // 当系统时间过了今天的24点到达另一天,或者超过单个日志文件最大值，切换日志输出文件
        if (bFileSizeLarge || bNextDate) {
            m_curLogFile.close();

            // 重新打开日志输出文件（不存在则创建并打开）
            openTheLogFile();
        }
    }

    //拼接信息字符串
    //    QString message = QString("[%1 %2] %3: %4 %5").arg(currentDate).arg(currentTime).arg(type).arg(contextInfo).arg(msg);
    QString message = QString("[%1 %2] %3: %4").arg(currentDate).arg(currentTime).arg(type).arg(msg);

    //存入信息到日志文件
    saveLog(message);

    m_mutex.unlock(); //开锁
}

//删除过期日志
void LogOutput::deleteLog()
{
    //获取日志文件夹地址
    QString dirName = QCoreApplication::applicationDirPath() + "/log";
    QDir dir(dirName);
    //获取文件夹下所有文件信息列表
    QFileInfoList infoList = dir.entryInfoList(QDir::Files);
    //遍历日志文件
    foreach (QFileInfo fileInfo, infoList) {
        //将文件创建时间与过期时间作比较，如果创建时间小于过期时间，则删除（代码是三天期限，如果改月为单位可以使用addMonths）
        if (fileInfo.birthTime() <= QDateTime::currentDateTime().addDays(-3)) {
            QFile::setPermissions(dirName + "/" + fileInfo.fileName(), QFileDevice::ReadOther | QFileDevice::WriteOther);
            if (QFile::remove(dirName + "/" + fileInfo.fileName())) {
                qDebug() << "过期日志文件删除成功！-->" << fileInfo.fileName();
            } else {
                qDebug() << "过期日志文件删除成功！-->" << fileInfo.fileName();
            }
        }
    }
}

//保存日志到文件
void LogOutput::saveLog(QString message)
{
    if (m_curLogFile.isOpen()) {
        QTextStream write(&m_curLogFile);
        write << message << "\r\n";
        m_curLogFile.flush(); // 刷新写入缓存
    }
}

void LogOutput::openTheLogFile()
{
    int i = 1; //当文件大小超过最大值时，给新文件添加编号

    m_curLogFileDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");

    //以天为单位给文件命名
    QString fileName = QCoreApplication::applicationDirPath() + "/log/" + m_curLogFileDate + "_log";
    //文件名右边（后缀）
    QString fileNameRight;
    //最终要写入的文件名
    QString fileNameLast = fileName + ".txt";
    //绑定文件对象
    m_curLogFile.setFileName(fileNameLast);
    //判断文件大小
    while (m_curLogFile.size() >= LOG_MAXSIZE) {
        //给新文件加入序号后缀
        fileNameRight = QString("_%1.txt").arg(i);
        //拼接最终文件名
        fileNameLast = fileName + fileNameRight;
        //修改file绑定的文件名
        m_curLogFile.setFileName(fileNameLast);
        i++;
    }
    //只写和拼接的方式打开文件
    bool isopen = m_curLogFile.open(QIODevice::WriteOnly | QIODevice::Append);
    if (isopen == true) {
    }
}

LogOutput *LogOutput::getInstance()
{
    QMutexLocker locker(&m_mutex); //必须加锁
    if (!ins) {
        ins = new LogOutput();
    }
    return ins;
}

void LogOutput::customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    LogOutput::getInstance()->outPutMsg(type, context, msg); // 调用非静态成员函数处理消息
};
