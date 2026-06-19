#include <QApplication>
#include "MainWindow.h"

//프로그램 실행
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);//Qt 이벤트 루프 와 애플리케이션 초기화.
    MainWindow w;
    w.setWindowTitle("항공권 예매 시스템");
    w.resize(900, 600);
    w.show();
    return app.exec();  // 이벤트 루프 시작 (이후 창이 닫힐 때까지 대기)
}
