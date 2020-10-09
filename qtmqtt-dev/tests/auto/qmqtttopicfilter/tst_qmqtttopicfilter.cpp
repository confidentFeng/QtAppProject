/******************************************************************************
**
** Copyright (C) 2017 Lorenz Haas
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtMqtt module.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtMqtt/QMqttTopicFilter>
#include <QtTest/QtTest>

class Tst_QMqttTopicFilter : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void checkValidity();
    void matches();

    void usableWithQList();
    void usableWithQMap();
    void usableWithQHash();
};

void Tst_QMqttTopicFilter::checkValidity()
{
    QVERIFY(QMqttTopicFilter("a").isValid());
    QVERIFY(QMqttTopicFilter("/").isValid());
    QVERIFY(QMqttTopicFilter("a b").isValid());
    QVERIFY(QMqttTopicFilter("#").isValid());
    QVERIFY(QMqttTopicFilter("/#").isValid());
    QVERIFY(QMqttTopicFilter("a/#").isValid());
    QVERIFY(QMqttTopicFilter("/a/#").isValid());
    QVERIFY(QMqttTopicFilter("+").isValid());
    QVERIFY(QMqttTopicFilter("/+").isValid());
    QVERIFY(QMqttTopicFilter("+/").isValid());
    QVERIFY(QMqttTopicFilter("/+/").isValid());
    QVERIFY(QMqttTopicFilter("/+/+").isValid());
    QVERIFY(QMqttTopicFilter("+/#").isValid());
    QVERIFY(QMqttTopicFilter("a/+/b").isValid());

    QVERIFY(!QMqttTopicFilter("").isValid());
    QVERIFY(!QMqttTopicFilter("#/").isValid());
    QVERIFY(!QMqttTopicFilter("/a/#/").isValid());
    QVERIFY(!QMqttTopicFilter("#/#").isValid());
    QVERIFY(!QMqttTopicFilter("a#").isValid());
    QVERIFY(!QMqttTopicFilter("/a#").isValid());

    QVERIFY(!QMqttTopicFilter("a+").isValid());
    QVERIFY(!QMqttTopicFilter("+a").isValid());
    QVERIFY(!QMqttTopicFilter("++").isValid());

    QVERIFY(!QMqttTopicFilter(QString(3, QChar(QChar::Null))).isValid());

    QVERIFY(QMqttTopicFilter("$share/group/topic").isValid());
    QVERIFY(QMqttTopicFilter("$share/group/topic/subtopic").isValid());
    QVERIFY(QMqttTopicFilter("$share/group/topic/+/someother").isValid());
    QVERIFY(QMqttTopicFilter("$share/group/topic/#").isValid());
    QVERIFY(!QMqttTopicFilter("$share/groupnotopic").isValid());
    QVERIFY(!QMqttTopicFilter("$share/").isValid());
    QVERIFY(!QMqttTopicFilter("$share//foo").isValid());
}

void Tst_QMqttTopicFilter::matches()
{
    // Non normative comment's examples [4.7.1.2]
    QMqttTopicFilter filter("sport/tennis/player1/#");
    QVERIFY(filter.match(QMqttTopicName("sport/tennis/player1")));
    QVERIFY(filter.match(QMqttTopicName("sport/tennis/player1/ranking")));
    QVERIFY(filter.match(QMqttTopicName("sport/tennis/player1/score/wimbledon")));

    filter = QMqttTopicFilter("sport/#");
    QVERIFY(filter.match(QMqttTopicName("sport")));

    // Non normative comment's examples [4.7.1.3]
    filter = QMqttTopicFilter("sport/tennis/+");
    QVERIFY(filter.match(QMqttTopicName("sport/tennis/player1")));
    QVERIFY(!filter.match(QMqttTopicName("sport/tennis/player1/ranking")));

    filter = QMqttTopicFilter("sport/+");
    QVERIFY(filter.match(QMqttTopicName("sport/")));
    QVERIFY(!filter.match(QMqttTopicName("sport")));

    QVERIFY(QMqttTopicFilter("+/+").match(QMqttTopicName("/finance")));
    QVERIFY(QMqttTopicFilter("/+").match(QMqttTopicName("/finance")));
    QVERIFY(!QMqttTopicFilter("+").match(QMqttTopicName("/finance")));

    // Non normative comment's examples [4.7.2]
    QVERIFY(QMqttTopicFilter("#").match(QMqttTopicName("$SYS/foo")));
    QVERIFY(!QMqttTopicFilter("#").match(QMqttTopicName("$SYS/foo"), QMqttTopicFilter::WildcardsDontMatchDollarTopicMatchOption));

    QVERIFY(QMqttTopicFilter("+/monitor/Clients").match(QMqttTopicName("$SYS/monitor/Clients")));
    QVERIFY(!QMqttTopicFilter("+/monitor/Clients").match(QMqttTopicName("$SYS/monitor/Clients"), QMqttTopicFilter::WildcardsDontMatchDollarTopicMatchOption));

    QVERIFY(QMqttTopicFilter("$SYS/#").match(QMqttTopicName("$SYS/foo")));
    QVERIFY(QMqttTopicFilter("$SYS/#").match(QMqttTopicName("$SYS/foo"), QMqttTopicFilter::WildcardsDontMatchDollarTopicMatchOption));

    QVERIFY(QMqttTopicFilter("$SYS/monitor/+").match(QMqttTopicName("$SYS/monitor/Clients")));
    QVERIFY(QMqttTopicFilter("$SYS/monitor/+").match(QMqttTopicName("$SYS/monitor/Clients"), QMqttTopicFilter::WildcardsDontMatchDollarTopicMatchOption));
}

void Tst_QMqttTopicFilter::usableWithQList()
{
    const QMqttTopicFilter topic{"a/b"};
    QList<QMqttTopicFilter> names;
    names.append(topic);
    QCOMPARE(topic, names.constFirst());
}

void Tst_QMqttTopicFilter::usableWithQMap()
{
    const QMqttTopicFilter topic{"a/b"};
    QMap<QMqttTopicFilter, int> names;
    names.insert(topic, 42);
    QCOMPARE(names[topic], 42);
}

void Tst_QMqttTopicFilter::usableWithQHash()
{
    const QMqttTopicFilter topic{"a/b"};
    QHash<QMqttTopicFilter, int> names;
    names.insert(topic, 42);
    QCOMPARE(names[topic], 42);
}

QTEST_MAIN(Tst_QMqttTopicFilter)

#include "tst_qmqtttopicfilter.moc"
