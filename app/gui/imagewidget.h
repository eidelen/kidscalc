#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class ImageWidget;
}

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();
    void resetImg(QString imgDirPath);

    /**
     * Update the image quality.
     * @param q 0.0 bad, 1.0 best
     */
    void updateQuality(double q);

private:
    bool loadImage(QString imgDirPath);

private:
    Ui::ImageWidget *ui;
    QPixmap m_rawImage;
};

#endif // IMAGEWIDGET_H
