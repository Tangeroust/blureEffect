#include <QtWidgets/QApplication>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QFileDialog>

#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPainter>

class BlurWidget : public QWidget
{
public:
    explicit BlurWidget(QWidget* parent = Q_NULLPTR)
        : QWidget(parent), sourceImage(QImage())
    {
        setLayout(new QVBoxLayout);
        setMinimumSize(500, 600);

        imageLabel = new QLabel;
        layout()->addWidget(imageLabel);

        slider = new QSlider(Qt::Horizontal);
        slider->setMinimum(0);
        slider->setMaximum(10);
        layout()->addWidget(slider);

        connect(slider, &QSlider::valueChanged, [this](int newValue)
            {
                imageLabel->setPixmap(QPixmap::fromImage(blurImage(sourceImage, newValue).scaled
                (imageLabel->width(), imageLabel->height(), Qt::KeepAspectRatio)));
            });

        auto* button = new QPushButton("Open");
        layout()->addWidget(button);
        connect(button, &QPushButton::clicked, [this]() 
            {
                sourceImage = QImage(QFileDialog::getOpenFileName(
                    nullptr,
                    "Open JPEG picture",
                    "C:\\",
                    "jpeg files (*.jpg)"));

                imageLabel->setPixmap(QPixmap::fromImage(sourceImage).scaled
                (imageLabel->width(), imageLabel->height(), Qt::KeepAspectRatio));
            });
    }

private:
    QImage sourceImage;
    QLabel* imageLabel;
    QSlider* slider;

    QImage blurImage(QImage source, int blurRadius)
    {
        if (source.isNull()) return QImage();
        QGraphicsScene scene;
        QGraphicsPixmapItem item;
        item.setPixmap(QPixmap::fromImage(source));

        auto* blur = new QGraphicsBlurEffect;
        blur->setBlurRadius(blurRadius);
        item.setGraphicsEffect(blur);
        scene.addItem(&item);
        QImage result(source.size(), QImage::Format_ARGB32);
        result.fill(Qt::transparent);
        QPainter painter(&result);
        scene.render(&painter, QRectF(),
            QRectF(0, 0, source.width(), source.height()));

        return result;
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    BlurWidget widget;

    widget.show();

    return a.exec();
}

#include <main.moc>