#ifndef LOGOUTPUT_H
#define LOGOUTPUT_H

#include <QObject>
#include <QtMessageHandler>
#include <QDebug>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>

#define LOG_MAXSIZE 5 * 1024 * 1024 //单个log文件最大值

class LogOutput : public QObject
{
    Q_OBJECT
public:
    static LogOutput *getInstance();

    void install();   //安装信息处理函数
    void uninstall(); //卸载信息处理函数
    void deleteLog(); //删除过期日志

protected:
    // 此函数用于注册
    static void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    //将构造函数，拷贝构造，赋值运算符都定义为私有，不允许外部类操作
    explicit LogOutput(QObject *parent = nullptr);       //构造函数
    ~LogOutput();                                        //析构
    LogOutput(const LogOutput &sig) = delete;            //拷贝构造函数
    LogOutput &operator=(const LogOutput &sig) = delete; //赋值运算符重载

private:
    static LogOutput *ins; //私有静态对象
    static QMutex m_mutex;

    QFile m_curLogFile;
    QString m_curLogFileDate; // 当前日志所属日期，防止在午夜24点刚刚过，需要更换日志输出文件

    //信息处理函数(重写的myMessageHandler)
    /*功能说明:通过调试信息保存到日志文件
     *
     *参数说明:
     * msgType: 调试信息类型或级别（qdebug, qwarning, qfatal 。。。。）
     * context: 调试信息所处文本，可使用context.file和context.line获取文本所处行数及所处文件路径，以及使用context.function获取文本所处函数名
     * msg: 调试信息内容，自定义
    */
    void outPutMsg(QtMsgType msgType, const QMessageLogContext &context, const QString &msg);

    /*
     * 函数功能:
     * 1、根据调试信息以及日期，保存到相应的文件。
     * 2、在保存文件前需要判断文件大小是否大于自定义值,如果大于,便按照序号从小到大新建一个。
    */
    void saveLog(QString message);

    // 打开日志文件
    void openTheLogFile();
};

#endif // LOGOUTPUT_H
