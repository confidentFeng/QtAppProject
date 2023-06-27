#include "database_xml.h"

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setHostName("easybook-3313b0");
    db.setDatabaseName("data.db");
    db.setUserName("zhouhejun");
    db.setPassword("123456");
    if(!db.open()){
        //提示出错
        return false;
    }

    QSqlQuery query;

    //创建厂家表
    query.exec("CREATE TABLE factory(id VARCHAR PRIMARY KEY,name VARCHAR)");
    query.exec(QString("INSERT INTO factory VALUES('0','请选择厂家')"));
    query.exec(QString("INSERT INTO factory VALUES('01','一汽大众')"));
    query.exec(QString("INSERT INTO factory VALUES('02','二汽神龙')"));
    query.exec(QString("INSERT INTO factory VALUES('03','上海大众')"));

    //创建品牌表
    query.exec("CREATE TABLE brand(id VARCHAR PRIMARY KEY,name VARCHAR,factory VARCHAR,\
                                    price INT,sum INT,sell INT,last INT)");
    query.exec(QString("INSERT INTO brand VALUES('01','奥迪A6','一汽大众',36,50,10,40)"));
    query.exec(QString("INSERT INTO brand VALUES('02','捷达','一汽大众',34,20,5,15)"));
    query.exec(QString("INSERT INTO brand VALUES('03','宝来','一汽大众',41,80,20,60)"));
    query.exec(QString("INSERT INTO brand VALUES('04','奔驰','一汽大众',83,40,15,25)"));
    query.exec(QString("INSERT INTO brand VALUES('05','毕加索','二汽神龙',39,50,15,35)"));
    query.exec(QString("INSERT INTO brand VALUES('06','富康','二汽神龙',28,60,10,50)"));
    query.exec(QString("INSERT INTO brand VALUES('07','标致307','二汽神龙',27,70,20,50)"));
    query.exec(QString("INSERT INTO brand VALUES('08','桑塔纳','上海大众',25,75,25,50)"));
    query.exec(QString("INSERT INTO brand VALUES('09','帕萨特','上海大众',27,65,20,45)"));

    //创建密码表
    query.exec("create table password(pwd varchar primary key)");
    query.exec("INSERT INTO password VALUES('123456')");

    return true;
}

bool createXml()
{
    QFile file("data.xml");
    if(file.exists())return true;
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
        return false;
    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement(QString("日销售清单"));
    doc.appendChild(root);
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
    return true;
}


