# Flaming Flaming Flamingos

## Reference & Quick Links

### SVN

- SVN Repo at blackhawk.ece.uah.edu: `/home/work/cpe353-20f/team6/ffflamingos` hereafter, the SVN repo base dir will be referred to as `ffflamingos`
- [How to use SVN](http://svnbook.red-bean.com/en/1.7/svn.tour.cycle.html)
- [See also](https://uah.hosted.panopto.com/Panopto/Pages/Viewer.aspx?id=e1c378ae-16bf-4b9c-a165-ac630125e271)
  - Warning Do Not run the svnadmin create command!

### Tools

- [How to Comment for Doxygen](https://www.doxygen.nl/manual/docblocks.html)
- Doxygen documentation at `./docs/index.html`.  This provides you with a high level documentation of the code base.

- [Style Guidelines](https://google.github.io/styleguide/cppguide.html) - To be enforced by the `clang-format` utility.

- How to rebuild documentation before a check in `./docnclean.sh`

### Links

- [Jira Board](https://uah-cpe-sd.atlassian.net/jira/software/projects/CG6/boards/4)
- [Canvas Collaborations](https://uah.instructure.com/groups/26302/collaborations)
- [Qt Classes](https://doc.qt.io/qt-5.12/classes.html)
- [Qt Docs](https://doc.qt.io/qt-5.12/index.html)

# Qt Quick Reference for CPE353

## Creating Classes

- Remember to include the line `Q_OBJECT` in the class declaration.

## Signals and Slots

```c++
connect(
  address of object emitting the signal,
  SIGNAL,
  address of the object to respond to that particular signal,
  SLOT
  )
```

### Qt4 Style Signals and Slots

The signals and slots are macros that are expanded by the inner workings of QT.  They are represented as follows:
`SIGNAL(clicked(bool))`
`SLOT(handleEvent(bool))`

### Qt5 Style Signals and Slots

The signals and slots are handled by passing the address in C++ form of the appropriate signal and slot functions:
`&QPushButton::clicked`
`&SomeClass:handlEvent`

#### Overloaded Functions in QT 5

The following returns the address of the setNum function that takes the int argument:
`static_cast<void (QLabel::*)(int)>(&QLabel::setNum)`
More can be found at [Signals & Slots](https://doc.qt.io/qt-5/signalsandslots.html)

## Modal vs NonModal

- **Modal** blocks interaction from the rest of the program until you are finished.
  - `myDialog.exec()`
- **NonModal** Lets you continue interaction with the rest of the program
  - `myDialog.show()`
Some more dialog windows can be seen at [Dialog Windows](https://doc.qt.io/qt-5/dialogs.html)

## Input Validation

Input validation is often most easily done using a `QRegularExpressionValidator`.  This looks as follows:

```c++
QRegularExpressionValidator* validatorName = new QRegularExpressionValidator(QRegularExpression("[0-9]{3}"));
someString.setValidator(validatorName);
```

You may also need to process only numerical input.  This is most easily done through `QIntValidator`

```c++
QIntValidator* validatorName = new QIntValidator(0,999, someString);
someString.setValidator(validatorName);
```

More can be found at [Qt Quick Text Input Handling and Validators](https://doc.qt.io/qt-5/qtquick-input-textinput.html)

## Tool Bar

The tool bar is used by adding `QAction` to it. See `QAction`.
The tool bar lets you have drag and drop functionality by default.  This can be handy when you're trying to implement tools that should be readily available to the user.

```c++
action1 = new QAction(...);
someToolBar->addAction(action1);
```

More can be found at [QToolBar](https://doc.qt.io/qt-5.9/qtoolbar.html)

## Menu bar

The menu bar also takes `QAction` and implements the typical `File`, `Edit`, `View`, `...` on normal windows.

```c++
action1 = new QAction(...);
actionMenu = menuBar()->addMenu("&Actions");
actionMenu->addAction(action1);
actionMenu->addSeparator();
```

More can be found at [QMenuBar](https://doc.qt.io/qt-5/qmenubar.html)

## Status Bar

```c++
QLabel* statusLabel = new QLabel("Ready");
statusBar()->addWidget(statusLabel);
```

More can be found at [QStatusBar](https://doc.qt.io/qt-5/qstatusbar.html)

## Containers

We commonly use the following types of Containers:

- `QTabWidget`

Other containers can be found at [Containers](https://doc.qt.io/qt-5/containers.html)

## Event Handlers

You may need to implement either the general or specific event handler of an event handler to get the functionality that you desire.  It is always preferred to mess with the most specific event handler possible.

### Specific

```c++
void MainWindow::keyPressEvent(QKeyEvent * key) {
    if (key && key->key() == Qt::Key_Escape) {
        bool ok;
        int count = status->text().toInt(&ok);
        if (ok) {
            count++;
            status->setNum(count);
        }
        else {
            qDebug() << "BAD BOI";
        }
    }
}

```

### Generic

```c++
bool MainWindow::event(QEvent * e) {
    if (e && e->type() == QEvent::KeyPress) {
        QKeyEvent * key = static_cast<QKeyEvent*>(e);

        if (key->key() == Qt::Key_Escape) {
            qDebug() << "Escape";
        }
    }
    return QMainWindow::event(e);
}
```

Notice how the general event handler passes the puck to `QMainWindow::event(e)` if the `MainwWindow::event(e)` call did not need to prcoess that specific event.

More can be found at [The Event System.](https://doc.qt.io/qt-5/eventsandfilters.html)

## IO functionality

### Files

***WARNING*** Paths that are relative attempt to open from the build directory.

```c++
QFile somefile("filename.txt");
if(somefile.exists()) // Returns a boolean
  somefile.open(QIODevice::ReadOnly | QIODevice::Text);
```

Notice the Logical or to combine properties.  Common properties are as follows:

- `QIODevice::ReadOnly`
- `QIODevice::WriteOnly`
- `QIODevice::ReadWrite`
- `QIODevice::Truncate` Deletes Previous Contents
- `QIODevice::Append` Adds to existing contents
- `QIODevice::Text` Use OS specific EOL

### Text and Data Streams

Remember, for Data streams you can choose to overload the `>>` and `<<` operators. The example below shows writing out using the student method discussed in Qt010.
For the following, we are using a `QDataStream`

```c++
QFile outFile( "sample.txt" );
outFile.open( QIODevice::WriteOnly)
QDataStream outStream(&outFile);
outStream.setVersion( QDataStream::Qt_4_1);
outStream<< student1 << student2 << student3;
outFile.close();
```

The following shows a similar type example but for Text Streams.  These are easier to debug although they require more space to store.

```c++
QFile outFile( "sample.txt" );
outFile.open( QIODevice::WriteOnly);
QTextStream someStream(&outFile);
someStream << "someString";
outFile.close();
```

More can be found at [File and Datastream Functions](https://doc.qt.io/qt-5/io-functions.html)

## Networking

### UDP

```c++
QUdpSocket * socket = new QUdpSocket;
connect(socket, &QUdpSocket::readyRead, this, someClass::someHandler);
socket->bind(QHostAddress::LocalHost, 5678);
```

The handler would look something like this:

```c++
QByteArray datagram;
while (socket->hasPendingDatagrams()) {
  datagram.resize(socket->pendingDatagramSize());
  socket->readDatagram(datagram.data(), datagram.size());
  QTextStream in(&dattagram);
  QString msg = in.readAll();
  msg = msg.trimmed();
  // Then put the QString where you need it.
}
```

### TCP

```c++
myTCPSocket = new QTcpSocket;                   // Allocate a new QTcpSocket
myTCPSocket->setProxy(QNetworkProxy::NoProxy);  // Avoid using a proxy if the system defaults to one

connect(
    myTCPSocket,
    &QTcpSocket::readyRead,
    this,
    &MainWindow::processPendingData
);                                  // Form the connection between the TCP socket and the handler
myTCPSocket->connectToHost(
    QHostAddress::LocalHost,
    5678,
    QIODevice::ReadOnly
);                                  // Attempt to connect to a device on incoming port 5678
myTCPSocket->waitForConnected();    // Stays in program loop until a TCP connection is established
```

Where the `processPendingData` would look something like this:

```c++
void MainWindow::processPendingData() {   
    QByteArray data = myTCPSocket->readAll();   // Allocate the memory of the size of the new line and read it in
    QString msg(data);                          // Type cast the QByteArray into a QString
    qDebug() << msg.trimmed();                  // Write out the message to debug
    ui->textBrowser->append(msg.trimmed());     // Append this wherever it needs to be
}
```

More can be found on [Networking and Connectivity.](https://doc.qt.io/qt-5/topics-network-connectivity.html)
More can be found on [QtNetwork C++ Classes](https://doc.qt.io/qt-5/qtnetwork-module.html)

## Drag and Drop

For QLabels:

- Create `class CustomLabel : public QLabel`

Function | Destination | Source
-------- | ----------- | ------
`dragEnterEvent(...)` | Y | N
`dropEvent(...)` | Y | N
`mousePressEvent(...)` | N | Y 

### Destination

- Reimplement `void dragEnterEvent(QDragEnterEvent* event);`

  ```c++
  void Label::dragEnterEvent(QDragEnterEvent* event) {
    if (event && event->mimeData()) {
      const QMimeData* md = event->mimeData();
      if(md->hasImage()) {  // Handle your MimeData as needed
        event->acceptProposedAction();
      }
    }
    QLabel::dragEnterEvent(event);
  }
  ```

- Reimplement `void dropEvent(QDropEvent* event);`

  ```c++
  void Label::dropEvent(QDropEvent* event) {
    QPixmap pic;
    if (event && event->mimeData()) {
      const QMimeData* md = event->mimeData();
      if (md->hasImage()) { // Handle your mimeData as needed
        pic = md->imageData().value<QPixmap>();
      }
    }
    QLabel::dropEvent(event);
  }
  ```

### Source

- Reimplement `void mousePressEvent(QMouseEvent* event);`

  ```c++
  void Label::mousePressEvent(QMouseEvent *event) {
    if(event && event->button() == Qt::LeftButton) {
      // Allocate and initialize Mimedata object
      QMimeData* md = new QMimeData;
      md->setImageData(*this->pixmap());

      QDrag* drag = new QDrag(this);
      drag->setMimeData(md);
      if (pixmap()) {
        drag->start();
      }
    }
  }
  ```

More can be found on the [Drag and Drop page.](https://doc.qt.io/qt-5/dnd.html)

## Model View

Data resides in the model while you may have multiple views of this data.

- `QStringListModel`
Viewed by
- `QListView`
- `QTableView`
- `QTreeView`
- `QColumnView`

Using the following:

```c++
QListView listView;
QStringList list;
QStringListModel model;
listView.setModel(&model);
list.append("someNewString);
model.setStringList(list);
```

More can be found on the [Graphics View Documentation.](https://doc.qt.io/qt-5/graphicsview.html)

## 2D Graphics

### Antialiasing

This can be enabled via

```c++
QPainter painter(this);
painter.setRenderHint(QPainter::Antialiasing);
```

### Coordinate Systems

See more on the usage of Logical COordinates on the Qt Docs [Coordinate System](https://doc.qt.io/qt-5/coordsys.html) page.


## Commonly used Properties (Other)

### QComboBox

A `QComboBox` is interected to by making appending QStrings to the values.

```c++
QComboBox someBox;
QStringList someList;
someList.append("Help");
someList.append("ME");
someBox.addItems(someList);
```

### QFile

- `size()`
- `setPermissions(...)`
- `permissions()`
- `rename(...)`
- `remove(...)`
- `exists(...)`
- `copy(...)`
- `atEnd()`
Also, note that similar things can be used for `QDir`.

### QDir

- `current()` returns current working directory
- `home()` returns user home directory
- `exists()`
- `filePath()` returns filename including path
- `absoluteFilePath()`
- `root()`
- `cd(...)`
- `cdUp()`
- `isAbsolute()`
- `isRelative()`
- `makeAbsolute()` forces conversion to absolute path

### QLabel

- Holds `QString` or `QPixmap`.
- `.setText(QString)`
- `.setPixmap(QPixmap)`

### QLineEdit

- Interact with
  - `clear`
  - `setText`
