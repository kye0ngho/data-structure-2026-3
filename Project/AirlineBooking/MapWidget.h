#pragma once
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QVector>
#include "Graph.h"

// 각 공항의 세계지도 상 상대적 위치 (0.0~1.0 비율, airportPoint()에서 픽셀 좌표로 변환하였습니다.)
struct AirportPos { double x; double y; };
static const AirportPos POS[] = {
    {0.770, 0.390},  //0: ICN (인천)
    {0.765, 0.410},  //1: GMP (김포)
    {0.772, 0.450},  //2: CJU (제주)
    {0.778, 0.440},  //3: PUS (부산)
    {0.805, 0.385},  //4: NRT (도쿄)
    {0.135, 0.430},  //5: LAX (로스앤젤레스)
    {0.730, 0.605},  //6: SIN (싱가포르)
    {0.745, 0.500},  //7: HKG (홍콩)
};

//QWidget 상속: paintEvent 오버라이드로 지도·노선을 QPainter로 직접 렌더링
//공항 노드는 QPushButton으로 표현, 클릭 시 airportClicked(int) 시그널 발생
class MapWidget : public QWidget {
    Q_OBJECT

    QPixmap mapPixmap;             //QPixmap::load()로 로드한 세계지도 이미지 → 구글에서 다운로드 하였음.
    AirportGraph* graph;           //인접 행렬 조회용 (hasRoute, getSize, getAirport)
    QVector<QPushButton*> buttons; //공항 수만큼 생성된 버튼 (repositionButtons에서 위치 조정)

signals:
    //QPushButton::clicked → 람다 → emit airportClicked(idx) 로 전달
    void airportClicked(int index);

public:
    MapWidget(AirportGraph* g, QWidget* parent = nullptr)
        : QWidget(parent), graph(g)
    {
        mapPixmap.load("world_map.jpg");
        setMinimumSize(680, 600);

        //graph->getSize()만큼 QPushButton 생성, 람다로 루프 변수 idx 캡처
        for (int i = 0; i < graph->getSize(); i++) {
            Airport ap = graph->getAirport(i);
            auto* btn = new QPushButton(ap.code, this);
            btn->setFixedSize(52, 22);
            btn->setStyleSheet(
                "QPushButton {"
                "  background-color: #2196F3; color: white;"
                "  border-radius: 11px; font-size: 11px; font-weight: bold;"
                "}"
                "QPushButton:hover { background-color: #64B5F6; }"
                "QPushButton:pressed { background-color: #1565C0; }"
            );
            // Qt 시그널-슬롯: QPushButton::clicked → 람다 → emit airportClicked(idx)
            int idx = i;
            connect(btn, &QPushButton::clicked, this, [this, idx]() {
                emit airportClicked(idx);
            });
            buttons.append(btn);
        }
        repositionButtons();
    }

protected:
    //Qt 이벤트: 위젯 갱신 시 자동 호출, QPainter로 지도 배경과 노선 선 렌더링 구현
    void paintEvent(QPaintEvent*) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        //QPixmap::isNull() 확인 후 drawPixmap으로 지도 출력, 없으면 단색 배경 , 지도를 입력하였기 때문에 지도 출력
        if (!mapPixmap.isNull())
            p.drawPixmap(0, 0, width(), height(), mapPixmap);
        else
            p.fillRect(rect(), QColor("#1a1a2e"));

        //hasRoute(i,j)||hasRoute(j,i)로 양방향 노선 확인, airportPoint()로 픽셀 좌표 변환 후 선 그리기
        p.setPen(QPen(QColor(255, 255, 255, 110), 1, Qt::SolidLine));
        for (int i = 0; i < graph->getSize(); i++) {
            for (int j = i + 1; j < graph->getSize(); j++) {
                if (graph->hasRoute(i, j) || graph->hasRoute(j, i)) {
                    p.drawLine(airportPoint(i), airportPoint(j));
                }
            }
        }
    }

    // Qt 이벤트: 창 리사이즈 시 자동 호출 → repositionButtons()로 버튼 위치 재계산하도록 하였습니다.
    void resizeEvent(QResizeEvent*) override {
        repositionButtons();
    }

private:
    //POS[i] 비율값 × 현재 위젯 크기(width/height)로 픽셀 좌표 계산을 구현.
    QPoint airportPoint(int i) const {
        return QPoint(
            static_cast<int>(POS[i].x * width()),
            static_cast<int>(POS[i].y * height())
        );
    }

    //airportPoint()로 각 공항 좌표 계산 후 move()로 버튼 중심 기준 배치
    void repositionButtons() {
        for (int i = 0; i < buttons.size(); i++) {
            QPoint c = airportPoint(i);
            buttons[i]->move(c.x() - 26, c.y() - 11);
        }
    }
};
