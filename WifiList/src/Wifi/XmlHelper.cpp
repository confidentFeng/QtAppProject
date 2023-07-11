#include "XmlHelper.h"

XmlHelper::XmlHelper()
{

}

XmlHelper::~XmlHelper()
{

}

// 写xml：WIFI的profile脚本文本
void XmlHelper::WriteXml(const QString& strWifiName, const QString& strWifiPasswd)
{
    // 打开或创建文件
    QFile file(QApplication::applicationDirPath() + "/" + strWifiName + ".xml"); // 相对路径、绝对路径、资源路径都可以
    if(!file.open(QFile::WriteOnly | QFile::Truncate)) // 可以用QIODevice，Truncate表示清空原来的内容
        return;

    QDomDocument doc;
    // 写入xml头部
    QDomProcessingInstruction instruction; // 添加处理命令
    instruction = doc.createProcessingInstruction("xml", "version=\"1.0\"");
    doc.appendChild(instruction);
    // 添加根节点
    QDomElement root = doc.createElement("WLANProfile");
    root.setAttribute("xmlns", "http://www.microsoft.com/networking/WLAN/profile/v1");
    doc.appendChild(root);

    // 添加子元素-name
    QDomElement name = doc.createElement("name"); // 创建子元素
    QDomText text;
    text = doc.createTextNode(strWifiName);
    name.appendChild(text); //添加子元素值
    root.appendChild(name); // 添加子元素

    // 添加子元素-SSIDConfig
    QDomElement SSIDConfig = doc.createElement("SSIDConfig");
    QDomElement SSID = doc.createElement("SSID");
    QDomElement SSID_hex = doc.createElement("hex");
    QDomElement SSID_name = doc.createElement("name");
    //SSID_hex.appendChild(doc.createTextNode("4445565F322E3447")); // DEV_24.G 8个
	//SSID_hex.appendChild(doc.createTextNode("52454D4F54452D352E3047")); // REMOTE-5.0G 11个
	SSID_hex.appendChild(doc.createTextNode(QString(strWifiName.toLatin1().toHex())));
    SSID_name.appendChild(doc.createTextNode(strWifiName));
    SSID.appendChild(SSID_hex);
    SSID.appendChild(SSID_name);
    SSIDConfig.appendChild(SSID);
    root.appendChild(SSIDConfig);

    // 添加子元素-connectionType
    QDomElement connectionType = doc.createElement("connectionType");
    connectionType.appendChild(doc.createTextNode("ESS"));
    root.appendChild(connectionType);

    // 添加子元素-connectionMode
    QDomElement connectionMode = doc.createElement("connectionMode");
    connectionMode.appendChild(doc.createTextNode("auto"));
    root.appendChild(connectionMode);

    // 添加子元素-MSM
    QDomElement MSM = doc.createElement("MSM");
    QDomElement security = doc.createElement("security");
    // security添加子元素-authEncryption
    QDomElement authEncryption = doc.createElement("authEncryption");
    QDomElement authentication = doc.createElement("authentication");
    QDomElement encryption = doc.createElement("encryption");
    QDomElement useOneX = doc.createElement("useOneX");
    authentication.appendChild(doc.createTextNode("WPA2PSK"));
	//authentication.appendChild(doc.createTextNode("WPAPSK"));
    encryption.appendChild(doc.createTextNode("AES"));
    useOneX.appendChild(doc.createTextNode("false"));
    authEncryption.appendChild(authentication);
    authEncryption.appendChild(encryption);
    authEncryption.appendChild(useOneX);
    security.appendChild(authEncryption);

    // security添加子元素-sharedKey
    QDomElement sharedKey = doc.createElement("sharedKey");
    QDomElement keyType = doc.createElement("keyType");
    QDomElement protectedP = doc.createElement("protected");
    QDomElement keyMaterial = doc.createElement("keyMaterial");
    keyType.appendChild(doc.createTextNode("passPhrase"));
    protectedP.appendChild(doc.createTextNode("false"));
    keyMaterial.appendChild(doc.createTextNode(strWifiPasswd));
    sharedKey.appendChild(keyType);
    sharedKey.appendChild(protectedP);
    sharedKey.appendChild(keyMaterial);
    security.appendChild(sharedKey);
    // MSM添加子元素-security
    MSM.appendChild(security);
    root.appendChild(MSM);

    // 添加子元素-MSM
    QDomElement MacRandomization = doc.createElement("MacRandomization");
    MacRandomization.setAttribute("xmlns", "http://www.microsoft.com/networking/WLAN/profile/v3");
    QDomElement enableRandomization = doc.createElement("enableRandomization");
    enableRandomization.appendChild(doc.createTextNode("false"));
    MacRandomization.appendChild(enableRandomization);
    root.appendChild(MacRandomization);

    // 输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); // 缩进4格
    file.close();
}

// 读xml
void XmlHelper::ReadXml()
{
    // 新建QDomDocument类对象，它代表一个XML文档
    QDomDocument doc;
    QFile file("my.xml");
    if (!file.open(QIODevice::ReadOnly))
        return;

    // 将文件内容读到doc中
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }

    // 关闭文件
    file.close();

    // 获得doc的第一个结点，即XML说明
    QDomNode firstNode = doc.firstChild();

    // 输出XML说明,nodeName()为“xml”,nodeValue()为版本和编码信息
    qDebug() << qPrintable(firstNode.nodeName())
             << qPrintable(firstNode.nodeValue());

    // 返回根元素
    QDomElement docElem = doc.documentElement();

    // 返回根节点的第一个子结点
    QDomNode n = docElem.firstChild();

    // 如果结点不为空，则转到下一个节点
    while(!n.isNull())
    {
        // 如果结点是元素
        if (n.isElement())
        {
            // 将其转换为元素
            QDomElement e = n.toElement();

            // 返回元素标记和id属性的值
            qDebug() << qPrintable(e.tagName())
                     << qPrintable(e.attribute("id"));

            // 获得元素e的所有子结点的列表
            QDomNodeList list = e.childNodes();

            // 遍历该列表
            for(int i=0; i<list.count(); i++)
            {
                QDomNode node = list.at(i);
                if(node.isElement())
                    qDebug() << "   "<< qPrintable(node.toElement().tagName())
                             <<qPrintable(node.toElement().text());
            }
        }

        // 转到下一个兄弟结点
        n = n.nextSibling();
    }
}
